#pragma once

#include "utinni.h"
#include "swg/object/object.h"

namespace utinni
{
enum cameraMode : int
{
	 cm_FreeChase = 2,
	 cm_Free = 5
};

enum cameraProjectionMode
{
	 pm_Perspective = 0,
	 pm_Parallel = 1,
};

class UTINNI_API Camera : public Object
{
public:
	 swg::math::Matrix4x4 projectionMatrix;
	 int viewportX;
	 int viewportY;
	 int viewportWidth;
	 int viewportHeight;
	 float oneOverViewportWidth;
	 float oneOverViewportHeight;
	 float nearPlane;
	 float farPlane;
	 float horizontalFieldOfView;
	 float verticalFieldOfView;
	 float tanOfHalfHorizontalFov;
	 float tanOfHalfVerticalFov;
	 swg::math::Vector frustumVertex[8];
	 swg::math::Volume frustumVolume;
	 swg::math::Vector frustumVertex_w[8];
	 swg::math::Volume frustumVolume_w;
	 cameraProjectionMode projectionMode;
	 float left;
	 float top;
	 float right;
	 float bottom;
	 bool isUnderWater;
	 uint32_t unk01;
	 int numberOfObjectsAdded;
	 uint32_t* unk02;

	 void getViewport(int& viewPortX0, int& viewPortY0, int& viewPortX1, int& viewPortY1);
	 void getViewport(float& viewPortX0, float& viewPortY0, float& viewPortX1, float& viewPortY1);
	 void setViewport(int x0, int y0, int width, int height);

	 void setNearPlane(float nearPlane);
	 void setFarPlane(float farPlane);

	 void setHorizontalFieldOfView(float fieldOfView);

    swg::math::Vector reverseProjectInViewportSpace(int x, int y);
    swg::math::Vector reverseProjectInViewportSpace(float viewPortX, float viewPortY, float cameraZ);

};

class UTINNI_API RenderWorldCamera
{
public:
	 static void addExcludedObject(Object* obj);
	 static void clearExcludedObjects();
};


}

