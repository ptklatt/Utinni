#include "client_world.h"

namespace swg::clientWorld
{
using pCollide = bool(__cdecl*)(utinni::CellProperty* cell, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swgptr unk, utinni::CollisionInfo& collisionResults, uint16_t collisionFlags, utinni::Object* excludeObject);

pCollide collide = (pCollide)0x00561350;  
}

namespace utinni::clientWorld
{
bool collide(CellProperty* cell, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, CollisionInfo& collisionResults, uint16_t collisionFlags, Object* excludeObject)
{
    return swg::clientWorld::collide(cell, worldStart, worldEnd, 0x199CB34, collisionResults, collisionFlags, excludeObject); // Unsure what 0x199CB34 is, taken from IDA
}
}