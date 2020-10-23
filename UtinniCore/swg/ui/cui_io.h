#pragma once

#include "utinni.h"

namespace utinni::cuiIo
{
swgptr get();
UTINNI_API extern void enableKeyboard(bool value);
UTINNI_API extern void restorePreviousEnableKeyboardValue();
UTINNI_API extern bool isInputBlocked();
void detour();
}
