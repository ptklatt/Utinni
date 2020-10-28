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

#include "extent.h"

namespace swg::baseExtent
{
using pIntersect = bool(__thiscall*)(utinni::ExtentBase* pThis, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* normal, float* time);
using pIntersect3 = int(__thiscall*)(utinni::ExtentBase* pThis, swg::math::Vector* worldStart, swg::math::Vector* worldEnd);

pIntersect intersect = (pIntersect)0x0126AF70;
pIntersect3 intersect3 = (pIntersect3)0x0126AFB0;
}

namespace swg::extent
{
    
}

namespace swg::boxExtent
{
using pIntersect = bool(__thiscall*)(utinni::BoxExtent* pThis, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* surfaceNormal, float* time);

pIntersect intersect = (pIntersect)0x0125FA10;
}

namespace utinni
{
bool ExtentBase::intersect(swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* normal, float* time)
{
    bool result = swg::baseExtent::intersect3(this, worldStart, worldEnd);
    return false;
}

bool BoxExtent::realIntersect(swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* surfaceNormal, float* time)
{
    return swg::boxExtent::intersect(this, worldStart, worldEnd, surfaceNormal, time);
}
}
