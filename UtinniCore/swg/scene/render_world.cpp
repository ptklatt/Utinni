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

#include "render_world.h"
#include "swg/graphics/directx9.h"

namespace swg::renderWorld
{
using pAddObjectNotifications = void(__cdecl*)(utinni::Object* obj);
pAddObjectNotifications addObjectNotifications = (pAddObjectNotifications)0x007664F0;

using pRender = void(__cdecl*)(swgptr pCamera);
pRender render = (pRender)0x00766DE0;

using pClearVisibleCells = void(__cdecl*)();
pClearVisibleCells clearVisibleCells = (pClearVisibleCells)0x765C20;
}

namespace utinni::renderWorld
{
void addObjectNotifications(Object* obj)
{
    swg::renderWorld::addObjectNotifications(obj);
}

directX::DepthTexture* depthTexture;

swgptr pCall = 0x772D60;
int listOffset = 0;
swgptr start_midPopCell = 0x00773E39;
swgptr return_midPopCell = 0x00773E41;
__declspec(naked) void midPopCell()
{
    __asm
    {
        mov listOffset, esi
        pushad
        pushfd
        call pCall
    }

    depthTexture = directX::getDepthTexture();

    if (listOffset / 36 == depthTexture->getStage()) // 36 is struct size, divide to get stage
    {
        if (depthTexture != nullptr && depthTexture->isSupported() && depthTexture->getTextureDepth() != nullptr)
        {
            depthTexture->resolveDepth();
        }
    }

    __asm
    {
        popfd
        popad
        add esi, 0x24
        jmp[return_midPopCell]
    }
}

void __cdecl hkRender(swgptr pCamera)
{
    swg::renderWorld::render(pCamera);

    //depthTexture = directX::getDepthTexture();
    //if (depthTexture != nullptr && depthTexture->isSupported() && depthTexture->getTexture() != nullptr)
    //{
    //    depthTexture->resolveDepth();
    //    //utinni::log::info("Test");
    //}
}

void __cdecl hkClearVisibleCells()
{
    swg::renderWorld::clearVisibleCells();

    depthTexture = directX::getDepthTexture();
    if (depthTexture != nullptr && depthTexture->isSupported() && depthTexture->getTextureDepth() != nullptr)
    {
        depthTexture->resolveDepth();
        //utinni::log::info("Test");
    }

}

void detour()
{
    //swg::renderWorld::render = (swg::renderWorld::pRender)Detour::Create(swg::renderWorld::render, hkRender, DETOUR_TYPE_PUSH_RET);
    //swg::renderWorld::clearVisibleCells = (swg::renderWorld::pClearVisibleCells)Detour::Create(swg::renderWorld::clearVisibleCells, hkClearVisibleCells, DETOUR_TYPE_PUSH_RET);
    memory::createJMP(start_midPopCell, (swgptr)midPopCell, 6);
  
}
}
