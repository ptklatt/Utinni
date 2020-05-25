#include "utinni.h"
#include <mscoree.h>
#include <metahost.h>

#include "swg/client/client.h"
#include "swg/game/game.h"
#include "swg/graphics/graphics.h"

#pragma comment(lib, "mscoree.lib")

static const LPCWSTR netParam = L"";

std::string path;
std::string swgOverrideCfgFilename = "utinni.cfg";

ICLRMetaHost* pClrMetaHost = nullptr;
ICLRRuntimeInfo* pClrRuntimeInfo = nullptr;
ICLRRuntimeHost* pClrRuntimeHost = nullptr;

void startCLR(LPCWSTR dotNetVersion)
{
    HRESULT hr;

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
                    return;
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
}

void stopCLR()
{
    pClrRuntimeHost->Release();
    pClrRuntimeInfo->Release();
    pClrMetaHost->Release();

    pClrRuntimeHost = nullptr;
    pClrRuntimeInfo = nullptr;
    pClrMetaHost = nullptr;
}

void loadCoreDotNet()
{
    std::string path = Utinni::getPath();
    int pathSize = MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), NULL, 0);
    std::wstring wPath(pathSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), &wPath[0], pathSize);

    const std::wstring combinedPath = wPath + L"UtinniCoreDotNet.dll";

    startCLR(L"v4.0.30319");
    if (pClrRuntimeHost != nullptr)
    {
        DWORD result;
        HRESULT hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(combinedPath.c_str(), L"UtinniCoreDotNet.Startup", L"EntryPoint", netParam, &result);
        if (hr == S_OK)
            return;

        pClrRuntimeHost->Release();
        pClrRuntimeHost = nullptr;
    }
}

void main()
{
    char dllPathbuffer[MAX_PATH];
    HMODULE handle = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&loadCoreDotNet, &handle);
    GetModuleFileNameA(handle, dllPathbuffer, sizeof(dllPathbuffer));
    std::string dllPath = std::string(dllPathbuffer);
    path = dllPath.substr(0, dllPath.find_last_of("\\/")) + "\\";

    utinni::loadConfig();

    utinni::Client::setIsEditorChild(utinni::getConfigBool("UtinniCore", "isEditorChild"));

    utinni::Client::detour();
    utinni::Game::detour();
    utinni::Graphics::detour();

    loadCoreDotNet();
}

void detatch()
{
    stopCLR();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) 
{
	 switch (fdwReason) 
	 {
	 case DLL_PROCESS_ATTACH:
		  CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
		  return true;

	 case DLL_PROCESS_DETACH:
        detatch();
		  return true;
	 }
	 return false;
}

std::string Utinni::getPath()
{
    return path;
}

std::string Utinni::getSwgCfgFilename()
{
    return swgOverrideCfgFilename;
}
