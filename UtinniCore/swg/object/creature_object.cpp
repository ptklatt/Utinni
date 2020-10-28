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

#include "creature_object.h"
#include "swg/object/object.h"
#include "swg/misc/network.h"

namespace swg::creatureObject
{
using pSetTarget = void(__thiscall*)(swgptr pThis, const int64_t& id);

pSetTarget setTarget = (pSetTarget)0x00434AB0;
}

static std::vector<void(*)(utinni::Object* target)> onTargetCallbacks;

namespace utinni::creatureObject
{

void addOnTargetCallback(void(*func)(Object* target))
{
    onTargetCallbacks.emplace_back(func);
}

void __fastcall hkSetTarget(swgptr pThis, DWORD EDX, const int64_t& id)
{
    swg::creatureObject::setTarget(pThis, id);

    Object* obj = Network::getObjectById(id);

    for (const auto& func : onTargetCallbacks)
    {
        func(obj);
    }
}

void detour()
{
    swg::creatureObject::setTarget = (swg::creatureObject::pSetTarget)Detour::Create(swg::creatureObject::setTarget, hkSetTarget, DETOUR_TYPE_PUSH_RET);
}
;
}