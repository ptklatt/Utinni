#include "swg_utility.h"

namespace swg::utility
{
using pCalculateCrc = unsigned int(__cdecl*)(const char* str);

pCalculateCrc calculateCrc = (pCalculateCrc)0x00AA4790;

}

namespace utinni
{
DWORD allocateMemory(size_t size)
{
    uint32_t _size = size;
    DWORD pCallAllocteMem = 0x00AC15C0;
    DWORD pAllocatedMem;
    __asm
    {
        push _size
        call pCallAllocteMem
        mov pAllocatedMem, eax
    }
    return pAllocatedMem;
}

unsigned int calculateCrc(const char* string)
{
    return swg::utility::calculateCrc(string);
}
}