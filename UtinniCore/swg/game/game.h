#pragma once

#include "utinni.h"
#include "swg/misc/repository.h"

namespace utinni
{
class Camera;
class Object;

class UTINNI_API Game
{
public:
    static void addInstallCallback(void(*func)());
    static void addMainLoopCallback(void(*func)());
    static void addSetSceneCallback(void(*func)());
    static void addCleanupSceneCallback(void(*func)());

    static void detour();
    static void quit();

    static bool isRunning();

    static void loadScene();
    static void loadScene(const char* terrainFilename, const char* avatarObjectFilename = "object/creature/player/shared_human_male.iff");
    static void cleanupScene();

    static Repository* getRepository();

    static Object* getPlayer();
    static Object* getPlayerCreatureObject();
    static swgptr getPlayerLookAtTargetObjectNetworkId();
    static Object* getPlayerLookAtTargetObject();

    static Camera* getCamera();
    static const Camera* getConstCamera();


};
}
