#include "cui_radial_menu.h"
#include "swg/ui/imgui_impl.h"

namespace swg::cuiRadialMenuManager
{
using pUpdate = void(__cdecl*)();
using pClear = void(__cdecl*)();

pUpdate update = (pUpdate)0x009698C0;
pClear clear = (pClear)0x0096C550;

}

namespace utinni
{
void __cdecl hkUpdate()
{
    if (imgui::gizmo::isEnabled())
    {
        swg::cuiRadialMenuManager::clear();
    }

    swg::cuiRadialMenuManager::update();
}

void cuiRadialMenuManager::detour()
{
    swg::cuiRadialMenuManager::update = (swg::cuiRadialMenuManager::pUpdate)Detour::Create((LPVOID)swg::cuiRadialMenuManager::update, hkUpdate, DETOUR_TYPE_PUSH_RET);
}

}
