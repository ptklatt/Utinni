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
