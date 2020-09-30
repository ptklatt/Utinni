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
UTINNI_API extern void addRenderCallback(void(*func)());
UTINNI_API extern bool isInternalUiHovered();

}

namespace imgui_gizmo
{
UTINNI_API extern void enable(utinni::Object* obj);
UTINNI_API extern void disable();
UTINNI_API extern bool isEnabled();
UTINNI_API bool hasRecentPositionChange();
UTINNI_API bool hasRecentRotationChange();
UTINNI_API extern bool hasMouseHover();
UTINNI_API extern void addOnPositionChangedCallback(void(*func)());
UTINNI_API extern void addOnRotationChangedCallback(void(*func)());
UTINNI_API extern void toggleOperationMode();
UTINNI_API extern void toggleSnap();

void draw();
}