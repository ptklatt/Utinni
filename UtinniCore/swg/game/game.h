#pragma once

#include "utinni.h"
#include "swg/camera/camera.h"

namespace utinni
{
class UTINNI_API Game
{
public:
    static void detour();
    static void quit();

    static Camera* getCamera();
    static const Camera* getConstCamera();

};
}
