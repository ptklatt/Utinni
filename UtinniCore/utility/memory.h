#pragma once

#include "utinni.h"

namespace memory
{
UTINNI_API extern swgptr findPattern(swgptr startAddress, size_t length, const char* pattern, const char* mask);
UTINNI_API extern swgptr findPattern(const char* moduleName, const char* pattern, const char* mask);

template<typename T>
UTINNI_API extern T read(swgptr address)
{
    if (address > 0)
    {
        return *(T*)address;
    }
    return T();
}

template<typename T>
UTINNI_API extern T read(swgptr address, int offsetOfAddrResult)
{
    const swgptr resultAddress = read<swgptr>(address);
    if (resultAddress > 0)
    {
        return *(T*)(resultAddress + offsetOfAddrResult);
    }
    return T();
}

template<typename T>
UTINNI_API extern void write(swgptr address, T value)
{
    if (address > 0)
    {
        *(T*)address = value;
    }
}

template<typename T>
UTINNI_API extern void write(swgptr address, int offsetOfAddrResult, T value)
{
    const swgptr resultAddress = read<swgptr>(address);
    if (resultAddress > 0)
    {
        *(T*)(resultAddress + offsetOfAddrResult) = value;
    }
}

UTINNI_API extern void copy(swgptr pDest, swgptr pSource, size_t length);
UTINNI_API extern void write(swgptr address, swgptr value, int length);
UTINNI_API extern void set(swgptr pDest, swgptr value, size_t length);

UTINNI_API extern void patchAddress(swgptr address, swgptr value);
UTINNI_API extern std::tuple<swgptr, std::vector<char>> nopAddress(swgptr address, int nopCount);
UTINNI_API extern void restoreBytes(const std::tuple <swgptr, std::vector<char>>& originalBytes);

UTINNI_API extern void createJMP(swgptr address, swgptr jumpToAddress, size_t overrideLength);

UTINNI_API extern swgptr getAddress(swgptr baseAddress, int ptrDepth);
UTINNI_API extern swgptr getAddress(swgptr baseAddress, std::vector<int>& offsets);

}

