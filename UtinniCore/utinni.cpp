#include "utinni.h"
#include "clr.h"

#include "plugin_framework/plugin_manager.h"
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
#include "swg/ui/cui_misc.h"
#include "swg/object/creature_object.h"

std::string path;
std::string swgOverrideCfgFilename = "utinni.cfg";

static utinni::UtINI ini;
utinni::PluginManager pluginManager;

void createDetours()
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
    utinni::creatureObject::detour();
    utinni::report::detour();
}

void createPatches()
{
    utinni::cuiMisc::patch();
}

void main()
{
    char dllPathbuffer[MAX_PATH];
    HMODULE handle = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&createDetours, &handle);
    GetModuleFileNameA(handle, dllPathbuffer, sizeof(dllPathbuffer));
    std::string dllPath = std::string(dllPathbuffer);
    path = dllPath.substr(0, dllPath.find_last_of("\\/")) + "\\";

    ini = utinni::log::create();

    utinni::Client::setEditorMode(ini.getBool("UtinniCore", "enableEditorMode"));
    imgui_impl::enableInternalUi(ini.getBool("UtinniCore", "enableInternalUi"));

    // Adds hooks to functions inside the game
    createDetours();

    // Patches memory instructions inside the game
    createPatches();

    pluginManager.loadPlugins();

    // Load the clr and UtinniCoreDotNet
    clr::load();
}

void detatch()
{
    clr::stop();
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