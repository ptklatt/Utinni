#pragma once

#include "utinni.h"
#include "swg/object/object.h"
#include "swg/misc/swg_math.h"

namespace utinni::cuiHud
{
UTINNI_API bool collideCursorWithWorld(int x, int y, swg::math::Vector& result, Object* excludeObject);
UTINNI_API const swg::math::Vector& getCursorWorldPosition();
UTINNI_API void patchAllowTargetEverything(bool value);

extern swg::math::Vector* getWs();
extern swg::math::Vector* getWe();


void detour();
}
