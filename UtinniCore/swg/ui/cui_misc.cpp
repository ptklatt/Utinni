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

#include "cui_misc.h"

namespace swg::cuiMisc
{
using pSwgCuiHudFactoryReloadUi = void(__cdecl*)();

pSwgCuiHudFactoryReloadUi swgCuiHudFactoryReloadUi = (pSwgCuiHudFactoryReloadUi)0x00BAA7E0;
}

namespace utinni::cuiMisc
{
void reloadUi()
{
    memory::write<bool>(0x01926138, true); // Todo what is this again?
    swg::cuiMisc::swgCuiHudFactoryReloadUi();
}

void patch()
{
    if (getConfig().getBool("UtinniCore", "enableOfflineScenes"))
    {
        // Enable the Load Scene button inside the login screen
        memory::nopAddress(0x00C8D250, 15);

        // Enable the Location button inside the ESC menu inside a scene
        static constexpr byte locationBtnPatchBuffer[] = { 0x6A, 0x01, // push 1
                                          0x51, // push ecx
                                          0x8B, 0xCE, // mov ecx, esi
                                          0xE8, 0x17, 0x43, 0xD4, 0xFF }; // call client.9C18A0
        memory::copy(0x00C7D57F, locationBtnPatchBuffer);


        // Disable the CUI resize based on RESO chunk in settings
        memory::nopAddress(0x009CC385, 6); // Removes RESO.Y changing CUI.X
        memory::nopAddress(0x009CC39C, 5); // Removes RESO.Y changing CUI.Y
        memory::nopAddress(0x009CC3BD, 3); // Removes isOk bool being set to false
    }
}
}