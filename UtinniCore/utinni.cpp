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

#include "utinni.h"
#include "clr.h"

#include "plugin_framework/plugin_manager.h"
#include "swg/appearance/skeleton.h"
#include "swg/camera/debug_camera.h"
#include "swg/client/client.h"
#include "swg/game/game.h"
#include "swg/graphics/graphics.h"
#include "swg/misc/config.h"
#include "swg/misc/tree_file.h"
#include "swg/object/creature_object.h"
#include "swg/scene/client_world.h"
#include "swg/scene/ground_scene.h"
#include "swg/ui/cui_manager.h"
#include "swg/ui/imgui_impl.h"
#include "swg/ui/cui_chat_window.h"
#include "swg/ui/cui_radial_menu.h"
#include "swg/ui/cui_hud.h"
#include "swg/ui/cui_menu.h"
#include "swg/ui/cui_misc.h"
#include "swg/ui/cui_io.h"
#include "swg/graphics/directx9.h"
#include "swg/scene/render_world.h"

std::string path;
std::string swgOverrideCfgFilename = "utinni.cfg";

static utinni::UtINI ini;
utinni::PluginManager pluginManager;

void createDetours()
{
    utinni::log::info("Creating detours");

    swg::config::detour();

    utinni::Client::detour();
    utinni::clientWorld::detour();
    utinni::creatureObject::detour();
    utinni::CuiChatWindow::detour();
    utinni::CuiManager::detour();
    utinni::cuiHud::detour();
    utinni::cuiIo::detour();
    //utinni::cuiIntro::detour();
    utinni::cuiMenu::detour();
    utinni::cuiRadialMenuManager::detour();
    utinni::cuiLoginScreen::detour();
    //utinni::cuiMediatorFactorySetup::detour();
    utinni::debugCamera::detour();
    utinni::Game::detour();
    utinni::GroundScene::detour();
    utinni::Graphics::detour();
    utinni::ParticleEffectAppearance::detour();
    utinni::report::detour();
    utinni::skeletalAppearance::detour();
    utinni::SystemMessageManager::detour();
    utinni::treefile::detour();
    utinni::renderWorld::detour();
}

void createPatches()
{
    utinni::log::info("Creating patches");

    utinni::cuiMisc::patch();
    utinni::debugCamera::patch();
}

void main()
{
    char dllPathbuffer[MAX_PATH];
    HMODULE handle = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&createDetours, &handle);
    GetModuleFileNameA(handle, dllPathbuffer, sizeof(dllPathbuffer));
    std::string dllPath = std::string(dllPathbuffer);
    path = dllPath.substr(0, dllPath.find_last_of("\\/")) + "\\";

    utinni::log::create();

    ini.createUtinniSettings();
    ini.load(path + "ut.ini");

    utinni::Client::setEditorMode(ini.getBool("Editor", "enableEditorMode"));
    imgui_impl::enableInternalUi(ini.getBool("UtinniCore", "enableInternalUi"));

    // Adds hooks to functions inside the game
    createDetours();

    // Patches memory instructions inside the game
    createPatches();

    utinni::log::info("Loading C++ plugins");
    pluginManager.loadPlugins();

    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    utinni::log::info("Loading .NET plugins");
    // Load the clr and UtinniCoreDotNet
    clr::load();
}

void detatch()
{
    directX::cleanup();
    clr::stop();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, nullptr, 0, nullptr);
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

PluginManager& getPluginManager()
{
    return pluginManager;
}
}
