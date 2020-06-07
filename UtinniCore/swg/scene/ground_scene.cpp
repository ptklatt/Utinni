#include "ground_scene.h"
#include "terrain.h"


namespace swg::groundScene
{
using pGroundScene_ctor = DWORD(__thiscall*)(utinni::GroundScene* pThis, const char* terrainFilename, const char* avatarFilename, DWORD customPlayer); // Offline scene ctor
using pReloadTerrain = void(__thiscall*)(utinni::GroundScene* pThis);
using pChangeCamera = int(__thiscall*)(utinni::GroundScene* pThis, int, float);
using pGetCurrentCamera = utinni::Camera* (__thiscall*)(utinni::GroundScene* pThis);

using pDraw = void(__thiscall*)(utinni::GroundScene* pThis);
using pUpdate = void(__thiscall*)(utinni::GroundScene* pThis, float time);
using pHandleInputMapUpdate = void(__thiscall*)(DWORD pThis);
using pHandleInputMapEvent = void(__thiscall*)(DWORD pThis, DWORD ioEvent);

using pInit = void(__thiscall*)(utinni::GroundScene* pThis, const char* terrain, utinni::Object* playerObj, float time);

pGroundScene_ctor groundScene_ctor = (pGroundScene_ctor)0x00519830; // Offline scene ctor
pReloadTerrain reloadTerrain = (pReloadTerrain)0x0051A4F0;
pChangeCamera changeCamera = (pChangeCamera)0x0051A350;
pGetCurrentCamera getCurrentCamera = (pGetCurrentCamera)0x0051A4D0;

pDraw draw = (pDraw)0x0051B770;
pUpdate update = (pUpdate)0x0051AF10;
pHandleInputMapUpdate handleInputMapUpdate = (pHandleInputMapUpdate)0x0051AB20;
pHandleInputMapEvent handleInputMapEvent = (pHandleInputMapEvent)0x0051AA40;

pInit init = (pInit)0x00518EB0;
}

static std::vector<void(*)(utinni::GroundScene* pThis)> preDrawLoopCallbacks;
static std::vector<void(*)(utinni::GroundScene* pThis)> postDrawLoopCallbacks;
static std::vector<void(*)(utinni::GroundScene* pThis, float time)> updateLoopCallbacks;

namespace utinni
{
GroundScene* GroundScene::get() // Static GroundScene Pointer
{
    return memory::read<GroundScene*>(0x190885C);
}

std::string GroundScene::getName()
{
    std::string terrainPath = Terrain::get()->getFilename();

    if (terrainPath.empty())
        return "";

    int i = terrainPath.find_first_of('/') + 1;
    const int length = terrainPath.size() - i - 5;

    if (length < 0)
        return "";

    return terrainPath.substr(i, length);
}

void GroundScene::addPreDrawLoopCallback(void(*func)(GroundScene * pThis))
{
    preDrawLoopCallbacks.emplace_back(func);

}

void GroundScene::addPostDrawLoopCallback(void(*func)(GroundScene* pThis))
{
    postDrawLoopCallbacks.emplace_back(func);

}

void __fastcall hkDrawLoop(GroundScene* pThis, DWORD EDX)
{
    for (const auto& func : preDrawLoopCallbacks)
    {
        func(pThis);
    }

    swg::groundScene::draw(pThis);

    for (const auto& func : postDrawLoopCallbacks)
    {
        func(pThis);
    }
}

void GroundScene::addUpdateLoopCallback(void(*func)(GroundScene* pThis, float time))
{
    updateLoopCallbacks.emplace_back(func);
}

void __fastcall hkUpdateLoop(utinni::GroundScene* pThis, DWORD EDX, float time)
{
    for (const auto& func : updateLoopCallbacks)
    {
        func(pThis, time);
    }

    swg::groundScene::update(pThis, time);
}

void GroundScene::detour()
{
    swg::groundScene::draw = (swg::groundScene::pDraw)Detour::Create(swg::groundScene::draw, hkDrawLoop, DETOUR_TYPE_PUSH_RET);
    swg::groundScene::update = (swg::groundScene::pUpdate)Detour::Create(swg::groundScene::update, hkUpdateLoop, DETOUR_TYPE_PUSH_RET);
}

void GroundScene::removeDetour()
{
    //Detour::Remove((LPVOID)swg::groundScene::handleInputMapUpdate);
}

Camera* GroundScene::getCurrentCamera()
{
    return swg::groundScene::getCurrentCamera(this);
}

void GroundScene::reloadTerrain()
{
    swg::groundScene::reloadTerrain(this);
}
}


