#include "appearance.h"

namespace swg::appearance
{
using pCreateAppearance = utinni::Appearance* (__cdecl*)(const char* filename);
pCreateAppearance createAppearance = (pCreateAppearance)0x00B262A0;
}

namespace swg::cellProperty
{
using pGetParentCell = swgptr(__thiscall*)(utinni::CellProperty* pThis);
using pSetPortalTransitions = void(__cdecl*)(bool enabled);

pGetParentCell getParentCell = (pGetParentCell)0x00B22C00;
pSetPortalTransitions setPortalTransitions = (pSetPortalTransitions)0x00B2A990;
}

namespace swg::portalPropertyTemplate
{
using pGetCrc = int(__thiscall*)(utinni::PortalPropertyTemplate* pThis);
using pGetCellCount = int(__thiscall*)(utinni::PortalPropertyTemplate* pThis);
using pGetExteriorAppearanceName = const char* (__thiscall*)(utinni::PortalPropertyTemplate* pThis);

pGetCrc getCrc = (pGetCrc)0x00B47BD0;
pGetCellCount getCellCount = (pGetCellCount)0x00B47BE0;
pGetExteriorAppearanceName getExteriorAppearanceName = (pGetExteriorAppearanceName)0x00B47C90;
}

namespace swg::portalPropertyTemplateList
{
using pGetPobByCrcString = utinni::PortalPropertyTemplate* (__cdecl*)(utinni::PersistentCrcString* pobCrcString);
pGetPobByCrcString getPobByCrcString = (pGetPobByCrcString)0x00B497E0;
}

namespace swg::skeleton
{
using pAddShaderPrimitives = void(__thiscall*)(swgptr pThis, swgptr pSkeletalAppearance);

pAddShaderPrimitives addShaderPrimitives = (pAddShaderPrimitives)0x007E6C50;
}

namespace swg::skeletalAppearance
{
using pRender = void(__thiscall*)(swgptr pThis);
using pGetDisplayLodSkeleton = swgptr(__thiscall*)(swgptr pThis);

pRender render = (pRender)0x007C8B60;
pGetDisplayLodSkeleton getDisplayLodSkeleton = (pGetDisplayLodSkeleton)0x007CA130;
}

namespace utinni
{

Appearance* Appearance::create(const char* filename)
{
    return swg::appearance::createAppearance(filename);
}

ClientObject* CellProperty::getParentObject() const
{
    return parentObject;
}

Object* CellProperty::getAppearanceObject() const
{
    return appearanceObject;
}

int CellProperty::getIndex() const
{
    return index;
}

const char* CellProperty::getName() const
{
    return name;
}

swgptr CellProperty::getParentCell()
{
    return swg::cellProperty::getParentCell(this);
}

void CellProperty::setPortalTransitions(bool enabled)
{
    swg::cellProperty::setPortalTransitions(enabled);
}

int PortalPropertyTemplate::getCrc()
{
    return swg::portalPropertyTemplate::getCrc(this);
}

int PortalPropertyTemplate::getCellCount()
{
    return swg::portalPropertyTemplate::getCellCount(this);
}

const char* PortalPropertyTemplate::getExteriorAppearanceName()
{
    return swg::portalPropertyTemplate::getExteriorAppearanceName(this);
}

PortalPropertyTemplate* PortalPropertyTemplateList::getPobByCrcString(PersistentCrcString* pobCrcString)
{
    return swg::portalPropertyTemplateList::getPobByCrcString(pobCrcString);
}


namespace skeletalAppearance
{
bool renderSkeleton = false;

void setRenderSkeleton(bool value)
{
    renderSkeleton = value;
}

void __fastcall hkRender(swgptr pThis)
{
    swg::skeletalAppearance::render(pThis);

    if (renderSkeleton)
    {
        swgptr pSkeleton = swg::skeletalAppearance::getDisplayLodSkeleton(pThis);
        if (pSkeleton != 0)
        {
            swg::skeleton::addShaderPrimitives(pSkeleton, pThis);
        }
    }
}
void detour()
{
    swg::skeletalAppearance::render = (swg::skeletalAppearance::pRender)Detour::Create(swg::skeletalAppearance::render, hkRender, DETOUR_TYPE_PUSH_RET);
}

}
}
