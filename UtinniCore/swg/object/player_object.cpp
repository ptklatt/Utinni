#include "player_object.h"

#include "swg/game/game.h"
#include "swg/camera/camera.h"

namespace swg::teleportHelper // ToDo implement proper, dirty taken from IDA
{
using pGetPlayerObject = swgptr(_cdecl*)();
using pSwgDynamicCast = swgptr (__cdecl*)(swgptr, int, swgptr, swgptr, int);
using pTeleportPlayer = int (__thiscall*)(DWORD pThis, swg::math::Transform* position);

pGetPlayerObject getPtr = (pGetPlayerObject)0x004251D0;
pSwgDynamicCast swg_dynamicCast = (pSwgDynamicCast)0x00B262A0;
pTeleportPlayer teleportPlayer = (pTeleportPlayer)0x0062A8B0; // Controller function, do proper later
}

namespace utinni::playerObject
{
bool hidePlayerAppearance;
void togglePlayerAppearance()
{
	 if (!Game::getPlayerCreatureObject())
	 {
		  return;
	 }

	 hidePlayerAppearance = !hidePlayerAppearance;

	 RenderWorldCamera::clearExcludedObjects();

	 if (hidePlayerAppearance)
	 {
		  RenderWorldCamera::addExcludedObject(Game::getPlayerCreatureObject());
	 }
}

float getSpeed()
{
    return memory::read<float>(0x0191BFB4, 0x674);
}

void setSpeed(float value)
{
    memory::write<float>(0x0191BFB4, 0x674, value);
}

void teleport(float x, float y, float z) // ToDo super hacky IDA copy, clean up
{
	 static constexpr swgptr pTargetType = 0x0186F484; // PlayerCreatureController
	 static constexpr swgptr pSourceType = 0x0186AE78; // Controller

    swg::math::Transform destPos = swg::math::Transform(x, y, z);
    swg::teleportHelper::teleportPlayer(swg::teleportHelper::swg_dynamicCast(memory::read<DWORD>((swgptr)Game::getPlayerCreatureObject() + 0x2C), 0, pSourceType, pTargetType, 0), &destPos);
}
}
