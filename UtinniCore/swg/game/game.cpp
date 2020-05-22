#include "game.h"
#include "utinni.h";
#include "swg/client/client.h"

namespace swg::game
{
using pInstall = void(__cdecl*)(int applicationType);
using pQuit = void(__cdecl*)();
using pMainLoop = int(__cdecl*)(bool presentToWindow, HWND hwnd, int width, int height);
using pSetupScene = void(__cdecl*)(DWORD newScene);
using pCleanupScene = void(__cdecl*)();

using pGetCamera = utinni::Camera* (__cdecl*)();
using pGetConstCamera = const utinni::Camera* (__cdecl*)();

using pIsViewFirstPerson = bool(__cdecl*)();
using pIsHudSceneTypeSpace = bool(__cdecl*)();

pInstall install = (pInstall)0x00422E80;
pQuit quit = (pQuit)0x00423720;
pMainLoop mainLoop = (pMainLoop)0x004237C0;
pSetupScene setupScene = (pSetupScene)0x00424220;
pCleanupScene cleanupScene = (pCleanupScene)0x00423700;

pGetCamera getCamera = (pGetCamera)0x00425BB0;
pGetConstCamera getConstCamera = (pGetConstCamera)0x00425BE0;

pIsViewFirstPerson isViewFirstPerson = (pIsViewFirstPerson)0x00425C10;
pIsHudSceneTypeSpace isHudSceneTypeSpace = (pIsHudSceneTypeSpace)0x00426170;
}

namespace utinni
{
int getMainLoopCount()
{
    return memory::read<int>(0x1908830); // Ptr to the main loop count
}

void __cdecl hkMainLoop(bool presentToWindow, HWND hwnd, int width, int height)
{
    RECT rect;
    if (Client::getIsEditorChild() && GetWindowRect(Client::getHwnd(), &rect))
    {
        int newWidth = rect.right - rect.left;
        int newHeight = rect.bottom - rect.top;
        swg::game::mainLoop(false, Client::getHwnd(), newWidth, newHeight);
    }
    else
    {
        swg::game::mainLoop(presentToWindow, hwnd, width, height);
    }
}

void Game::detour()
{
    if (getMainLoopCount() == 0) // Checks the Games main loop count, if 0, we're in the 'suspended' startup entry point loop
    {
        swg::game::mainLoop = (swg::game::pMainLoop)Detour::Create(swg::game::mainLoop, hkMainLoop, DETOUR_TYPE_PUSH_RET);
    }
}

void Game::quit()
{
    swg::game::quit();
}

bool Game::isRunning()
{
    return getMainLoopCount();
}

Camera* Game::getCamera()
{
    return swg::game::getCamera();
}

const Camera* Game::getConstCamera()
{
    return swg::game::getConstCamera();
}

}
