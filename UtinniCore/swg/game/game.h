#pragma once

#include "utinni.h"

namespace utinni
{
class Camera;

class UTINNI_API Game
{
public:
    static void detour();
    static void quit();

    static Camera* getCamera();
    static const Camera* getConstCamera();

};
}
