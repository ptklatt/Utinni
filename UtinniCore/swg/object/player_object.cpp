#include "player_object.h"

#include "swg/game/game.h"
#include "swg/camera/camera.h"

namespace swg::teleportHelper // ToDo implement proper, dirty taken from IDA
{
using pTeleportPlayer = int (__thiscall*)(swgptr pThis, swg::math::Transform* position);

pTeleportPlayer teleportPlayer = (pTeleportPlayer)0x0062A8B0; // Controller function, do proper later
}

namespace utinni::playerObject
{
bool hidePlayerAppearance;
void togglePlayerAppearance()
{
    Object* playerCreatureObj = Game::getPlayerCreatureObject();
	 if (playerCreatureObj == nullptr)
	 {
		  return;
	 }

	 RenderWorldCamera::clearExcludedObjects();

	 hidePlayerAppearance = !hidePlayerAppearance;
	 if (hidePlayerAppearance)
	 {
		  RenderWorldCamera::addExcludedObject(playerCreatureObj);
	 }
}

float getSpeed()
{
    return memory::read<float>(0x0191BFB4, 0x674);
}

void setSpeed(float value)
{
	 if (!Game::isSafeToUse())
	 {
		  return;
	 }

    memory::write<float>(0x0191BFB4, 0x674, value);
}

void teleport(float x, float y, float z) // ToDo do more proper in the future
{
	 if (!Game::isSafeToUse())
	 {
		  return;
	 }

    swg::math::Transform destPos(x, y, z);
    swg::teleportHelper::teleportPlayer(memory::read<swgptr>((swgptr)Game::getPlayerCreatureObject() + 0x2C), &destPos);
}
}
