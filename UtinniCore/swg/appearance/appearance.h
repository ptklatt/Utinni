#pragma once

#include "utinni.h"
#include "swg/misc/crc_string.h"
#include "swg/misc/swg_math.h"
#include "swg/object/object.h"
#include "extent.h"

namespace utinni
{
class Object;
class ClientObject;

struct UTINNI_API Hardpoint
{
    utinni::PersistentCrcString name;
    swg::math::Transform Transform;
};

class UTINNI_API AppearanceTemplate
{
public:
    swgptr vtbl;
    int referenceCount;
    PersistentCrcString* const m_crcName;
    swgptr unk01;
    swgptr unk02;
    std::vector<Hardpoint*, std::allocator<Hardpoint*>>* hardpoints;
    char* floorName;
    swgptr unk03;
};

class UTINNI_API Appearance
{
public:
    swgptr vtbl;
    AppearanceTemplate* appearanceTemplate;
    swgptr unk;
    Object* ownerObject;
    int renderedFrameCount;
    swg::math::Vector scale;
    bool keepAlive;
    bool useRenderEffectsFlag;
    bool allowShadowBlob;
    swg::math::Transform appearanceToWorld;

    static Appearance* create(const char* filename);

    BoxExtent* getExtent();
};

class UTINNI_API ParticleEffectAppearance : public Appearance
{
public:
    bool collide(swg::math::Vector* worldStart, swg::math::Vector* worldEnd, swgptr unk, utinni::CollisionInfo& collisionResults);
    static void detour();;
};


}
