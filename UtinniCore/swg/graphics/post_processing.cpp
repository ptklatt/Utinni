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

#include "post_processing.h"

namespace swg::bloom
{
using pPreSceneRender = void(__cdecl*)();
using pPostSceneRender = void(__cdecl*)();

pPreSceneRender preSceneRender = (pPreSceneRender)0x0064B500;
pPostSceneRender postSceneRender = (pPostSceneRender)0x0064B560;

}

static std::vector<void(*)()> preSceneRenderCallbacks;
static std::vector<void(*)()> postSceneRenderCallbacks;

namespace utinni::postProcessing
{
void __cdecl hkPreSceneRender() // Originally a Bloom class function, repurposed to be a general PostProcessing function.
{
    for (const auto& func : preSceneRenderCallbacks)
    {
        func();
    }

    swg::bloom::preSceneRender();
}

void __cdecl hkPostSceneRender() // Originally a Bloom class function, repurposed to be a general PostProcessing function.
{
    swg::bloom::postSceneRender();

    for (const auto& func : postSceneRenderCallbacks)
    {
        func();
    }
}

void addPreSceneRenderCallback(void(* func)())
{
    preSceneRenderCallbacks.emplace_back(func);
}

void addPostSceneRenderCallback(void(* func)())
{
    postSceneRenderCallbacks.emplace_back(func);
}

void detour()
{
    swg::bloom::preSceneRender = (swg::bloom::pPreSceneRender)Detour::Create(swg::bloom::preSceneRender, hkPreSceneRender, DETOUR_TYPE_PUSH_RET);
    swg::bloom::postSceneRender = (swg::bloom::pPostSceneRender)Detour::Create(swg::bloom::postSceneRender, hkPostSceneRender, DETOUR_TYPE_PUSH_RET);

}
}