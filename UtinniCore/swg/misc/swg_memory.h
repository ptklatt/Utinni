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
#include <new>

namespace utinni
{
struct NewPlaceholder {};

UTINNI_API extern void* allocate(size_t size);
UTINNI_API extern void* allocateString(size_t size);

UTINNI_API extern void deallocate(void* address, size_t size);
UTINNI_API extern void deallocateString(void* address, size_t size);
 
}

inline void* operator new(size_t, utinni::NewPlaceholder, void* where) { return where; }

inline void operator delete(void*, utinni::NewPlaceholder, void*) { }

namespace utinni
{
template<class Type, class... Args>
UTINNI_API Type* swg_new(Args&&...args)
{
    return new (NewPlaceholder(), allocate(sizeof(Type))) Type(std::forward<Args>(args)...);
}

//template<class Type, class... Args>
//inline Type* swg_new(Args&&...args)
//{
//    Type* result = (Type*)allocateMemory(sizeof(Type));
//    return Type::get_ctor()(result, std::forward<Args>(args)...);
//}
}