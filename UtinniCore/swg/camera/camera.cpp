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

#include "camera.h"
#include "swg/game/game.h"
#include "swg/scene/ground_scene.h"

namespace swg::camera
{
using pGetViewportInt = void(__thiscall*)(utinni::Camera* pThis, int& viewPortX0, int& viewPortY0, int& viewPortX1, int& viewPortY1);
using pGetViewportFloat = void(__thiscall*)(utinni::Camera* pThis, float& viewPortX0, float& viewPortY0, float& viewPortX1, float& viewPortY1);
using pSetViewport = void(__thiscall*)(utinni::Camera* pThis, int x0, int y0, int width, int height);

using pSetNearPlane = void(__thiscall*)(utinni::Camera* pThis, float nearPlane);
using pSetFarPlane = void(__thiscall*)(utinni::Camera* pThis, float farPlane);

using pSetHorizontalFieldOfView = void(__thiscall*)(utinni::Camera* pThis, float fieldOfView);

using pReverseProjectInViewportSpaceInt = swg::math::Vector*(__thiscall*)(utinni::Camera* pThis, math::Vector& result, int x, int y);
using pReverseProjectInViewportSpaceFloat = swg::math::Vector*(__thiscall*)(utinni::Camera* pThis, math::Vector& result, float viewPortX, float viewPortY, float cameraZ);

pGetViewportInt getViewportInt = (pGetViewportInt)0x00767DF0;
pGetViewportFloat getViewportFloat = (pGetViewportFloat)0x00767E40;
pGetViewportFloat getViewportFloatDetour;
pSetViewport setViewport = (pSetViewport)0x00767E90;

pSetNearPlane setNearPlane = (pSetNearPlane)0x00767EC0;
pSetFarPlane setFarPlane = (pSetFarPlane)0x00767EE0;

pSetHorizontalFieldOfView setHorizontalFieldOfView = (pSetHorizontalFieldOfView)0x00767F00;

pReverseProjectInViewportSpaceInt reverseProjectInViewportSpaceInt = (pReverseProjectInViewportSpaceInt)0x007682B0;
pReverseProjectInViewportSpaceFloat reverseProjectInViewportSpaceFloat = (pReverseProjectInViewportSpaceFloat)0x00768390;
}

namespace swg::renderWorldCamera
{
using pAddExcludedObject = int(__thiscall*)(const utinni::Camera* pThis, utinni::Object* obj);
using pClearExcludedObjects = int(__thiscall*)(const utinni::Camera* pThis);

pAddExcludedObject addExcludedObject = (pAddExcludedObject)0x00778FE0;
pClearExcludedObjects clearExcludedObjects = (pClearExcludedObjects)0x00779130;
}

namespace swg::gameCamera
{
using pAlter = float(__thiscall*)(utinni::GameCamera* pThis, float time);

pAlter alter = (pAlter)0x00788740;
}

namespace utinni
{
void Camera::getViewport(int& viewPortX0, int& viewPortY0, int& viewPortX1, int& viewPortY1)
{
    swg::camera::getViewportInt(this, viewPortX0, viewPortY0, viewPortX1, viewPortY1);
}

void Camera::getViewport(float& viewPortX0, float& viewPortY0, float& viewPortX1, float& viewPortY1)
{
    swg::camera::getViewportFloat(this, viewPortX0, viewPortY0, viewPortX1, viewPortY1);
}

void Camera::setViewport(int x0, int y0, int width, int height)
{
    swg::camera::setViewport(this, x0, y0, width, height);
}

void Camera::setNearPlane(float nearPlane)
{
    swg::camera::setNearPlane(this, nearPlane);
}

void Camera::setFarPlane(float farPlane)
{
    swg::camera::setFarPlane(this, farPlane);
}

void Camera::setHorizontalFieldOfView(float fieldOfView)
{
    swg::camera::setHorizontalFieldOfView(this, fieldOfView);
}

swg::math::Vector Camera::reverseProjectInViewportSpace(int x, int y)
{
    swg::math::Vector tmp;
    return *swg::camera::reverseProjectInViewportSpaceInt(this, tmp, x, y);
}

swg::math::Vector Camera::reverseProjectInViewportSpace(float viewPortX, float viewPortY, float cameraZ)
{
    swg::math::Vector tmp;
    return *swg::camera::reverseProjectInViewportSpaceFloat(this, tmp, viewPortX, viewPortY, cameraZ);;
}

void RenderWorldCamera::addExcludedObject(Object* obj)
{
    const Camera* camera = Game::getConstCamera();
    if (camera == nullptr)
    {
        return;
    }

    swg::renderWorldCamera::addExcludedObject(camera, obj);
}

void RenderWorldCamera::clearExcludedObjects()
{
    const Camera* camera = Game::getConstCamera();
    if (camera == nullptr)
    {
        return;
    }

    swg::renderWorldCamera::clearExcludedObjects(camera);
}

float GameCamera::alter(float time)
{
    return swg::gameCamera::alter(this, time);
}
}
