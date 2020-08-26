#include "cui_manager.h"
#include "swg/camera/camera.h"
#include "swg/misc/swg_string.h"

namespace swg::cuiManager
{
using pRender = void(__thiscall*)(DWORD* pThis);
using pFindObjectUnderCursor = utinni::Object* (__cdecl*)(utinni::Camera* camera, math::Vector* worldStart, math::Vector* worldEnd, utinni::Object* player);

using pSetSize = void(__cdecl*)(int width, int height);
using pTogglePointer = void(__cdecl*)(bool isOn);

pRender render = (pRender)0x00881210;
pFindObjectUnderCursor findObjectUnderCursor = (pFindObjectUnderCursor)0x00BD3E20;

pSetSize setSize = (pSetSize)0x00882410;
pTogglePointer togglePointer = (pTogglePointer)0x00881940;
    
}

namespace swg::uiManager
{
using pDrawCursor = void(__thiscall*)(utinni::UiManager* pThis, bool value);

pDrawCursor drawCursor = (pDrawCursor)0x010E8410;

}

namespace swg::systemMessageManager
{
using pSendMessage = void(__cdecl*)(const swg::WString& message, bool chatOnly);

pSendMessage sendMessage = (pSendMessage)0x008AC250;

}

namespace utinni
{
bool isRenderingUi = false;
bool hasObjectUnderCursor = false;

void CuiManager::setSize(int width, int height)
{
    swg::cuiManager::setSize(width, height);
}

void CuiManager::togglePointer(bool isOn)
{
    swg::cuiManager::togglePointer(isOn);
}

bool CuiManager::isRenderingUi()
{
    return utinni::isRenderingUi;
}

bool CuiManager::hasObjectUnderCursor()
{
    return utinni::hasObjectUnderCursor;
}

void __fastcall hkRender(DWORD* pThis, void* useless)
{
    isRenderingUi = true;
    swg::cuiManager::render(pThis);
    isRenderingUi = false;
}

Object* __cdecl hkFindObjectUnderCursor(Camera* camera, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, Object* player)
{
    Object* result = swg::cuiManager::findObjectUnderCursor(camera, worldStart, worldEnd, player);

    hasObjectUnderCursor = result != nullptr;

    return result;
}

void CuiManager::detour()
{
    swg::cuiManager::render = (swg::cuiManager::pRender)Detour::Create(swg::cuiManager::render, hkRender, DETOUR_TYPE_PUSH_RET);
    swg::cuiManager::findObjectUnderCursor = (swg::cuiManager::pFindObjectUnderCursor)Detour::Create(swg::cuiManager::findObjectUnderCursor, hkFindObjectUnderCursor, DETOUR_TYPE_PUSH_RET);
}

UiManager* UiManager::get()
{
    return memory::read<UiManager*>(0x1996E98);
}

void UiManager::drawCursor(bool value)
{
    swg::uiManager::drawCursor(this, value);
}

void SystemMessageManager::sendMessage(const char* message, bool chatOnly)
{
    swg::systemMessageManager::sendMessage(swg::WString(message), chatOnly);
}
}
