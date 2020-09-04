#pragma once

#include "utinni.h"

namespace utinni::playerObject
{
UTINNI_API extern void togglePlayerAppearance();
UTINNI_API extern float getSpeed();
UTINNI_API extern void setSpeed(float value);
UTINNI_API extern void teleport(float x, float y, float z);
}
