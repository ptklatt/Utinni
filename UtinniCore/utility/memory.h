#pragma once

#include "utinni.h"

namespace memory
{
extern swgptr findPattern(swgptr startAddress, size_t length, const char* pattern, const char* mask);
extern swgptr findPattern(const char* moduleName, const char* pattern, const char* mask);

template<typename T>
extern T read(swgptr address)
{
    if (address > 0)
    {
        return *(T*)address;
    }
    return T();
}

template<typename T>
extern T read(swgptr address, int offsetOfAddrResult)
{
    const swgptr resultAddress = read<swgptr>(address);
    if (resultAddress > 0)
    {
        return *(T*)(resultAddress + offsetOfAddrResult);
    }
    return T();
}

template<typename T>
extern void write(swgptr address, T value)
{
    if (address > 0)
    {
        *(T*)address = value;
    }
}

template<typename T>
extern void write(swgptr address, int offsetOfAddrResult, T value)
{
    const swgptr resultAddress = read<swgptr>(address);
    if (resultAddress > 0)
    {
        *(T*)(resultAddress + offsetOfAddrResult) = value;
    }
}

extern void write(swgptr address, swgptr value, int length);
extern void set(swgptr pDest, swgptr value, size_t length);

extern void patchAddress(swgptr address, swgptr value);
extern void nopAddress(swgptr address, int nopCount);

extern void createJMP(swgptr address, swgptr jumpToAddress, size_t overrideLength);

extern swgptr getAddress(swgptr baseAddress, int ptrDepth);
extern swgptr getAddress(swgptr baseAddress, std::vector<int>& offsets);

}

