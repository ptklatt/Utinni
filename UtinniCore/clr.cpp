#include "clr.h"
#include <mscoree.h>
#include <metahost.h>

#include "utinni.h"
#include "swg/game/game.h"

#pragma comment(lib, "mscoree.lib")

static const LPCWSTR netParam = L"";

ICLRMetaHost* pClrMetaHost = nullptr;
ICLRRuntimeInfo* pClrRuntimeInfo = nullptr;
ICLRRuntimeHost* pClrRuntimeHost = nullptr;

namespace clr
{
void start()
{
    HRESULT hr;

    // Get information about the installed .NET
    hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pClrMetaHost);
    if (SUCCEEDED(hr))
    {
        // Get the runtime information for this version of .NET
        hr = pClrMetaHost->GetRuntime(L"v4.0.30319", IID_PPV_ARGS(&pClrRuntimeInfo));
        if (SUCCEEDED(hr))
        {
            // Check if the CLR can be loaded
            BOOL isLoadable;
            hr = pClrRuntimeInfo->IsLoadable(&isLoadable);
            if ((SUCCEEDED(hr)) && isLoadable)
            {
                // Load the CLR into the process and get a ptr for the interface
                hr = pClrRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_PPV_ARGS(&pClrRuntimeHost));
                if (SUCCEEDED(hr))
                {
                    // Start the CLR
                    pClrRuntimeHost->Start();
                    return;
                }
            }
        }
    }

    utinni::log::critical("Failed to start CLR");

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

void stop()
{
    pClrRuntimeHost->Release();
    pClrRuntimeInfo->Release();
    pClrMetaHost->Release();

    pClrRuntimeHost = nullptr;
    pClrRuntimeInfo = nullptr;
    pClrMetaHost = nullptr;
}

void load()
{
    std::string path = utinni::getPath();
    int pathSize = MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), NULL, 0);
    std::wstring wPath(pathSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), &wPath[0], pathSize);

    const std::wstring combinedPath = wPath + L"UtinniCoreDotNet.dll";

    start();
    if (pClrRuntimeHost != nullptr)
    {
        DWORD result;
        HRESULT hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(combinedPath.c_str(), L"UtinniCoreDotNet.Startup", L"EntryPoint", netParam, &result);
        if (hr == S_OK)
            return;

        // If the CLR Runtime Host crashes, shut the game down and release the CLR
        utinni::Game::quit();
        stop();
    }
}
}
