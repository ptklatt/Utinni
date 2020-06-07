#pragma once

#include "utinni.h"

namespace memory
{
extern DWORD findPattern(DWORD startAddress, DWORD fileSize, const char* pattern, const char* mask);
extern DWORD FindPattern(const char* moduleName, const char* pattern, const char* mask);

template<typename T>
extern T read(DWORD address)
{
    if (address > 0)
    {
        return *(T*)address;
    }
    return T();
}

template<typename T>
extern T read(DWORD address, int offsetOfAddrResult)
{
    const int resultAddress = *(int*)address;
    if (resultAddress > 0)
    {
        return *(T*)(resultAddress + offsetOfAddrResult);
    }
    return T();
}

template<typename T>
extern void write(DWORD address, T value)
{
    if (address > 0)
    {
        *(T*)address = value;
    }
}

template<typename T>
extern void write(int address, int offsetOfAddrResult, T value)
{
    const int resultAddress = *(int*)address;
    if (resultAddress > 0)
    {
        *(T*)(resultAddress + offsetOfAddrResult) = value;
    }
}

extern void write(DWORD address, void* value, int length);
extern void set(DWORD address, DWORD value, int size);

extern void patchAddress(DWORD address, DWORD value);
extern void nopAddress(DWORD address, int nopCount);

extern void createJMP(PBYTE address, DWORD jumpToAddress, DWORD overrideLength);

extern DWORD getAddress(DWORD baseAddress, int ptrDepth);
extern DWORD getAddress(DWORD baseAddress, std::vector<int>& offsets);

}

