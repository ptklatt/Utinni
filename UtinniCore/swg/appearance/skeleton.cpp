#include "skeleton.h"


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