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
UTINNI_API extern void setOperationModeToTranslate();
UTINNI_API extern void setOperationModeToRotate();
UTINNI_API extern void toggleSnap();
UTINNI_API extern void enableSnap(bool value);
UTINNI_API extern bool isSnapOn();
UTINNI_API extern void setSnapSize(float value);

void draw();
}