#include "utinni.h"
#include <mscoree.h>
#include <metahost.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "swg/client/client.h"
#include "swg/game/game.h"
#include "swg/graphics/graphics.h"
#include "swg/scene/ground_scene.h"
#include "swg/ui/cui_manager.h"
#include "swg/ui/imgui_impl.h"
#include "swg/misc/config.h"
#include "swg/misc/tree_file.h"
#include "swg/ui/cui_chat_window.h"
#include "swg/ui/cui_radial_menu.h"
#include "swg/ui/cui_hud.h"
#include "swg/ui/cui_menu.h"

#pragma comment(lib, "mscoree.lib")

static const LPCWSTR netParam = L"";

std::string path;
std::string swgOverrideCfgFilename = "utinni.cfg";

static utinni::UtINI ini;

ICLRMetaHost* pClrMetaHost = nullptr;
ICLRRuntimeInfo* pClrRuntimeInfo = nullptr;
ICLRRuntimeHost* pClrRuntimeHost = nullptr;

void startCLR()
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

    spdlog::critical("Failed to start CLR");

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
    std::string path = utinni::getPath();
    int pathSize = MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), NULL, 0);
    std::wstring wPath(pathSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, &path[0], (int)path.size(), &wPath[0], pathSize);

    const std::wstring combinedPath = wPath + L"UtinniCoreDotNet.dll";

    startCLR();
    if (pClrRuntimeHost != nullptr)
    {
        DWORD result;
        HRESULT hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(combinedPath.c_str(), L"UtinniCoreDotNet.Startup", L"EntryPoint", netParam, &result);
        if (hr == S_OK)
            return;

        // If the CLR Runtime Host crashes, shut the game down and release the CLR
        utinni::Game::quit();
        stopCLR();
    }
}

void detourGame()
{
    swg::config::detour();

    utinni::treefile::detour();
    utinni::Client::detour();
    utinni::Game::detour();
    utinni::GroundScene::detour();
    utinni::Graphics::detour();
    utinni::CuiChatWindow::detour();
    utinni::CuiManager::detour();
    utinni::cuiHud::detour();
    utinni::cuiMenu::detour();
    utinni::cuiRadialMenuManager::detour();
}

void main()
{
    char dllPathbuffer[MAX_PATH];
    HMODULE handle = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&loadCoreDotNet, &handle);
    GetModuleFileNameA(handle, dllPathbuffer, sizeof(dllPathbuffer));
    std::string dllPath = std::string(dllPathbuffer);
    path = dllPath.substr(0, dllPath.find_last_of("\\/")) + "\\";

    ini = utinni::UtINI(std::string(path + "ut.ini").c_str());

    spdlog::set_level(spdlog::level::debug);

    spdlog::set_pattern("[%H:%M:%S] [%l]%! %v");
    spdlog::flush_on(spdlog::level::info);

    std::string logName = "utinni";
    std::string previousLogFilename = path + logName + "_previous.log";
    std::string logFilename = path + logName + ".log";

    // Delete previous log and rename the current log to previous log, so spdlog can create a clean new log
    std::remove(previousLogFilename.c_str());
    std::rename(logFilename.c_str(), previousLogFilename.c_str());

    auto file_logger = spdlog::basic_logger_mt("UtinniLog", logFilename);
    spdlog::set_default_logger(file_logger);

    spdlog::info("Process: " + std::to_string(_getpid()));

    utinni::Client::setEditorMode(ini.getBool("UtinniCore", "enableEditorMode"));
    imgui_impl::enableInternalUi(ini.getBool("UtinniCore", "enableInternalUi"));

    detourGame();

    // ToDo Add C++ plugin load before C# plugin load

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

namespace utinni
{

const std::string& getPath()
{
    return path;
}

const std::string& getSwgCfgFilename()
{
    return swgOverrideCfgFilename;
}

UtINI& getConfig()
{
    return ini;
}

  

}
