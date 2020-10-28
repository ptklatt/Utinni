/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

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
    int pathSize = MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), nullptr, 0);
    std::wstring wPath(pathSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), &wPath[0], pathSize);

    const std::wstring combinedPath = wPath + L"UtinniCoreDotNet.dll";

    start();
    if (pClrRuntimeHost != nullptr)
    {
        DWORD result;
        HRESULT hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(combinedPath.c_str(), L"UtinniCoreDotNet.Startup", L"EntryPoint", netParam, &result);
        if (hr == S_OK)
        {
            return;
        }

        // If the CLR Runtime Host crashes, shut the game down and release the CLR
        utinni::Game::quit();
        stop();
    }
}
}
