#include "cui_hud.h"
#include "swg/ui/imgui_impl.h"

namespace swg::cuiHud
{
using pUpdate = void(__thiscall*)(swgptr pThis, float time);
using pActionPerformAction = bool(__thiscall*)(swgptr pThis, DWORD val1, DWORD val2);

pUpdate update = (pUpdate)0x00BD56F0;
pActionPerformAction actionPerformAction = (pActionPerformAction)0x00EDBAA0;

}

namespace utinni::cuiHud
{
Object* targetUnderCursor;

void __fastcall hkUpdate(swgptr pThis, float time)
{
    swg::cuiHud::update(pThis, time);
}

bool __fastcall hkActionPerformAction(swgptr pThis, DWORD EDX, DWORD val1, DWORD val2)
{
    if (imgui_gizmo::hasMouseHover())
    {
        return false;
    }

    return swg::cuiHud::actionPerformAction(pThis, val1, val2);
}

swgptr jmpToTarget_midUpdate = 0x00BD5961;
swgptr return_midUpdate = 0x00BD595C;
__declspec(naked) void midUpdate()
{
    swgptr pTargetUnderCursor;
    __asm
    {
        mov pTargetUnderCursor, ecx
        pushad
        pushfd
    }

    targetUnderCursor = (Object*)pTargetUnderCursor;
    
    __asm
    {
        popfd
        popad
        test eax, eax
        jz jumpToTarget
        mov targetUnderCursor, 0
        push edi
        lea ecx, [0x84 + eax]
        jmp[return_midUpdate]

        jumpToTarget:
        jmp[jmpToTarget_midUpdate]
    }
}


void detour()
{
    //swg::cuiHud::update = (swg::cuiHud::pUpdate)Detour::Create((LPVOID)swg::cuiHud::update, hkUpdate, DETOUR_TYPE_PUSH_RET);
    swg::cuiHud::actionPerformAction = (swg::cuiHud::pActionPerformAction)Detour::Create((LPVOID)swg::cuiHud::actionPerformAction, hkActionPerformAction, DETOUR_TYPE_PUSH_RET);

    //memory::createJMP(0x00BD5951, (swgptr)midUpdate, 6); // Mid CuiHud::update detour
}

}
