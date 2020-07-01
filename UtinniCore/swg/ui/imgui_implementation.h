#pragma once

#include <d3d9.h>

namespace imgui_implementation
{
extern void enableInternalUi(bool enable);
extern void setup(IDirect3DDevice9* pDevice);
extern void render();
extern void addRenderCallback(void(*func)());

}
