#include "ground_scene.h"
#include "terrain.h"


namespace swg::groundScene
{
using pGroundScene_ctor = DWORD(__thiscall*)(utinni::GroundScene* pThis, const char* terrainFilename, const char* avatarFilename, DWORD customPlayer); // Offline scene ctor
using pReloadTerrain = void(__thiscall*)(utinni::GroundScene* pThis);
using pChangeCamera = int(__thiscall*)(utinni::GroundScene* pThis, int, float);
using pGetCurrentCamera = utinni::Camera* (__thiscall*)(utinni::GroundScene* pThis);

using pUpdate = void(__thiscall*)(utinni::GroundScene* pThis, float time);
using pHandleInputMapUpdate = void(__thiscall*)(DWORD pThis);
using pHandleInputMapEvent = void(__thiscall*)(DWORD pThis, DWORD ioEvent);

using pInit = void(__thiscall*)(utinni::GroundScene* pThis, const char* terrain, utinni::Object* playerObj, float time);

pGroundScene_ctor groundScene_ctor = (pGroundScene_ctor)0x00519830; // Offline scene ctor
pReloadTerrain reloadTerrain = (pReloadTerrain)0x0051A4F0;
pChangeCamera changeCamera = (pChangeCamera)0x0051A350;
pGetCurrentCamera getCurrentCamera = (pGetCurrentCamera)0x0051A4D0;

pUpdate update;
pHandleInputMapUpdate handleInputMapUpdate;
pHandleInputMapEvent handleInputMapEvent;

pInit init;
}

namespace utinni
{
GroundScene* GroundScene::get() // Static GroundScene Pointer
{
    return memory::read<GroundScene*>(0x190885C);
}

const char* GroundScene::getName()
{
    std::string terrainPath = Terrain::get()->getPath();
    if (terrainPath.empty())
        return "";

    int i = terrainPath.find_first_of('/') + 1;
    const int length = terrainPath.size() - i - 5;

    if (length < 0)
        return "";

    return terrainPath.substr(i, length).c_str();
}


void GroundScene::detour()
{

}

void GroundScene::removeDetour()
{
    Detour::Remove((LPVOID)swg::groundScene::handleInputMapUpdate);
}

Camera* GroundScene::getCurrentCamera()
{
    return swg::groundScene::getCurrentCamera(this);
}

}


