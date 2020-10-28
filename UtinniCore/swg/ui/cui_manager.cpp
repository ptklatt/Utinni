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

#include "cui_manager.h"
#include "swg/camera/camera.h"
#include "swg/misc/swg_string.h"

namespace swg::cuiManager
{
using pRender = void(__thiscall*)(swgptr pThis);
using pFindObjectUnderCursor = utinni::Object* (__cdecl*)(utinni::Camera* camera, math::Vector* worldStart, math::Vector* worldEnd, utinni::Object* player);

using pSetSize = void(__cdecl*)(int width, int height);
using pTogglePointer = void(__cdecl*)(bool isOn);

using pRestartMusic = void(__cdecl*)(bool notPlaying);

pRender render = (pRender)0x00881210;
pFindObjectUnderCursor findObjectUnderCursor = (pFindObjectUnderCursor)0x00BD3E20;

pSetSize setSize = (pSetSize)0x00882410;
pTogglePointer togglePointer = (pTogglePointer)0x00881940;

pRestartMusic restartMusic = (pRestartMusic)0x00881560;
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

void CuiManager::restartMusic()
{
    swg::cuiManager::restartMusic(true);
}

void __fastcall hkRender(swgptr pThis, void* useless)
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
