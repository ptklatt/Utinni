#include "crc_string.h"
#include "swg_utility.h"

namespace swg::crcString
{
using pConstCharCrcString_ctor = utinni::ConstCharCrcString * (__thiscall*)(DWORD pThis, const char* value);
using pPersistentCrcString_ctor = utinni::PersistentCrcString * (__thiscall*)(DWORD pThis, const char* value, bool unk);

pConstCharCrcString_ctor constCharCrcString_ctor = (pConstCharCrcString_ctor)0x00AA55B0;
pPersistentCrcString_ctor persistentCrcString_ctor = (pPersistentCrcString_ctor)0x00AA4050;

}

namespace utinni
{
PersistentCrcString* PersistentCrcString::ctor(const char* str)
{
    return swg::crcString::persistentCrcString_ctor(allocateMemory(sizeof(PersistentCrcString)), str, true);
}

#pragma optimize( "", off )
ConstCharCrcString* ConstCharCrcString::ctor(const char* str)
{
    return swg::crcString::constCharCrcString_ctor(allocateMemory(sizeof(ConstCharCrcString)), str);
}
}
