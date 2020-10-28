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

#include "network.h"
#include "swg/object/object.h"

namespace swg::network
{
// 00B37F30 -- NetworkIdManager & NetworkIdManager::getInstance ()
using pIdManagerGetObjectById = utinni::Object* (__cdecl*)(const int64_t& id);
using pIdManagerGetInstance = swgptr(__cdecl*)();

using pCachedNetworkIdGetObject = utinni::Object* (__thiscall*)(swgptr pThis); // pThis = CachedNetworkId, should be 8 bytes?

using pCast = int64_t(__thiscall*)(swgptr*, int, int);

pIdManagerGetObjectById idManagerGetObjectById = (pIdManagerGetObjectById)0x00B380E0;
pIdManagerGetInstance idManagerGetInstance = (pIdManagerGetInstance)0x00B37F30;


pCachedNetworkIdGetObject cachedNetworkIdGetObject = (pCachedNetworkIdGetObject)0x00B30160;

pCast cast = (pCast)0xAA4900;
}

namespace utinni
{

swgptr Network::getManger()
{
    return swg::network::idManagerGetInstance(); // See if this needs to be read
}

Object* Network::getObjectById(const int64_t& id)
{
    return swg::network::idManagerGetObjectById(id);
}

Object* Network::getCachedObjectById(swgptr pCachedNetworkId)
{
    return swg::network::cachedNetworkIdGetObject(pCachedNetworkId);
}

int64_t Network::cast(int id)
{
    swgptr networkId; // This is broken
    return swg::network::cast(&networkId, id, (id >> 32));;
}


}

