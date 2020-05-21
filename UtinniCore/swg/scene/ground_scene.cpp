#include "ground_scene.h"
#include "swg/misc/swg_utility.h"
#include "swg/appearance/appearance.h"


namespace swg::groundScene
{
using pGroundScene_ctor = DWORD(__thiscall*)(utinni::GroundScene* pThis, const char* terrainFilename, const char* avatarFilename, DWORD customPlayer); // Offline scene ctor
using pReloadTerrain = void(__thiscall*)(utinni::GroundScene* pThis);
using pChangeCamera = int(__thiscall*)(utinni::GroundScene* pThis, int, float);

using pUpdate = void(__thiscall*)(utinni::GroundScene* pThis, float time);
using pHandleInputMapUpdate = void(__thiscall*)(DWORD pThis);
using pHandleInputMapEvent = void(__thiscall*)(DWORD pThis, DWORD ioEvent);

using pInit = void(__thiscall*)(utinni::GroundScene* pThis, const char* terrain, utinni::Object* playerObj, float time);

pGroundScene_ctor groundScene_ctor = (pGroundScene_ctor)0x00519830; // Offline scene ctor
pReloadTerrain reloadTerrain = (pReloadTerrain)0x0051A4F0;
pChangeCamera changeCamera = (pChangeCamera)0x0051A350;

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

void GroundScene::detour()
{

}

void GroundScene::removeDetour()
{
    Detour::Remove((LPVOID)swg::groundScene::handleInputMapUpdate);
}

}


