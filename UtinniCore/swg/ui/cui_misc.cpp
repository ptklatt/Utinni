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
#include "ui_textbox.h"
#include <fstream>

namespace swg::cuiMisc
{
using pSwgCuiHudFactoryReloadUi = void(__cdecl*)();

pSwgCuiHudFactoryReloadUi swgCuiHudFactoryReloadUi = (pSwgCuiHudFactoryReloadUi)0x00BAA7E0;
}

namespace swg::cuiLoginScreen
{
using pCtor = swgptr(__thiscall*)(swgptr pThis, swgptr unk);
using pActivate = void(__thiscall*)(swgptr pThis);
using pLogin = void(__thiscall*)(swgptr pThis);

pCtor ctor = (pCtor)0x00C8CE00;
pActivate activate = (pActivate)0x00C8D190;
pLogin login = (pLogin)0x00C8D5D0;

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

namespace utinni::cuiLoginScreen
{
swgptr pLoginScreen;

swgptr __fastcall hkCtor(swgptr pThis, DWORD EDX, swgptr unk)
{
    pLoginScreen = swg::cuiLoginScreen::ctor(pThis, unk);
    return pLoginScreen;
}

void __fastcall hkActivate(swgptr pThis)
{
    swg::cuiLoginScreen::activate(pThis);

    // ToDo get it more proper at some point
    UiTextbox* txtUsername = memory::read<UiTextbox*>(pThis + 0xA0);
    UiTextbox* txtPassword = memory::read<UiTextbox*>(pThis + 0xA4);

    // ToDo add an option to auto fill data without auto login
    if (!getConfig().getBool("UtinniCore", "autoLoadScene") && getConfig().getBool("UtinniCore", "autoLogin"))
    {
        txtUsername->setLocalText(getConfig().getString("UtinniCore", "autoLoginUsername").c_str());

        // ToDo absolutely WIP, currently stored in plaintext, store with simple encryption to not leave a plaintext password on disk
        std::fstream infile(getPath() + "autoLoginData", std::fstream::in | std::fstream::out | std::fstream::app);
        if (infile.good())
        {
            std::string line;
            getline(infile, line);

            // ToDo Store multiple encrypted passwords with associated usernames in file and then look up the correct password to decrypt and enter, based on autoLoginUsername

            txtPassword->setLocalText(line.c_str());
        }
        infile.close();

        swg::cuiLoginScreen::login(pThis);
    }
}

void detour()
{
   swg::cuiLoginScreen::ctor = (swg::cuiLoginScreen::pCtor)Detour::Create(swg::cuiLoginScreen::ctor, hkCtor, DETOUR_TYPE_PUSH_RET);
   swg::cuiLoginScreen::activate = (swg::cuiLoginScreen::pActivate)Detour::Create(swg::cuiLoginScreen::activate, hkActivate, DETOUR_TYPE_PUSH_RET);
}

}
