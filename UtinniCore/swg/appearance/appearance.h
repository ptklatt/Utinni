#pragma once

#include "utinni.h"
#include "swg/misc/crc_string.h"
#include "swg/misc/swg_math.h"
#include "swg/object/object.h"

namespace utinni
{
class Object;

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
    swgptr extent;
    Object* ownerObject;
    int renderedFrameCount;
    swg::math::Vector scale;
    bool keepAlive;
    bool useRenderEffectsFlag;
    bool allowShadowBlob;
    swg::math::Transform appearanceToWorld;

    static Appearance* create(const char* filename);
};

class UTINNI_API CellProperty
{
public:
    swgptr getParentCell();
    static void setPortalTransitions(bool enabled);
};

class UTINNI_API PortalPropertyTemplate
{
public:
    int getCrc();
    int getCellCount();
    const char* getExteriorAppearanceName();
};

class UTINNI_API PortalPropertyTemplateList
{
public:
    static PortalPropertyTemplate* getPobByCrcString(PersistentCrcString* pobCrcString);
};

namespace skeletalAppearance
{
UTINNI_API extern void setRenderSkeleton(bool value);
extern void detour();
}

}
