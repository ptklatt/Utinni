#include "cui_hud.h"
#include "swg/ui/imgui_implementation.h"

namespace swg::cuiHud
{
using pActionPerformAction = bool(__thiscall*)(DWORD pThis, DWORD val1, DWORD val2);

pActionPerformAction actionPerformAction = (pActionPerformAction)0x00EDBAA0;

}

namespace utinni
{
bool __fastcall hkActionPerformAction(DWORD pThis, DWORD EDX, DWORD val1, DWORD val2)
{
    if (imgui::gizmo::hasMouseHover())
    {
        return false;
    }

    return swg::cuiHud::actionPerformAction(pThis, val1, val2);
}

void cuiHud::detour()
{
    swg::cuiHud::actionPerformAction = (swg::cuiHud::pActionPerformAction)Detour::Create((LPVOID)swg::cuiHud::actionPerformAction, hkActionPerformAction, DETOUR_TYPE_PUSH_RET);
}

}
