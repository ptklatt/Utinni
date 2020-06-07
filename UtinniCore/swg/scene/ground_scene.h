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
    DWORD* inputMap;
    DWORD* debugPortalCameraInputMap;
    DWORD* structurePlacementCameraInputMap;
    DWORD* freeCameraInputMap;
    DWORD* mouseCursor;
    DWORD* lastYawPitch;
    DWORD* cockpitCamera;
    DWORD* shipTurretCamera;
    DWORD* freeChaseCamera;
    DWORD* freeCamera;
    DWORD* debugPortalCamera;
    DWORD* structurePlacementCamera;
    DWORD* flyByCamera;
    DWORD* cameras[7];
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
    DWORD* overheadMap;
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
    std::string getName();

    static void addPreDrawLoopCallback(void(*func)(GroundScene* pThis));
    static void addPostDrawLoopCallback(void(*func)(GroundScene* pThis));
    static void addUpdateLoopCallback(void(*func)(GroundScene* pThis, float elapsedTime));

    static void detour();
    static void removeDetour();

    Camera* getCurrentCamera();

    void reloadTerrain();
};

}
