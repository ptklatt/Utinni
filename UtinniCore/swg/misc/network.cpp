#include "network.h"
#include "swg/object/object.h"

namespace swg::network
{
// 00B37F30 -- NetworkIdManager & NetworkIdManager::getInstance ()
using pIdManagerGetObjectById = utinni::Object* (__cdecl*)(const int64_t& id);
using pIdManagerGetInstance = DWORD(__cdecl*)();

using pCast = int64_t(__thiscall*)(DWORD*, int, int);

pIdManagerGetObjectById idManagerGetObjectById = (pIdManagerGetObjectById)0x00B380E0;
pIdManagerGetInstance idManagerGetInstance = (pIdManagerGetInstance)0x00B37F30;

pCast cast = (pCast)0xAA4900;
}

namespace utinni
{

DWORD Network::getManger()
{
    return swg::network::idManagerGetInstance(); // See if this needs to be read
}

Object* Network::getObjectById(const int64_t& id)
{
    return swg::network::idManagerGetObjectById(id);
}

int64_t Network::cast(int id)
{
    DWORD networkId;
    return swg::network::cast(&networkId, id, (id >> 32));;
}


}

