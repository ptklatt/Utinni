#pragma once

#include "utinni.h"
#include "swg/misc/swg_math.h"

namespace utinni
{
class UTINNI_API ExtentBase
{
private:
    int type;
public:

    bool intersect(swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* normal, float* time);
};

class UTINNI_API Extent : public ExtentBase
{
private:
    swgptr sphere;
    int refCount;
public:
};

class UTINNI_API BoxExtent : public Extent
{
private:
public:
    // Axial box
    swg::math::Vector min;
    swg::math::Vector max;
    bool realIntersect(swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swg::math::Vector* surfaceNormal, float* time);
};
}
