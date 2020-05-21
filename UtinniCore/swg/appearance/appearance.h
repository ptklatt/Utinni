#pragma once

#include "utinni.h"
#include "swg/misc/crc_string.h"
#include "swg/misc/swg_math.h"
#include "swg/object/object.h"

struct UTINNI_API Hardpoint
{
    utinni::PersistentCrcString name;
    swg::math::Transform Transform;
};

namespace utinni
{
class UTINNI_API AppearanceTemplate
{
public:
    DWORD* vtbl;
    int referenceCount;
    PersistentCrcString* const m_crcName;
    DWORD* unk01;
    DWORD* unk02;
    std::vector<Hardpoint*, std::allocator<Hardpoint*>>* hardpoints;
    char* floorName;
    DWORD* unk03;
};

class UTINNI_API Appearance
{
public:
    DWORD* vtbl;
    AppearanceTemplate* appearanceTemplate;
    DWORD* extent;
    Object* ownerObject;
    int renderedFrameCount;
    swg::math::Vector scale;
    bool keepAlive;
    bool useRenderEffectsFlag;
    bool allowShadowBlob;
    swg::math::Transform appearanceToWorld;
};

class UTINNI_API CellProperty
{
public:
    DWORD getParentCell();
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

}
