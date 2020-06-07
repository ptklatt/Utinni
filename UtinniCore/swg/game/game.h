#pragma once

#include "utinni.h"

namespace utinni
{
class Camera;

class UTINNI_API Game
{
public:
    static void addMainLoopCallback(void(*func)());

    static void detour();
    static void quit();

    static bool isRunning();

    static Camera* getCamera();
    static const Camera* getConstCamera();

};
}
