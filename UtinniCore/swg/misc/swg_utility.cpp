#include "swg_utility.h"

namespace swg::utility
{
using pAllocateMemory = DWORD(__cdecl*)(size_t size);
using pCalculateCrc = unsigned int(__cdecl*)(const char* str);

pAllocateMemory allocateMemory = (pAllocateMemory)0x00AC15C0;
pCalculateCrc calculateCrc = (pCalculateCrc)0x00AA4790;

}

namespace utinni
{
DWORD allocateMemory(size_t size)
{
    return swg::utility::allocateMemory(size);
}

unsigned int calculateCrc(const char* string)
{
    return swg::utility::calculateCrc(string);
}
}