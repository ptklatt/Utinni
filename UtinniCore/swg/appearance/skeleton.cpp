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

#include "skeleton.h"


namespace swg::skeleton
{
using pAddShaderPrimitives = void(__thiscall*)(swgptr pThis, swgptr pSkeletalAppearance);

pAddShaderPrimitives addShaderPrimitives = (pAddShaderPrimitives)0x007E6C50;
}

namespace swg::skeletalAppearance
{
using pRender = void(__thiscall*)(swgptr pThis);
using pGetDisplayLodSkeleton = swgptr(__thiscall*)(swgptr pThis);

pRender render = (pRender)0x007C8B60;
pGetDisplayLodSkeleton getDisplayLodSkeleton = (pGetDisplayLodSkeleton)0x007CA130;
}

namespace utinni
{

namespace skeletalAppearance
{
bool renderSkeleton = false;

void setRenderSkeleton(bool value)
{
    renderSkeleton = value;
}

void __fastcall hkRender(swgptr pThis)
{
    swg::skeletalAppearance::render(pThis);

    if (renderSkeleton)
    {
        swgptr pSkeleton = swg::skeletalAppearance::getDisplayLodSkeleton(pThis);
        if (pSkeleton != 0)
        {
            swg::skeleton::addShaderPrimitives(pSkeleton, pThis);
        }
    }
}
void detour()
{
    swg::skeletalAppearance::render = (swg::skeletalAppearance::pRender)Detour::Create(swg::skeletalAppearance::render, hkRender, DETOUR_TYPE_PUSH_RET);
}

}

}