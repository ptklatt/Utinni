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