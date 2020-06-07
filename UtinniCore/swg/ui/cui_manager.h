#pragma once

#include "utinni.h"

namespace utinni
{
class UTINNI_API CuiManager
{
public:
    static void setSize(int width, int height);
    static void togglePointer(bool isOn);
    static bool isRenderingUi();
    static bool hasObjectUnderCursor();

    static void detour();
};

class UTINNI_API UiManager
{
public:
    static UiManager* get();
    void drawCursor(bool value);
};


}

