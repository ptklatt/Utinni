#include "cui_io.h"
#include "swg/ui/imgui_impl.h"

namespace swg::cuiIo
{
using pProcessEvent = swgptr(__thiscall*)(swgptr pThis, swgptr pEvent);
using pSetKeyboardInputActive = swgptr(__thiscall*)(swgptr pThis, bool value);
using pRequestKeyboard = swgptr(__thiscall*)(swgptr pThis, bool value);

pProcessEvent processEvent = (pProcessEvent)0x093BD50;
pSetKeyboardInputActive setKeyboardInputActive = (pSetKeyboardInputActive)0x0093D490;
pRequestKeyboard requestKeyboard = (pRequestKeyboard)0x0093D560;

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

void cuiIo::detour()
{
   swg::cuiIo::processEvent = (swg::cuiIo::pProcessEvent)Detour::Create((LPVOID)swg::cuiIo::processEvent, hkProcessEvent, DETOUR_TYPE_PUSH_RET);
}

}
