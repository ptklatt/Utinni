#include "game.h"
#include "utinni.h";

namespace swg::game
{
using pInstall = void(__cdecl*)(int applicationType);
using pQuit = void(__cdecl*)();
using pMainLoop = int(__cdecl*)(bool presentToWindow, HWND hwnd, int width, int height);
using pSetupScene = void(__cdecl*)(DWORD newScene);
using pCleanupScene = void(__cdecl*)();

using pIsViewFirstPerson = bool(__cdecl*)();
using pIsHudSceneTypeSpace = bool(__cdecl*)();

pInstall install = (pInstall)0x00422E80;
pQuit quit = (pQuit)0x00423720;
pMainLoop mainLoop = (pMainLoop)0x004237C0;
pSetupScene setupScene = (pSetupScene)0x00424220;
pCleanupScene cleanupScene = (pCleanupScene)0x00423700;

pIsViewFirstPerson isViewFirstPerson = (pIsViewFirstPerson)0x00425C10;
pIsHudSceneTypeSpace isHudSceneTypeSpace = (pIsHudSceneTypeSpace)0x00426170;
}

void __cdecl hkMainLoop(bool presentToWindow, HWND hwnd, int width, int height)
{
    swg::game::mainLoop(presentToWindow, hwnd, width, height);
}

namespace utinni
{

int getMainLoopCount()
{
    return memory::read<int>(0x1908830); // Ptr to the main loop count
}

void Game::detour()
{
    if (getMainLoopCount() == 0) // Checks the Games main loop count, if 0, we're in the 'suspended' startup entry point loop
    {
        swg::game::mainLoop = (swg::game::pMainLoop)Detour::Create(swg::game::mainLoop, hkMainLoop, DETOUR_TYPE_PUSH_RET);

    }
    else
    {

    }

}

void Game::quit()
{
    swg::game::quit();
}

}
