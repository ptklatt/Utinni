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

#pragma once

#include "utinni.h"
#include "swg/object/object.h"

namespace utinni
{
class UTINNI_API Camera : public Object
{
public:

	 enum Modes : int
	 {
		  cm_FreeChase = 2,
		  cm_Free = 5
	 };

	 enum ProjectionModes
	 {
		  pm_Perspective = 0,
		  pm_Parallel = 1,
	 };

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
	 ProjectionModes projectionMode;
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

class UTINNI_API RenderWorldCamera : public Camera
{
public:
	 static void addExcludedObject(Object* obj);
	 static void clearExcludedObjects();
};

class UTINNI_API GameCamera : public RenderWorldCamera
{
public:
	 float alter(float time);
};

}

