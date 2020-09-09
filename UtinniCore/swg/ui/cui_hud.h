#pragma once

#include "utinni.h"
#include "swg/misc/swg_math.h"

namespace utinni::cuiHud
{
UTINNI_API const swg::math::Vector& getCursorWorldPosition();
UTINNI_API void patchAllowTargetEverything(bool value);

void detour();
}
