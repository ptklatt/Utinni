#pragma once

#include "utinni.h"

namespace utinni
{
class UTINNI_API DirectInput
{
public:
    static void suspend();
    static void resume();

    static void detour();
};
}