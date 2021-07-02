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

#include "cui_io.h"
#include "swg/ui/imgui_impl.h"

namespace swg::cuiIo
{
using pProcessEvent = swgptr(__thiscall*)(swgptr pThis, swgptr pEvent);
using pSetKeyboardInputActive = swgptr(__thiscall*)(swgptr pThis, bool value);
using pRequestKeyboard = swgptr(__thiscall*)(swgptr pThis, bool value);
using pDraw = void(__thiscall*)(swgptr pThis);


pProcessEvent processEvent = (pProcessEvent)0x093BD50;
pSetKeyboardInputActive setKeyboardInputActive = (pSetKeyboardInputActive)0x0093D490;
pRequestKeyboard requestKeyboard = (pRequestKeyboard)0x0093D560;
pDraw draw = (pDraw)0x0093B2B0;

}

namespace utinni
{
bool oldIsKeyboardEnabled;
bool isKeyboardEnabled = true;
 
enum EventTypes
{
    KeyCharacter = 6,
    KeyDown = 7,
    KeyUp = 8
};

swgptr cuiIo::get()
{
    return memory::read<swgptr>(0x192613C); // Static CuiIo ptr
}

void cuiIo::enableKeyboard(bool value)
{
    oldIsKeyboardEnabled = isKeyboardEnabled;
    isKeyboardEnabled = value;
}

void cuiIo::restorePreviousEnableKeyboardValue()
{
    // ToDo this can get broken somehow when called from .NET, figure out why. Use enableKeyboard(true) for now
    isKeyboardEnabled = true;
}

bool cuiIo::isInputBlocked()
{
    return !isKeyboardEnabled;
}

swgptr __fastcall hkProcessEvent(swgptr pThis, swgptr EDX, swgptr pEvent)
{
    const int eventType = memory::read<int>(pEvent + 4);
    if ((eventType == 6 || eventType == 7) && !isKeyboardEnabled)
    {
        return 0;
    }

    return swg::cuiIo::processEvent(pThis, pEvent);
}

void __fastcall hkDraw(swgptr pThis, swgptr EDX)
{
    swg::cuiIo::draw(pThis);
}

void cuiIo::detour()
{
   swg::cuiIo::processEvent = (swg::cuiIo::pProcessEvent)Detour::Create((LPVOID)swg::cuiIo::processEvent, hkProcessEvent, DETOUR_TYPE_PUSH_RET);
   //swg::cuiIo::draw = (swg::cuiIo::pDraw)Detour::Create((LPVOID)swg::cuiIo::draw, hkDraw, DETOUR_TYPE_PUSH_RET);
}

}
