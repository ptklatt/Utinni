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
#include "swg/misc/swg_math.h"
#include "swg/appearance/extent.h"

namespace utinni
{
    class UTINNI_API Graphics
{
public:
    static void addPreUpdateLoopCallback(void (*func)(float elapsedTime));
    static void addPostUpdateLoopCallback(void (*func)(float elapsedTime));
    static void addPreBeginSceneCallback(void (*func)());
    static void addPostBeginSceneCallback(void (*func)());
    static void addPreEndSceneCallback(void (*func)());
    static void addPostEndSceneCallback(void (*func)());
    static void addPrePresentWindowCallback(void (*func)(HWND hwnd, int width, int height));
    static void addPostPresentWindowCallback(void (*func)(HWND hwnd, int width, int height));
    static void addPrePresentCallback(void (*func)());
    static void addPostPresentCallback(void (*func)());

    static void detour();

    static void useHardwareCursor(bool value);
    static void showMouseCursor(bool isShown);
    static void setSystemMouseCursorPosition(int X, int Y);

    static int getCurrentRenderTargetWidth();
    static int getCurrentRenderTargetHeight();

    static void flushResources(bool fullFlush);

    static void reloadTextures();

    static void setStaticShader(swgptr staticShader, int pass = 0);
    static void setObjectToWorldTransformAndScale(swg::math::Transform* objecToWorld, swg::math::Vector* scale);
    static void drawExtent(Extent* extent, swgptr vecArgbColor);
};
};

