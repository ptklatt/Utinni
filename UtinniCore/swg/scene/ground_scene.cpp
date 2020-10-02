#include "ground_scene.h"
#include "terrain.h"
#include "world_snapshot.h"
#include "render_world.h"
#include "swg/misc/swg_memory.h"
#include "swg/game/game.h"
#include "swg/object/client_object.h"
#include "utility/string_utility.h"


namespace swg::groundScene
{
using pCtor = utinni::GroundScene* (__thiscall*)(void* pThis, const char* terrainFilename, const char* avatarObjectFilename, swgptr customPlayer); // Offline scene ctor
using pReloadTerrain = void(__thiscall*)(utinni::GroundScene* pThis);
using pChangeCamera = int(__thiscall*)(utinni::GroundScene* pThis, utinni::Camera::Modes cameraMode, float);
using pGetCurrentCamera = utinni::Camera* (__thiscall*)(utinni::GroundScene* pThis);

using pDraw = void(__thiscall*)(utinni::GroundScene* pThis);
using pUpdate = void(__thiscall*)(utinni::GroundScene* pThis, float time);
using pHandleInputMapUpdate = void(__thiscall*)(utinni::GroundScene* pThis);
using pHandleInputMapEvent = void(__thiscall*)(utinni::GroundScene* pThis, swgptr ioEvent);

using pInit = void(__thiscall*)(utinni::GroundScene* pThis, const char* terrain, utinni::Object* playerObj, float time);

pCtor ctor = (pCtor)0x00519830; // Offline scene ctor
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

GroundScene* GroundScene::ctor(const char* terrainFilename, const char* avatarObjectFilename)
{
    return swg::groundScene::ctor(utinni::allocate(0xF4), terrainFilename, avatarObjectFilename, 0);
}

std::string GroundScene::getName()
{
    const std::string terrainPath = Terrain::get()->getFilename();

    if (terrainPath.empty())
    {
        return "";
    }

    int i = terrainPath.find_first_of('/') + 1;
    const int length = terrainPath.size() - i - 5;

    if (length < 0)
    {
        return "";
    }

    return terrainPath.substr(i, length);
}

void GroundScene::addPreDrawLoopCallback(void(*func)(GroundScene* pThis))
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

void GroundScene::addUpdateLoopCallback(void(*func)(GroundScene* pThis, float elapsedTime))
{
    updateLoopCallbacks.emplace_back(func);
}

void __fastcall hkUpdateLoop(utinni::GroundScene* pThis, DWORD EDX, float time)
{
  
    swg::groundScene::update(pThis, time);
    for (const auto& func : updateLoopCallbacks)
    {
        func(pThis, time);
    }

}

void GroundScene::detour()
{
    swg::groundScene::draw = (swg::groundScene::pDraw)Detour::Create(swg::groundScene::draw, hkDrawLoop, DETOUR_TYPE_PUSH_RET);
    swg::groundScene::update = (swg::groundScene::pUpdate)Detour::Create(swg::groundScene::update, hkUpdateLoop, DETOUR_TYPE_PUSH_RET);

    WorldSnapshot::setPreloadSnapshot(false);
}

void GroundScene::removeDetour()
{
    //Detour::Remove((LPVOID)swg::groundScene::handleInputMapUpdate);
}

Camera* GroundScene::getCurrentCamera()
{
    return swg::groundScene::getCurrentCamera(this);
}

bool isFreeCam;
void GroundScene::toggleFreeCamera() // ToDo Shitty, do proper
{
    isFreeCam = !isFreeCam;

    Camera::Modes cameraMode;
    if (isFreeCam)
    {
        cameraMode = Camera::Modes::cm_Free;
    }
    else
    {
        cameraMode = Camera::Modes::cm_FreeChase;
    }

    swg::groundScene::changeCamera(this, cameraMode, 0);
}

void GroundScene::changeCameraMode(int cameraMode)
{
    swg::groundScene::changeCamera(this, (Camera::Modes) cameraMode, 0);
}

void GroundScene::reloadTerrain()
{
    swg::groundScene::reloadTerrain(this);
}

void GroundScene::createObjectAtPlayer(const char* filename)
{
    Object* player = Game::getPlayer();
    if (!player)
    {
        return;
    }

    SharedObjectTemplate* objTemplate = ObjectTemplateList::getObjectTemplateByFilename(filename);
    if (objTemplate == nullptr)
    {
        return;
    }

    Object* obj = nullptr;
    const char* pobFilename = objTemplate->getPortalLayoutFilename();
    if (constCharUtility::isEmpty(pobFilename))
    {
        obj = ObjectTemplate::createObject(filename);
    }
    else
    {
        PortalPropertyTemplate* pob = PortalPropertyTemplateList::getPobByCrcString(PersistentCrcString::ctor(pobFilename));
        obj = Object::ctor();

        obj->addNotification(0x019136E4, false);
        obj->setAppearance(Appearance::create(pob->getExteriorAppearanceName()));
        renderWorld::addObjectNotifications(obj);
    }

    ClientObject* clientObj = (ClientObject*)obj;
    clientObj->setParentCell(player->getParentCell());

    CellProperty::setPortalTransitions(false);
    { // ToDO see if this can be removed
        memcpy((void*)(((int)obj) + 0x50), (void*)(((int)player) + 0x50), 0x30u); // Todo see if it can be replaced
    }
    CellProperty::setPortalTransitions(true);

    renderWorld::addObjectNotifications(obj);
    clientObj->endBaselines();

    obj->addToWorld();
}

void GroundScene::createAppearanceAtPlayer(const char* filename)
{
    Object* player = Game::getPlayer();
    if (!player)
    {
        return;
    }

    Appearance* appearance;
    std::string str = filename; // ToDo replace with a 'endsWith' utility function for const char*
    if (str.substr(str.length() - 4) == ".pob")
    {
        PortalPropertyTemplate* pob = PortalPropertyTemplateList::getPobByCrcString(PersistentCrcString::ctor(filename));
        appearance = Appearance::create(pob->getExteriorAppearanceName());
    }
    else
    {
        appearance = Appearance::create(filename);
    }

    if (appearance == nullptr)
    {
        return;
    }

    Object* obj = Object::ctor();

    obj->addNotification(0x019136E4, false);
    obj->setAppearance(appearance);

    memcpy((void*)(((int)obj) + 0x50), (void*)(((int)player) + 0x50), 0x30u);  // Todo see if it can be replaced

    renderWorld::addObjectNotifications(obj);

    obj->addToWorld();
}
}


