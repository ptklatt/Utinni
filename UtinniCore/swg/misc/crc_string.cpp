#include "crc_string.h"
#include "swg_memory.h"

namespace swg::crcString
{
using pConstCharCrcString_ctor = utinni::ConstCharCrcString * (__thiscall*)(void* pThis, const char* value);
using pPersistentCrcString_ctor = utinni::PersistentCrcString * (__thiscall*)(void* pThis, const char* value, bool unk);

pConstCharCrcString_ctor constCharCrcString_ctor = (pConstCharCrcString_ctor)0x00AA55B0;
pPersistentCrcString_ctor persistentCrcString_ctor = (pPersistentCrcString_ctor)0x00AA4050;

}

namespace utinni
{
PersistentCrcString* PersistentCrcString::ctor(const char* str)
{
    return swg::crcString::persistentCrcString_ctor(allocate(sizeof(PersistentCrcString)), str, true);
}

ConstCharCrcString* ConstCharCrcString::ctor(const char* str)
{
    return swg::crcString::constCharCrcString_ctor(allocate(sizeof(ConstCharCrcString)), str);
}

}
