#pragma once

#include "utinni.h"

namespace utinni
{
class UTINNI_API Graphics
{
public:
    static void detour();

    static void useHardwareCursor(bool value);
    static void showMouseCursor(bool isShown);
    static void setSystemMouseCursorPosition(int X, int Y);

    static int getCurrentRenderTargetWidth();
    static int getCurrentRenderTargetHeight();

    static void flushResources(bool fullFlush);

    static void reloadTextures();
};
};

