#include "swg_utility.h"

namespace swg::utility
{
using pAllocateMemory = DWORD(__cdecl*)(size_t size);
using pCalculateCrc = unsigned int(__cdecl*)(const char* str);
using pTreeFileOpen = DWORD(__cdecl*)(const char* filename, int priorityType, bool allowFail);

pAllocateMemory allocateMemory = (pAllocateMemory)0x00AC15C0;
pCalculateCrc calculateCrc = (pCalculateCrc)0x00AA4790;
pTreeFileOpen treeFileOpen = (pTreeFileOpen)0x00A931E0;

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

DWORD treeFileOpen(const char* filename, int priorityType, bool allowFail)
{
    return swg::utility::treeFileOpen(filename, priorityType, allowFail);
}

}
