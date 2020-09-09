#include "cui_hud.h"
#include "swg/ui/imgui_impl.h"
#include "swg/misc/swg_misc.h"
#include "swg/camera/camera.h"
#include "swg/scene/client_world.h"

namespace swg::cuiHud
{
using pUpdate = void(__thiscall*)(swgptr pThis, float time);
using pActionPerformAction = bool(__thiscall*)(swgptr pThis, DWORD val1, DWORD val2);
using pGetTarget = utinni::Object* (__cdecl*)(utinni::Camera* pCamera, math::Vector* worldStart, math::Vector* worldEnd, utinni::Object* pObject);

pUpdate update = (pUpdate)0x00BD56F0;
pActionPerformAction actionPerformAction = (pActionPerformAction)0x00EDBAA0;
pGetTarget getTarget = (pGetTarget)0x00BD3E20;

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


static swg::math::Vector cursorWorldPos;
Object* __cdecl hkGetTarget(utinni::Camera* pCamera, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, Object* pObject)
{
    static constexpr uint16_t flags = (1 | 128 | 4096); // terrain | child objects | disable portal crossing
    CollisionInfo collisionResults;
    if (clientWorld::collide(pCamera->getParentCell(), worldStart, worldEnd, collisionResults, flags, pObject))
    {
        cursorWorldPos = swg::math::Vector(collisionResults.point);
    }

    return swg::cuiHud::getTarget(pCamera, worldStart, worldEnd, pObject);
}

static constexpr swgptr jmpToTarget_midUpdate = 0x00BD5961;
static constexpr swgptr return_midUpdate = 0x00BD595C;
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

const swg::math::Vector& getCursorWorldPosition()
{
    return cursorWorldPos;
}

void patchAllowTargetEverything(bool value)
{
    if (value)
    {
        memory::createJMP(0x00BD3FA3, 0x00BD403D, 5);
    }
    else
    {
        static constexpr byte originalBytes[] = { 0x8B, 0xCE, 0xE8, 0x76, 0xF9 }; // call client.9C18A0
        memory::copy(0x00BD3FA3, originalBytes);
    }
}

void detour()
{
    //swg::cuiHud::update = (swg::cuiHud::pUpdate)Detour::Create((LPVOID)swg::cuiHud::update, hkUpdate, DETOUR_TYPE_PUSH_RET);
    swg::cuiHud::actionPerformAction = (swg::cuiHud::pActionPerformAction)Detour::Create((LPVOID)swg::cuiHud::actionPerformAction, hkActionPerformAction, DETOUR_TYPE_PUSH_RET);
    swg::cuiHud::getTarget = (swg::cuiHud::pGetTarget)Detour::Create((LPVOID)swg::cuiHud::getTarget, hkGetTarget, DETOUR_TYPE_PUSH_RET, 5);

    //memory::createJMP(0x00BD5951, (swgptr)midUpdate, 6); // Mid CuiHud::update detour
}

}
