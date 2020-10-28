/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

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
