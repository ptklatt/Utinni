#pragma once

#include "utinni.h"

namespace utinni
{
struct UTINNI_API CrcString
{
    swgptr vtbl;
    unsigned int crc;
};

struct UTINNI_API PersistentCrcString : CrcString
{
    swgptr unk01;
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
