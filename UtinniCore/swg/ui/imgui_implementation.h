#pragma once

#include <d3d9.h>
#include "utinni.h"

namespace utinni
{
    class Object;
}

namespace imgui_implementation
{
extern void enableInternalUi(bool enable);
extern void setup(IDirect3DDevice9* pDevice);
extern void render();
extern void addRenderCallback(void(*func)());
UTINNI_API extern bool isInternalUiHovered();

}

namespace imgui::gizmo
{
void enable(utinni::Object* obj);
void disable();
void draw();
}