#pragma once

#include "utinni.h"

namespace memory
{
template<typename T>
T read(DWORD address)
{
    if (address > 0)
    {
        return *(T*)address;
    }
    return T();
}

template<typename T>
T read(DWORD address, int offsetOfAddrResult)
{
    const int resultAddress = *(int*)address;
    if (resultAddress > 0)
    {
        return *(T*)(resultAddress + offsetOfAddrResult);
    }
    return T();
}

template<typename T>
void write(DWORD address, T value)
{
    if (address > 0)
    {
        *(T*)address = value;
    }
}

template<typename T>
void write(int address, int offsetOfAddrResult, T value)
{
    const int resultAddress = *(int*)address;
    if (resultAddress > 0)
    {
        *(T*)(resultAddress + offsetOfAddrResult) = value;
    }
}

void write(DWORD address, void* value, int length);
void set(DWORD address, DWORD value, int size);

void patchAddress(DWORD address, DWORD value);
void nopAddress(DWORD address, int nopCount);

void createJMP(PBYTE address, DWORD jumpToAddress, DWORD overrideLength);

DWORD getAddress(DWORD baseAddress, int ptrDepth);
DWORD getAddress(DWORD baseAddress, std::vector<int>& offsets);

}

