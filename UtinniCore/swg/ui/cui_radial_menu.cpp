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
    if (imgui_gizmo::isEnabled())
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
