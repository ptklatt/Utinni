#include "creature_object.h"
#include "swg/object/object.h"
#include "swg/misc/network.h"

namespace swg::creatureObject
{
using pSetTarget = void(__thiscall*)(swgptr pThis, const int64_t& id);

pSetTarget setTarget = (pSetTarget)0x00434AB0;
}

static std::vector<void(*)(utinni::Object* target)> onTargetCallbacks;

namespace utinni::creatureObject
{

void addOnTargetCallback(void(*func)(Object* target))
{
    onTargetCallbacks.emplace_back(func);
}

void __fastcall hkSetTarget(swgptr pThis, DWORD EDX, const int64_t& id)
{
    swg::creatureObject::setTarget(pThis, id);

    Object* obj = Network::getObjectById(id);

    for (const auto& func : onTargetCallbacks)
    {
        func(obj);
    }
}

void detour()
{
    swg::creatureObject::setTarget = (swg::creatureObject::pSetTarget)Detour::Create(swg::creatureObject::setTarget, hkSetTarget, DETOUR_TYPE_PUSH_RET);
}
;
}