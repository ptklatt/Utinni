#pragma once

#include "utinni.h"
#include <new>

namespace utinni
{
extern DWORD allocateMemory(size_t size);

extern unsigned int calculateCrc(const char* string);

extern DWORD treeFileOpen(const char* filename, int priorityType, bool allowFail);

}

namespace utinni
{
struct NewPlaceholder {};
}

inline void* operator new(size_t, utinni::NewPlaceholder, void* where)
{
    return where;
}

inline void operator delete(void*, utinni::NewPlaceholder, void*)
{
}

namespace utinni
{
//template<class Type, class... Args>
//Type* swg_new(Args&&...args)
//{
//    //return new (NewPlaceholder(), allocateMemory(sizeof(Type)), ctor) Type ctor();
//    
//    return new (sizeof(Type), NewPlaceholder(), allocateMemory(sizeof(Type))) Type(std::forward<Args>(args)...);
//}
//
template<class Type>
Type* swg_new()
{
    //return new (NewPlaceholder(), allocateMemory(sizeof(Type)), ctor) Type ctor();

    return new (NewPlaceholder(), allocateMemory(sizeof(Type))) Type;
}
}