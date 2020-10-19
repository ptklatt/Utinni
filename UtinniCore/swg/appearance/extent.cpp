#include "extent.h"

namespace swg::baseExtent
{
using pIntersect = bool(__thiscall*)(utinni::ExtentBase* pThis, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* normal, float* time);
using pIntersect3 = int(__thiscall*)(utinni::ExtentBase* pThis, swg::math::Vector* worldStart, swg::math::Vector* worldEnd);

pIntersect intersect = (pIntersect)0x0126AF70;
pIntersect3 intersect3 = (pIntersect3)0x0126AFB0;


    // 0x0126AFB0;
}

namespace swg::extent
{
    
}

namespace swg::boxExtent
{
using pIntersect = bool(__thiscall*)(utinni::BoxExtent* pThis, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* surfaceNormal, float* time);

pIntersect intersect = (pIntersect)0x0125FA10;
}

namespace utinni
{
bool ExtentBase::intersect(swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* normal, float* time)
{
    bool result = swg::baseExtent::intersect3(this, worldStart, worldEnd);
    return false;
}

bool BoxExtent::realIntersect(swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* surfaceNormal, float* time)
{
    return swg::boxExtent::intersect(this, worldStart, worldEnd, surfaceNormal, time);
}
}
