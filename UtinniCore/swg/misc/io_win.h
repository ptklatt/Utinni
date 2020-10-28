/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#pragma once

#include "utinni.h"

namespace utinni
{
enum VirtualKeys
{
    VK_A = 0x41,
    VK_C = 0x43,
    VK_D = 0x44,
    VK_S = 0x53,
    VK_W = 0x57,
    VK_X = 0x58,
};

class UTINNI_API IoWin
{
public:
    swgptr vtbl;
    char* name;
    IoWin* ioWin;
};

class UTINNI_API MouseCursor
{
public:
    uint32_t style;
    bool unk01;
    int unk02;
    int localX;
    int localY;
    int* x;
    int* y;
};

struct UTINNI_API IoEvent
{
    enum Type
    {
        t_Update = 4,
        t_InputReset = 5,
        t_Character = 6,
        t_KeyDown = 7,
        t_KeyUp = 8,
        t_MouseButtonDown = 15,
        t_MouseButtonUp = 16,
    };

    enum Keys
    {
        kc_Q = 16,
        kc_W = 17,
        kc_E = 18,
        kc_R = 19,
        kc_T = 20,
        kc_Y = 21,
        kc_U = 22,
        kc_I = 23,
        kc_O = 24,
        kc_P = 25,

        kc_A = 30,
        kc_S = 31,
        kc_D = 32,
        kc_F = 33,
        kc_G = 34,
        kc_H = 35,
        kc_J = 36,
        kc_K = 37,
        kc_L = 38,

        kc_Z = 44,
        kc_X = 45,
        kc_C = 46,
        kc_V = 47,
        kc_B = 48,
        kc_N = 49,
        kc_M = 50,

        kc_LShift = 42,
        kc_LCtrl = 29,
        kc_LAlt = 56,

        kc_RShift = 54,
        kc_RCtrl = 157,
        kc_RAlt = 184,

        kc_Enter = 28,
        kc_Space = 57,
    };

    enum MouseButtons
    {
        mb_Left = 0,
        mb_Right = 1,
        mb_Middle = 2,
        mb_Side = 3,
    };

    swgptr unk;
    int type;
    int arg1;
    int arg2;
    float arg3;

};

class UTINNI_API MessageQueue
{
public:
    int getCount();
    void getMessage(int index, int* msg, float* value);
    void appendMessage(int msg, float value);
    void appendMessage(int msg, float value, swgptr data);
};


}

