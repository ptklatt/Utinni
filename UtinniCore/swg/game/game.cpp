#include "game.h"
#include "utinni.h";
#include "swg/client/client.h"
#include "swg/misc/config.h"
#include "swg/object/object.h"
#include "swg/scene/ground_scene.h"
#include "swg/scene/world_snapshot.h"
#include "swg/ui/imgui_impl.h"

namespace swg::game
{
using pInstall = void(__cdecl*)(int applicationType);
using pQuit = void(__cdecl*)();
using pMainLoop = void(__cdecl*)(bool presentToWindow, HWND hwnd, int width, int height);

using pSetupScene = void(__cdecl*)(utinni::GroundScene* newScene);
using pCleanupScene = void(__cdecl*)();

using pGetPlayer = utinni::Object* (__cdecl*)();
using pGetPlayerCreatureObject = utinni::Object* (__cdecl*)();

using pGetCamera = utinni::Camera* (__cdecl*)();
using pGetConstCamera = const utinni::Camera* (__cdecl*)();

using pIsViewFirstPerson = bool(__cdecl*)();
using pIsHudSceneTypeSpace = bool(__cdecl*)();

pInstall install = (pInstall)0x00422E80;
pQuit quit = (pQuit)0x00423720;
pMainLoop mainLoop = (pMainLoop)0x004237C0;

pSetupScene setupScene = (pSetupScene)0x00424220;
pCleanupScene cleanupScene = (pCleanupScene)0x00423700;

pGetPlayer getPlayer = (pGetPlayer)0x00425140;
pGetPlayerCreatureObject getPlayerCreatureObject = (pGetPlayerCreatureObject)0x004251D0;

pGetCamera getCamera = (pGetCamera)0x00425BB0;
pGetConstCamera getConstCamera = (pGetConstCamera)0x00425BE0;

pIsViewFirstPerson isViewFirstPerson = (pIsViewFirstPerson)0x00425C10;
pIsHudSceneTypeSpace isHudSceneTypeSpace = (pIsHudSceneTypeSpace)0x00426170;
}

static std::vector<void(*)()> mainLoopCallbacks;
static std::vector<void(*)()> cleanUpSceneCallbacks;
static utinni::Repository repository;

namespace utinni
{

void Game::addMainLoopCallback(void(*func)())
{
    mainLoopCallbacks.emplace_back(func);
}

void Game::addCleanupSceneCallback(void(*func)())
{
    cleanUpSceneCallbacks.emplace_back(func);
}

int getMainLoopCount()
{
    return memory::read<int>(0x1908830); // Ptr to the main loop count
}

bool loadNewScene = false;
bool sceneCleaned = false;
std::string sceneToLoadTerrainFilename;
std::string sceneToLoadAvatarObjectFilename;
void __cdecl hkMainLoop(bool presentToWindow, HWND hwnd, int width, int height)
{
    RECT rect;
    if (Client::getEditorMode() && GetWindowRect(Client::getHwnd(), &rect))
    {
        int newWidth = rect.right - rect.left;
        int newHeight = rect.bottom - rect.top;

        swg::game::mainLoop(false, Client::getHwnd(), newWidth, newHeight); // ToDo fix random crash with getHwnd on load Scene?
    }
    else
    {
        swg::game::mainLoop(presentToWindow, hwnd, width, height);
    }

    for (const auto& func : mainLoopCallbacks)
    {
        func();
    }

    if (loadNewScene && sceneCleaned)
    {
        loadNewScene = false;
        sceneCleaned = false;
        swg::game::setupScene(GroundScene::ctor(sceneToLoadTerrainFilename.c_str(), sceneToLoadAvatarObjectFilename.c_str()));
    }

    if (loadNewScene)
    {
        Game::cleanupScene();
        sceneCleaned = true;
    }
}

void __cdecl hkInstall(int application)
{
    swg::game::install(application);
    repository = Repository();
    WorldSnapshot::generateHighestId();
    if (getConfig().getBool("UtinniCore", "autoLoadScene"))
    {
        Game::loadScene();
    }
}

void __cdecl hkCleanupScene()
{
    swg::game::cleanupScene();

    imgui_gizmo::disable();

    for (const auto& func : cleanUpSceneCallbacks)
    {
        func();
    }

}

void Game::detour()
{
    if (getMainLoopCount() == 0) // Checks the Games main loop count, if 0, we're in the 'suspended' startup entry point loop
    {
        //utility::showMessageBox("");
        swg::game::mainLoop = (swg::game::pMainLoop)Detour::Create(swg::game::mainLoop, hkMainLoop, DETOUR_TYPE_PUSH_RET);
        swg::game::install = (swg::game::pInstall)Detour::Create(swg::game::install, hkInstall, DETOUR_TYPE_PUSH_RET);
        swg::game::cleanupScene = (swg::game::pCleanupScene)Detour::Create(swg::game::cleanupScene, hkCleanupScene, DETOUR_TYPE_PUSH_RET);
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

void Game::loadScene()
{
    sceneToLoadTerrainFilename = swg::config::clientGame::getSceneTerrainFilename();
    sceneToLoadAvatarObjectFilename = swg::config::clientGame::getSceneAvatarFilename();
    loadNewScene = true;
}

void Game::loadScene(const char* terrainFilename, const char* avatarObjectFilename)
{
    sceneToLoadTerrainFilename = terrainFilename;
    sceneToLoadAvatarObjectFilename = avatarObjectFilename;
    loadNewScene = true;
}

void Game::cleanupScene()
{
    swg::game::cleanupScene();
}

Repository* Game::getRepository()
{
    return &repository;
}

Object* Game::getPlayer()
{
    return swg::game::getPlayer();
}

Object* Game::getPlayerCreatureObject() // ToDo return CreatureObject*
{
    return swg::game::getPlayerCreatureObject();
}

swgptr Game::getPlayerLookAtTargetObjectNetworkId()
{
    const Object* playerObj = getPlayerCreatureObject();

    if (!playerObj)
        return 0;

    return (swgptr)playerObj + 1432;
}

Object* Game::getPlayerLookAtTargetObject()
{
    const swgptr lookAtId = getPlayerLookAtTargetObjectNetworkId();

    if (lookAtId == 0)
        return nullptr;

    return Object::getObjectById(lookAtId);
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
