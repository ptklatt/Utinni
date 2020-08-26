#include "network.h"
#include "swg/object/object.h"

namespace swg::network
{
// 00B37F30 -- NetworkIdManager & NetworkIdManager::getInstance ()
using pIdManagerGetObjectById = utinni::Object* (__cdecl*)(const int64_t& id);
using pIdManagerGetInstance = swgptr(__cdecl*)();

using pCachedNetworkIdGetObject = utinni::Object* (__thiscall*)(swgptr pThis); // pThis = CachedNetworkId, should be 8 bytes?

using pCast = int64_t(__thiscall*)(swgptr*, int, int);

pIdManagerGetObjectById idManagerGetObjectById = (pIdManagerGetObjectById)0x00B380E0;
pIdManagerGetInstance idManagerGetInstance = (pIdManagerGetInstance)0x00B37F30;


pCachedNetworkIdGetObject cachedNetworkIdGetObject = (pCachedNetworkIdGetObject)0x00B30160;

pCast cast = (pCast)0xAA4900;
}

namespace utinni
{

swgptr Network::getManger()
{
    return swg::network::idManagerGetInstance(); // See if this needs to be read
}

Object* Network::getObjectById(const int64_t& id)
{
    return swg::network::idManagerGetObjectById(id);
}

Object* Network::getCachedObjectById(swgptr pCachedNetworkId)
{
    return swg::network::cachedNetworkIdGetObject(pCachedNetworkId);
}

int64_t Network::cast(int id)
{
    swgptr networkId; // This is broken
    return swg::network::cast(&networkId, id, (id >> 32));;
}


}

