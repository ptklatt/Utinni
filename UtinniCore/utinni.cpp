#include "utinni.h"
#include <codecvt>
#include <mscoree.h>
#include <metahost.h>

#include "swg/game/game.h"

#pragma comment(lib, "mscoree.lib")

static const LPCWSTR netParam = L"";

UtinniBase* baseUtinniInstance = nullptr;
Utinni* utinniInstance = nullptr;

std::string utinniPath;
std::string swgOverrideCfgFilename;

UtinniBase* UtinniBase::instance() 
{
	 if (!baseUtinniInstance)
	 {
        baseUtinniInstance = new UtinniBase();
	 }
	 return baseUtinniInstance;
}

void UtinniBase::cleanUpHook() 
{
	 SAFE_DELETE(utinniInstance);
}

UtinniBase::UtinniBase() 
{
	 DisableThreadLibraryCalls(GetModuleHandle(nullptr));
}

bool UtinniBase::initialize() 
{
    utinniInstance = Utinni::instance();
	 return true;
}

UtinniBase::~UtinniBase() 
{
	 SAFE_DELETE(utinniInstance);
    baseUtinniInstance = nullptr;
}

Utinni* Utinni::instance()
{
    baseUtinniInstance = UtinniBase::instance();
    if (!utinniInstance && baseUtinniInstance)
    {
        utinniInstance = new Utinni();
    }
    return utinniInstance;
}

ICLRRuntimeHost* startCLR(LPCWSTR dotNetVersion)
{
    HRESULT hr;

    ICLRMetaHost* pClrMetaHost = nullptr;
    ICLRRuntimeInfo* pClrRuntimeInfo = nullptr;
    ICLRRuntimeHost* pClrRuntimeHost = nullptr;

    // Get information about the installed .NET
    hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pClrMetaHost);
    if (hr == S_OK)
    {
        // Ge runtime information for this version of .NET
        hr = pClrMetaHost->GetRuntime(dotNetVersion, IID_PPV_ARGS(&pClrRuntimeInfo));
        if (hr == S_OK)
        {
            // Check if the CLR can be loaded
            BOOL isLoadable;
            hr = pClrRuntimeInfo->IsLoadable(&isLoadable);
            if ((hr == S_OK) && isLoadable)
            {
                // Load the CLR into the process and get a ptr for the interface
                hr = pClrRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_PPV_ARGS(&pClrRuntimeHost));
                if (hr == S_OK)
                {
                    // Start the CLR
                    pClrRuntimeHost->Start();
                    return pClrRuntimeHost;
                }
            }
        }
    }

    // Cleanup if failed
    if (pClrRuntimeHost)
    {
        pClrRuntimeHost->Release();
        pClrRuntimeHost = nullptr;
    }

    if (pClrRuntimeInfo)
    {
        pClrRuntimeInfo->Release();
        pClrRuntimeInfo = nullptr;
    }

    if (pClrMetaHost)
    {
        pClrMetaHost->Release();
        pClrMetaHost = nullptr;
    }

    return nullptr;
}

void loadCoreDotNet()
{
    std::string path = Utinni::getUtinniPath();
    int pathSize = MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), NULL, 0);
    std::wstring wPath(pathSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), &wPath[0], pathSize);

    const std::wstring combinedPath = wPath + L"UtinniCoreDotNet.dll";

    HRESULT hr;
    ICLRRuntimeHost* pClr = startCLR(L"v4.0.30319");
    if (pClr != nullptr)
    {
        DWORD result;
        hr = pClr->ExecuteInDefaultAppDomain(combinedPath.c_str(), L"UtinniCoreDotNet.Startup", L"EntryPoint", L"", &result);
    }
}

Utinni::Utinni()
{
    char dllPathbuffer[MAX_PATH];
    HMODULE handle = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&Utinni::instance, &handle);
    GetModuleFileNameA(handle, dllPathbuffer, sizeof(dllPathbuffer));
    std::string dllPath = std::string(dllPathbuffer);
    utinniPath = dllPath.substr(0, dllPath.find_last_of("\\/")) + "\\";

    swgOverrideCfgFilename = "utinni.cfg";

    utinni::Game::detour();

    loadCoreDotNet();
}

Utinni::~Utinni() {}

std::string Utinni::getUtinniPath()
{
    return utinniPath;
}

std::string Utinni::getSwgCfgFilename()
{
    return swgOverrideCfgFilename;
}