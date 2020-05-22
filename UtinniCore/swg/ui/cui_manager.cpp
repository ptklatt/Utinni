#include "cui_manager.h"

namespace swg::cuiManager
{
using pSetSize = void(__cdecl*)(int width, int height);
using pTogglePointer = void(__cdecl*)(bool isOn);

pSetSize setSize = (pSetSize)0x00882410;
pTogglePointer togglePointer = (pTogglePointer)0x00881940;
    
}

namespace swg::uimanager
{
using pDrawCursor = void(__thiscall*)(utinni::UiManager* pThis, bool value);

pDrawCursor drawCursor = (pDrawCursor)0x010E8410;

}

namespace utinni
{
void CuiManager::setSize(int width, int height)
{
    swg::cuiManager::setSize(width, height);
}

void CuiManager::togglePointer(bool isOn)
{
    swg::cuiManager::togglePointer(isOn);
}

UiManager* UiManager::get()
{
    return memory::read<UiManager*>(0x1996E98);
}

void UiManager::drawCursor(bool value)
{
    swg::uimanager::drawCursor(this, value);
}

}
