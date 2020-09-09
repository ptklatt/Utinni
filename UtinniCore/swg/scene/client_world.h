#pragma once

#include "utinni.h"
#include "swg/misc/swg_math.h"

namespace utinni
{
    class CellProperty;
    class Object;
    struct CollisionInfo;
}

namespace utinni::clientWorld
{
extern bool collide(CellProperty* cell, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, CollisionInfo& collisionResults, uint16_t collisionFlags, Object* excludeObject);
}
