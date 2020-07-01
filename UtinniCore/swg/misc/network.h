#pragma once

#include "utinni.h"
#include "swg/object/object.h"

namespace utinni
{
class UTINNI_API Network
{
public:
    static DWORD getManger();
    static Object* getObjectById(const int64_t& id);
    static Object* getCachedObjectById(DWORD pCachedNetworkId);

    static int64_t cast(int id);
};
}
