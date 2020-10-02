#pragma once

#include "utinni.h"
#include "swg/misc/crc_string.h"
#include "swg/misc/swg_math.h"
#include "swg/object/object.h"

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
    swgptr vtbl;
    ClientObject* parentObject;
    swgptr unk_08;
    swgptr unk_0C;
    swgptr unk_10;
    swgptr unk_14;
    swgptr unk_18;
    swgptr unk_1C;
    swgptr portalProperty;
    int index;
    Object* appearanceObject;
    swgptr unk_2C;
    swgptr unk_30;
    swgptr floor;
    const char* name;
    swgptr dpvsObject;
    swgptr unk_40;
    swgptr unk_44;
    swgptr unk_48;
    swgptr unk_4C;
    swgptr unk_50;
    swgptr unk_54;
    swgptr unk_58;
    swgptr unk_5C;
    swgptr unk_60;

    ClientObject* getParentObject() const;
    Object* getAppearanceObject() const;
    int getIndex() const;
    const char* getName() const;
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
