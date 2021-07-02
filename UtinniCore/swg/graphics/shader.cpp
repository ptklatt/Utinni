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

#include "shader.h"
#include "swg/graphics/directx9.h"

namespace swg::shaderPrimitiveSorter
{

}

namespace utinni::shaderPrimitiveSorter
{


directX::DepthTexture* depthTexture;

int vecOffset = 0;
constexpr uint8_t phaseStructSize = 36;
constexpr swgptr midPopCell_Call = 0x772D60;
constexpr swgptr start_midPopCell = 0x00773E39;
constexpr swgptr return_midPopCell = 0x00773E41;
__declspec(naked) void midPopCell()
{
    __asm
    {
        mov vecOffset, esi
        pushad
        pushfd
        call midPopCell_Call
    }

    depthTexture = directX::getDepthTexture();
    if ((vecOffset / phaseStructSize) == depthTexture->getStage()) // divide offset by struct size to get stage
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


void detour()
{
    memory::createJMP(start_midPopCell, (swgptr)midPopCell, 6);
}
}