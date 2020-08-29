#pragma once

#include "utinni.h"
#include "swg/object/object.h"

namespace utinni::creatureObject // temporary
{
UTINNI_API extern void addOnTargetCallback(void(*func)(Object* target));

void detour();
}
