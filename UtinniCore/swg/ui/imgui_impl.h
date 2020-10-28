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

#include <d3d9.h>
#include "utinni.h"

namespace utinni
{
class Object;
}

namespace imgui_impl
{
UTINNI_API extern void enableInternalUi(bool enable);
extern void setup(IDirect3DDevice9* pDevice);
extern void render();
extern bool isRendering();
UTINNI_API extern void addRenderCallback(void(*func)());
UTINNI_API extern bool isInternalUiHovered();

}

namespace imgui_gizmo
{
UTINNI_API extern void enable(utinni::Object* obj);
UTINNI_API extern void disable();
UTINNI_API extern bool isEnabled();
UTINNI_API extern bool hasMouseHover();
UTINNI_API extern void addOnEnabledCallback(void(*func)());
UTINNI_API extern void addOnDisabledCallback(void(*func)());
UTINNI_API extern void addOnPositionChangedCallback(void(*func)());
UTINNI_API extern void addOnRotationChangedCallback(void(*func)());
UTINNI_API extern void toggleGizmoMode();
UTINNI_API extern void toggleOperationMode();
UTINNI_API extern void setGizmoModeToWorld();
UTINNI_API extern void setGizmoModeToLocal();
UTINNI_API extern bool isGizmoModeToLocal();
UTINNI_API extern bool isGizmoModeToWorld();
UTINNI_API extern void setOperationModeToTranslate();
UTINNI_API extern void setOperationModeToRotate();
UTINNI_API extern bool isOperationModeTransform();
UTINNI_API extern bool isOperationModeRotate();
UTINNI_API extern void toggleSnap();
UTINNI_API extern void enableSnap(bool value);
UTINNI_API extern bool isSnapOn();
UTINNI_API extern void setSnapSize(float value);

void draw();
}