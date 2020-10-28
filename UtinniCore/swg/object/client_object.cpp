#include "client_object.h"
#include "swg/misc/swg_utility.h"
#include "utility/string_utility.h"

namespace swg::clientObject
{
using pSetParentCell = void(__thiscall*)(utinni::ClientObject* pThis, utinni::CellProperty* cell);
using pBeginBaselines = void(__thiscall*)(utinni::ClientObject* pThis);
using pEndBaselines = void(__thiscall*)(utinni::ClientObject* pThis);

using pGetGameObjectType = int(__thiscall*)(utinni::ClientObject* pThis);
using pGetGameObjectTypeStringIdKey = const char** (__thiscall*)(utinni::ClientObject* pThis);
using pGetGameObjectTypeName = const wchar_t** (__thiscall*)(utinni::ClientObject* pThis);

using pGetStaticObject = swgptr(__thiscall*)(swgptr pThis);
using pGetTangibleObject = swgptr(__thiscall*)(swgptr pThis);

pSetParentCell setParentCell = (pSetParentCell)0x00555410;
pBeginBaselines beginBaselines = (pEndBaselines)0x00555070;
pEndBaselines endBaselines = (pEndBaselines)0x00555070;

pGetGameObjectType getGameObjectType = (pGetGameObjectType)0x00557360;
pGetGameObjectTypeStringIdKey getGameObjectTypeStringIdKey = (pGetGameObjectTypeStringIdKey)0x00557370;
pGetGameObjectTypeName getGameObjectTypeName = (pGetGameObjectTypeName)0x00557390;

pGetStaticObject getStaticObject = (pGetStaticObject)0x00554BF0;
pGetTangibleObject getTangibleObject = (pGetTangibleObject)0x00554C00;
}

namespace swg::buildingObject
{
using pCtor = utinni::Object * (__thiscall*)(DWORD pThis, DWORD sharedTemplate);
using pAddToWorld = void(__thiscall*)(utinni::Object* pThis);
using pRemoveFromWorld = void(__thiscall*)(utinni::Object* pThis);

pCtor ctor = (pCtor)0x0070DBB0;

pAddToWorld addToWorld = (pAddToWorld)0x0070DD00;
pRemoveFromWorld removeFromWorld = (pRemoveFromWorld)0x0070DD20;
}

namespace utinni
{
void ClientObject::setParentCell(CellProperty* cell)
{
    swg::clientObject::setParentCell(this, cell);
}

void ClientObject::beginBaselines()
{
    swg::clientObject::beginBaselines(this);
}

void ClientObject::endBaselines()
{
    swg::clientObject::endBaselines(this);
}

int ClientObject::getGameObjectType()
{
    return swg::clientObject::getGameObjectType(this);
}

const char* ClientObject::getGameObjectTypeStringIdKey()
{
    return *swg::clientObject::getGameObjectTypeStringIdKey(this);
}

std::string ClientObject::getGameObjectTypeName()
{
    return std::string(stringUtility::toString(std::wstring(*swg::clientObject::getGameObjectTypeName(this))));
}

swgptr ClientObject::getCreatureObject()
{
    return (*(int(__thiscall**)(ClientObject*))(*(swgptr*)this + 92))(this); // ToDo do this proper via variable
}

swgptr ClientObject::getShipObject()
{
    return (*(int(__thiscall**)(ClientObject*))(*(swgptr*)this + 116))(this); // ToDo do this proper via variable
}

swgptr ClientObject::getStaticObject()
{
    return (*(int(__thiscall**)(ClientObject*))(*(swgptr*)this + 100))(this); // ToDo do this proper via variable
}

swgptr ClientObject::getTangibleObject()
{
    return (*(int(__thiscall**)(ClientObject*))(*(swgptr*)this + 108))(this); // ToDo do this proper via variable
}
}

