#pragma once
#include "utinni.h"

namespace directX
{
void detour();

UTINNI_API extern void toggleWireframe();
UTINNI_API extern void blockPresent(bool value);
UTINNI_API extern bool isPresentBlocked();
}
