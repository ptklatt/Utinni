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

#include "swg_memory.h"

namespace swg::memory
{
using pAllocate = void* (__cdecl*)(size_t size);
using pAllocateString = void* (__cdecl*)(size_t size);

using pDeallocate = void (__cdecl*)(void* address, size_t size);
using pDeallocateString = void (__cdecl*)(void* address, size_t size);

pAllocate allocate = (pAllocate)0x00AC15C0;
pAllocateString allocateString = (pAllocateString)0x012EA770;

pDeallocate deallocate = (pDeallocate)0x00AC1640;
pDeallocateString deallocateString = (pDeallocateString)0x012EA920;
}

namespace utinni
{
void* allocate(size_t size)
{
    return swg::memory::allocate(size);
}

void* allocateString(size_t size)
{
    return swg::memory::allocateString(size);
}

void deallocate(void* address, size_t size)
{
    swg::memory::deallocate(address, size);
}

void deallocateString(void* address, size_t size)
{
    swg::memory::deallocateString(address, size);
}
}
