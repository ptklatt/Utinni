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
#include "scene.h"
#include "swg/camera/camera.h"

namespace utinni
{
class Camera;

class UTINNI_API GroundScene : public NetworkScene
{
public:
    swgptr inputMap;
    swgptr debugPortalCameraInputMap;
    swgptr structurePlacementCameraInputMap;
    swgptr freeCameraInputMap;
    swgptr mouseCursor;
    swgptr lastYawPitch;
    swgptr cockpitCamera;
    swgptr shipTurretCamera;
    swgptr freeChaseCamera;
    swgptr freeCamera;
    swgptr debugPortalCamera;
    swgptr structurePlacementCamera;
    swgptr flyByCamera;
    swgptr cameras[7];
    int currentView;
    bool disableWorldSnapshot;
    bool unk01;
    bool unk02;
    bool isLoading;
    bool unk03;
    bool isReady;
    bool unk04;
    uint32_t unk05;
    uint32_t unk06;
    uint32_t unk07;
    uint32_t unk08;
    uint32_t unk09;
    swgptr overheadMap;
    uint32_t unk10;
    uint32_t unk11;
    bool currentMode;
    uint32_t unk12;
    uint32_t unk13;
    uint32_t unk14;
    uint32_t unk15;
    bool isTutorial;
    uint32_t unk16;
    uint32_t unk17;

    static GroundScene* get();
    static GroundScene* ctor(const char* terrainFilename, const char* avatarObjectFilename);
    std::string getName();

    static void addPreDrawLoopCallback(void(*func)(GroundScene* pThis));
    static void addPostDrawLoopCallback(void(*func)(GroundScene* pThis));
    static void addUpdateLoopCallback(void(*func)(GroundScene* pThis, float elapsedTime));
    static void addCameraChangeCallback(void(*func)());

    static void detour();
    static void removeDetour();

    Camera* getCurrentCamera();
    void toggleFreeCamera();
    void changeCameraMode(int cameraMode);
    bool isFreeCameraActive() const;

    void reloadTerrain();

    void createObjectAtPlayer(const char* filename);
    void createAppearanceAtPlayer(const char* filename);


};

}
