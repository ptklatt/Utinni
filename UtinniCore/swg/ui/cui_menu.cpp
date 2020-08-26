#include "cui_menu.h"
#include "swg/ui/imgui_impl.h"
#include "swg/object/client_object.h"

namespace swg::cuiMenu
{
using pInfoTypesFindDefaultCursor = swgptr(__cdecl*)(utinni::ClientObject* obj);

pInfoTypesFindDefaultCursor infoTypesFindDefaultCursor = (pInfoTypesFindDefaultCursor)0x00A08EE0;

}

namespace utinni
{
swgptr __cdecl hkInfoTypesFindDefaultCursor(ClientObject* obj)
{
    if (imgui::gizmo::isEnabled())
    {
        return 0;
    }

    return swg::cuiMenu::infoTypesFindDefaultCursor(obj);
}

void cuiMenu::detour()
{
    swg::cuiMenu::infoTypesFindDefaultCursor = (swg::cuiMenu::pInfoTypesFindDefaultCursor)Detour::Create((LPVOID)swg::cuiMenu::infoTypesFindDefaultCursor, hkInfoTypesFindDefaultCursor, DETOUR_TYPE_PUSH_RET);
}

}
