
#include "object.h"
#include "swg/appearance/appearance.h"
#include "swg/misc/swg_math.h"
#include "swg/misc/network.h"
#include "swg/misc/swg_memory.h"
#include "swg/misc/swg_utility.h"

namespace swg::objectTemplateList
{
using pGetObjectTemplateByFilename = utinni::SharedObjectTemplate* (__cdecl*)(const char* filename);
using pGetObjectTemplateByIff = utinni::SharedObjectTemplate* (__cdecl*)(swgptr iff);
using pGetObjectTemplateByCrc = utinni::SharedObjectTemplate* (__cdecl*)(unsigned int crc);

using pReloadObject = swgptr(__cdecl*)(swgptr iff);

using pGetCrcStringByName = utinni::ConstCharCrcString(__cdecl*)(utinni::ConstCharCrcString* result, const char* name);
using pGetCrcStringByCrc = swgptr(__cdecl*)(void* result, unsigned int crc);

pGetObjectTemplateByFilename getObjectTemplateByFilename = (pGetObjectTemplateByFilename)0x00B28700;
pGetObjectTemplateByIff getObjectTemplateByIff = (pGetObjectTemplateByIff)0x00B28720;
pGetObjectTemplateByCrc getObjectTemplateByCrc = (pGetObjectTemplateByCrc)0x00B28740;

pReloadObject reloadObject = (pReloadObject)0x00B289B0;

pGetCrcStringByName getCrcStringByName = (pGetCrcStringByName)0x00B28A10;
pGetCrcStringByCrc getCrcStringByCrc = (pGetCrcStringByCrc)0x00B28AA0;
}

namespace swg::objectTemplate
{
using pCreateObject = utinni::Object* (__cdecl*)(const char* filename);

pCreateObject createObject = (pCreateObject)0x00B2E760;
}

namespace swg::sharedObjectTemplate
{
using pGetAppearancetFilename = const char** (__thiscall*)(utinni::SharedObjectTemplate* pThis, bool unk);
using pGetPortalLayoutFilename = const char** (__thiscall*)(utinni::SharedObjectTemplate* pThis, bool unk);
using pGetClientDataFilename = const char** (__thiscall*)(utinni::SharedObjectTemplate* pThis, bool unk);

using pGetGameObjectType = int(__thiscall*)(utinni::SharedObjectTemplate* pThis, bool unk);

pGetAppearancetFilename getAppearancetFilename = (pGetAppearancetFilename)0x011A6C10;
pGetPortalLayoutFilename getPortalLayoutFilename = (pGetPortalLayoutFilename)0x011A6D30;
pGetClientDataFilename getClientDataFilename = (pGetClientDataFilename)0x011A6E50;

pGetGameObjectType getGameObjectType = (pGetGameObjectType)0x011A8B60;
}

namespace swg::sharedBuildingObjectTemplate
{
using pGetTerrainLayerFilename = const char* (__thiscall*)(utinni::SharedBuildingObjectTemplate* pThis, bool unk);
using pGetInteriorLayoutFilename = const char* (__thiscall*)(utinni::SharedBuildingObjectTemplate* pThis, bool unk);

pGetTerrainLayerFilename getTerrainLayerFilename = (pGetTerrainLayerFilename)0x01231910;
pGetInteriorLayoutFilename getInteriorLayoutFilename = (pGetInteriorLayoutFilename)0x01231A30;
}

namespace swg::object
{
using pCtor = utinni::Object* (__thiscall*)(utinni::Object* pThis);

using pDisallowDelete = void(__cdecl*)(bool disallowDelete);

using pGetType = unsigned int(__thiscall*)(utinni::Object* pThis);

using pSetParentCell = void(__thiscall*)(utinni::Object* pThis, DWORD parentCell);

using pAddToWorld = void(__thiscall*)(utinni::Object* pThis);
using pRemoveFromWorld = void(__thiscall*)(utinni::Object* pThis);

using pGetTransform_o2w = swg::math::Transform* (__thiscall*)(utinni::Object* pThis);
using pSetTransform_o2w = void(__thiscall*)(utinni::Object* pThis, swg::math::Transform& objectToWorld);
using pGetTransform_a2w = swg::math::Transform* (__thiscall*)(utinni::Object* pThis);
using pSetTransform_a2w = void(__thiscall*)(utinni::Object* pThis, swg::math::Transform& appearanceToWorld);

using pGetPosition = swg::math::Vector* (__thiscall*)(utinni::Object* pThis);
using pSetPosition = void(__thiscall*)(utinni::Object* pThis, swg::math::Vector& position);

using pSetScale = void(__thiscall*)(utinni::Object* pThis, swg::math::Vector& scale);

using pRotate_o2w = const swg::math::Vector(__thiscall*)(utinni::Object* pThis, DWORD unk, const swg::math::Vector* o2w, const swg::math::Vector* pointInSpace); // ??

using pGetAppearance = utinni::Appearance* (__thiscall*)(utinni::Object* pThis);
using pSetAppearance = void(__thiscall*)(utinni::Object* pThis, utinni::Appearance* appearance);
using pGetAppearanceFilename = const char* (__thiscall*)(utinni::Object* pThis);
using pSetAppearanceByFilename = void(__thiscall*)(utinni::Object* pThis, const char* filename);

using pAddNotification = void(__thiscall*)(utinni::Object* pThis, swgptr notification, bool allowInWorld);

using pGetParentCell = utinni::CellProperty* (__thiscall*)(utinni::Object* pThis);

using pSetObjectToWorldDirty = void(__thiscall*)(utinni::Object* pThis, bool isDirty);

using pPositionAndRotationChanged = void(__thiscall*)(utinni::Object* pThis, bool dueToParentChange, swg::math::Vector& oldPosition);

using pGetClientObject = utinni::ClientObject*(__thiscall*)(utinni::Object* pThis);

using pGetTemplateFilename = const char* (__thiscall*)(utinni::Object* pThis);

pCtor ctor = (pCtor)0x00B21B80;

pDisallowDelete disallowDelete;

pGetType getType = (pGetType)0x00B23C60;

pSetParentCell setParentCell = (pSetParentCell)0x00B22C30;

pAddToWorld addToWorld = (pAddToWorld)0x00B225F0;
pRemoveFromWorld removeFromWorld = (pRemoveFromWorld)0x00B22680;

pGetTransform_o2w getTransform_o2w = (pGetTransform_o2w)0x00B22C80;
pSetTransform_o2w setTransform_o2w = (pSetTransform_o2w)0x00B22CC0;
pGetTransform_a2w getTransform_a2w = (pGetTransform_a2w)0x00B22E90;
pSetTransform_a2w setTransform_a2w = (pSetTransform_a2w)0x00B22E10;

pGetPosition getPosition = (pGetPosition)0x00B243F0;
pSetPosition setPosition = (pSetPosition)0x00B23960;

pSetScale setScale = (pSetScale)0x00B23A10;

pRotate_o2w rotate_o2w = (pRotate_o2w)0x004361F0;

pGetAppearance getAppearance = (pGetAppearance)0x00B22FF0;
pSetAppearance setAppearance = (pSetAppearance)0x00B22F60;
pGetAppearanceFilename getAppearanceFilename = (pGetAppearanceFilename)0x00B243E0;
pSetAppearanceByFilename setAppearanceByFilename = (pSetAppearanceByFilename)0x00B243A0;

pAddNotification addNotification = (pAddNotification)0x00B225A0;

pGetParentCell getParentCell = (pGetParentCell)0x00B22C00;

pSetObjectToWorldDirty setObjectToWorldDirty = (pSetObjectToWorldDirty)0x00B24CE0;

pPositionAndRotationChanged positionAndRotationChanged = (pPositionAndRotationChanged)0x00B22A50;

pGetClientObject getClientObject = (pGetClientObject)0x00554BC0;

pGetTemplateFilename getTemplateFilename = (pGetTemplateFilename)0x00B23C40;
}

namespace utinni
{
SharedObjectTemplate* ObjectTemplateList::getObjectTemplateByFilename(const char* filename)
{
    return swg::objectTemplateList::getObjectTemplateByFilename(filename);
}

SharedObjectTemplate* ObjectTemplateList::getObjectTemplateByIff(swgptr iff)
{
    return swg::objectTemplateList::getObjectTemplateByIff(iff);
}

ConstCharCrcString getCrcStringByCrc(unsigned int crc)
{
    return *(ConstCharCrcString*)swg::objectTemplateList::getCrcStringByCrc(allocate(sizeof(ConstCharCrcString)), crc);
}

ConstCharCrcString ObjectTemplateList::getCrcStringByName(const char* name)
{
    return *(ConstCharCrcString*)swg::objectTemplateList::getCrcStringByCrc(allocate(sizeof(ConstCharCrcString)), calculateCrc(name));
}

swgptr ObjectTemplateList::getCrcStringByNameAsPtr(const char* name)
{
    return swg::objectTemplateList::getCrcStringByCrc(allocate(sizeof(ConstCharCrcString)), calculateCrc(name));
}

Object* ObjectTemplate::createObject(const char* filename)
{
    return swg::objectTemplate::createObject(filename);
}

const char* SharedObjectTemplate::getAppearanceFilename()
{
    return *swg::sharedObjectTemplate::getAppearancetFilename(this, false);
}

const char* SharedObjectTemplate::getPortalLayoutFilename()
{
    return *swg::sharedObjectTemplate::getPortalLayoutFilename(this, false);
}

const char* SharedObjectTemplate::getClientDataFilename()
{
    return *swg::sharedObjectTemplate::getClientDataFilename(this, false);
}

int SharedObjectTemplate::getGameObjectType()
{
    return swg::sharedObjectTemplate::getGameObjectType(this, false);
}

const char* SharedBuildingObjectTemplate::getTerrainLayerFilename()
{
    return swg::sharedBuildingObjectTemplate::getTerrainLayerFilename(this, false);
}

const char* SharedBuildingObjectTemplate::getInteriorLayoutFilename()
{
    return swg::sharedBuildingObjectTemplate::getInteriorLayoutFilename(this, false);
}

Object* Object::ctor()
{
    return swg::object::ctor((Object*)allocate(160));
}

Object* Object::getObjectById(swgptr cachedNetworkId)
{
    if (cachedNetworkId == 0)
    {
        return nullptr;
    }

    return Network::getCachedObjectById(cachedNetworkId);
}

void Object::remove()
{
    (**(void(__thiscall***)(Object*, bool))this)(this, true); // ToDo do this proper at some point, taken from IDA pseudo code
}

swg::math::Transform* Object::getTransform()
{
    if (parentObject == nullptr)
    {
        return getTransform_o2w();
    }
    else
    {
        return &objectToParent;
    }
}

swg::math::Transform* Object::getTransform_o2w()
{
    return swg::object::getTransform_o2w(this);
}

void Object::setTransform_o2w(swg::math::Transform& object2world)
{
    swg::object::setTransform_o2w(this, object2world);
}

const swg::math::Vector Object::rotate_o2w(const swg::math::Vector* o2w, const swg::math::Vector* pointInSpace)
{
    return swg::object::rotate_o2w(this, 0, o2w, pointInSpace);
}

void Object::addNotification(swgptr notification, bool allowWhenInWorld)
{
    swg::object::addNotification(this, notification, allowWhenInWorld);
}

void Object::addToWorld()
{
    swg::object::addToWorld(this);
}

void Object::removeFromWorld()
{
    swg::object::removeFromWorld(this);
}

void Object::setAppearance(Appearance* appearance)
{
    swg::object::setAppearance(this, appearance);
}

CellProperty* Object::getParentCell()
{
    return swg::object::getParentCell(this);
}

void Object::setObjectToWorldDirty(bool isDirty)
{
    swg::object::setObjectToWorldDirty(this, isDirty);
}

void Object::positionAndRotationChanged(bool dueToParentChange, swg::math::Vector& oldPosition)
{
    swg::object::positionAndRotationChanged(this, dueToParentChange, oldPosition);
}

ClientObject* Object::getClientObject()
{
    return swg::object::getClientObject(this);
}

const char* Object::getTemplateFilename()
{
    return swg::object::getTemplateFilename(this);
}

const char* Object::getAppearanceFilename()
{
    return swg::object::getAppearanceFilename(this);
}
}
