#include "client_world.h"

namespace swg::clientWorld
{
using pCollide = bool(__cdecl*)(utinni::CellProperty* cell, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swgptr unk, utinni::CollisionInfo& collisionResults, uint16_t collisionFlags, utinni::Object* excludeObject);
using pInternalCollide = bool(__cdecl*)(uint16_t collisionFlags, utinni::CellProperty* cell, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, utinni::Object* excludeObject, swgptr unk, swgptr collisionResults);
using pInternalCollideFindAllObjects = bool(__cdecl*)(uint16_t collisionFlags, int objectList, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, utinni::Object* excludeObject, swgptr unk, swgptr collisionResults);

pCollide collide = (pCollide)0x00561350;
pInternalCollide internalCollide = (pInternalCollide)0x00562940;
pInternalCollideFindAllObjects internalCollideFindAllObjects = (pInternalCollideFindAllObjects)0x00562680;
}

namespace utinni::clientWorld
{
bool collide(CellProperty* cell, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, CollisionInfo& collisionResults, uint16_t collisionFlags, Object* excludeObject)
{
    return swg::clientWorld::collide(cell, worldStart, worldEnd, 0x199CB34, collisionResults, collisionFlags, excludeObject); // Unsure what 0x199CB34 is, taken from IDA
}

bool __cdecl hkInternalCollide(uint16_t collisionFlags, utinni::CellProperty* cell, swg::math::Vector* worldStart, swg::math::Vector* worldEnd, utinni::Object* excludeObject, swgptr unk, swgptr collisionResults)
{
    bool result;
  /*  if (swg::clientWorld::internalCollideFindAllObjects(8, 1, worldStart, worldEnd, excludeObject, unk, collisionResults))
    {
        result = true;
    }
    if (swg::clientWorld::internalCollideFindAllObjects(8, 2, worldStart, worldEnd, excludeObject, unk, collisionResults))
    {
        result = true;
    }*/
    result = swg::clientWorld::internalCollide(collisionFlags, cell, worldStart, worldEnd, excludeObject, unk, collisionResults);

    return result;
}

void detour()
{
    //swg::clientWorld::internalCollide = (swg::clientWorld::pInternalCollide)Detour::Create((LPVOID)swg::clientWorld::internalCollide, hkInternalCollide, DETOUR_TYPE_PUSH_RET);
}
}
