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
    if (imgui_gizmo::isEnabled())
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
