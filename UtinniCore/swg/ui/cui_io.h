#pragma once

#include "utinni.h"

namespace utinni::cuiIo
{
swgptr get();
UTINNI_API extern void enableKeyboard(bool value);
UTINNI_API extern void restorePreviousEnableKeyboardValue();
void detour();
}
