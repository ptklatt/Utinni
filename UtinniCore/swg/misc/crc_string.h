#pragma once

#include "utinni.h"

namespace utinni
{
struct UTINNI_API CrcString
{
    DWORD* vtbl;
    unsigned int crc;
};

struct UTINNI_API PersistentCrcString : CrcString
{
    DWORD* unk01;
    char* buffer;

    static PersistentCrcString* ctor(const char* str);
};

struct UTINNI_API TemporaryCrcString : CrcString
{
    char* buffer;
};

struct UTINNI_API ConstCharCrcString : CrcString
{
    const char* buffer;

    static ConstCharCrcString* ctor(const char* str);
};

}
