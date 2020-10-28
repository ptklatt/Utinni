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

#pragma once

#include "utinni.h"
#include "swg/misc/crc_string.h"
#include "swg/misc/swg_math.h"
#include "swg/object/object.h"
#include "extent.h"

namespace utinni
{
class Object;
class ClientObject;

struct UTINNI_API Hardpoint
{
    utinni::PersistentCrcString name;
    swg::math::Transform Transform;
};

class UTINNI_API AppearanceTemplate
{
public:
    swgptr vtbl;
    int referenceCount;
    PersistentCrcString* const m_crcName;
    swgptr unk01;
    swgptr unk02;
    std::vector<Hardpoint*, std::allocator<Hardpoint*>>* hardpoints;
    char* floorName;
    swgptr unk03;
};

class UTINNI_API Appearance
{
public:
    swgptr vtbl;
    AppearanceTemplate* appearanceTemplate;
    swgptr unk;
    Object* ownerObject;
    int renderedFrameCount;
    swg::math::Vector scale;
    bool keepAlive;
    bool useRenderEffectsFlag;
    bool allowShadowBlob;
    swg::math::Transform appearanceToWorld;

    static Appearance* create(const char* filename);

    BoxExtent* getExtent();
};

class UTINNI_API ParticleEffectAppearance : public Appearance
{
public:
    bool collide(swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swgptr unk, utinni::CollisionInfo& collisionResults);
    static void detour();;
};


}
