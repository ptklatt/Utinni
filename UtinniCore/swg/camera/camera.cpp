#include "camera.h"
#include "../game/game.h"
#include "../scene/ground_scene.h"

namespace swg::camera
{
using pGetViewportInt = void(__thiscall*)(utinni::Camera* pThis, int& viewPortX0, int& viewPortY0, int& viewPortX1, int& viewPortY1);
using pGetViewportFloat = void(__thiscall*)(utinni::Camera* pThis, float& viewPortX0, float& viewPortY0, float& viewPortX1, float& viewPortY1);
using pSetViewport = void(__thiscall*)(utinni::Camera* pThis, int x0, int y0, int width, int height);

using pSetNearPlane = void(__thiscall*)(utinni::Camera* pThis, float nearPlane);
using pSetFarPlane = void(__thiscall*)(utinni::Camera* pThis, float farPlane);

using pSetHorizontalFieldOfView = void(__thiscall*)(utinni::Camera* pThis, float fieldOfView);

using pReverseProjectInViewportSpaceInt = const swg::math::Vector(__thiscall*)(utinni::Camera* pThis, int x, int y);
using pReverseProjectInViewportSpaceFloat = const swg::math::Vector(__thiscall*)(utinni::Camera* pThis, float viewPortX, float viewPortY, float cameraZ);

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
using pAddExcludedObject = int(__thiscall*)(utinni::Camera* pThis, utinni::Object* obj);
using pClearExcludedObjects = int(__thiscall*)(utinni::Camera* pThis);

pAddExcludedObject addExcludedObject = (pAddExcludedObject)0x00778FE0;
pClearExcludedObjects clearExcludedObjects = (pClearExcludedObjects)0x00779130;
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
    return swg::camera::reverseProjectInViewportSpaceInt(this, x, y);
}

swg::math::Vector Camera::reverseProjectInViewportSpace(float viewPortX, float viewPortY, float cameraZ)
{
    return swg::camera::reverseProjectInViewportSpaceFloat(this, viewPortX, viewPortY, cameraZ);
}

void RenderWorldCamera::addExcludedObject(Object* obj)
{
    Camera* camera = Game::getCamera(); // does it need getConstCamera?
    if (!camera)
        return;

    swg::renderWorldCamera::addExcludedObject(camera, obj);
}

void RenderWorldCamera::clearExcludedObjects()
{
    Camera* camera = Game::getCamera(); // does it need getConstCamera?
    if (!camera)
        return;

    swg::renderWorldCamera::clearExcludedObjects(camera);
}

}
