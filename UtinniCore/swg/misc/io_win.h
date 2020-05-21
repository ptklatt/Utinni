#pragma once

#include "utinni.h"

namespace utinni
{
enum commands
{
    cmd_up = 3332,
    cmd_upfast,
    cmd_down,
    cmd_downfast
};

class UTINNI_API IoWin
{
public:
    DWORD* vtbl;
    char* name;
    IoWin* ioWin;
};

class UTINNI_API MouseCursor
{
public:
    unsigned int style;
    bool unk01;
    int unk02;
    int localX;
    int localY;
    int& x;
    int& y;
};
}

