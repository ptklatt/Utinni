#include "graphics.h"
#include "swg/scene/ground_scene.h"
#include "swg/client/client.h"
#include "swg/ui/cui_manager.h"
#include "directx9.h"

namespace swg::graphics
{
using pInstall = bool(__cdecl*)();

using pUpdate = void(__cdecl*)(float elapsedTime);
using pBeginScene = void(__cdecl*)();
using pEndScene = void(__cdecl*)();

using pPresentWindow = int(__cdecl*)(HWND hwnd, int width, int height);
using pPresent = void(__cdecl*)();

using pUseHardwareCursor = bool(__cdecl*)(bool value);
using pShowMouseCursor = bool(__cdecl*)(bool isShown);
using pSetSystemMouseCursorPosition = void(__cdecl*)(int X, int Y);

using pResize = void(__cdecl*)(int width, int height);
using pFlushResources = void(__cdecl*)(bool reset);

using pTextureListReloadTextures = void(__cdecl*)();

pInstall install = (pInstall)0x007548A0;

pUpdate update = (pUpdate)0x00755700; 
pBeginScene beginScene = (pBeginScene)0x00755730; 
pEndScene endScene = (pEndScene)0x00755740;

pPresentWindow presentWindow = (pPresentWindow)0x00755810;
pPresent present = (pPresent)0x00755800; 

pUseHardwareCursor useHardwareCursor = (pUseHardwareCursor)0x00755940;
pShowMouseCursor showMouseCursor = (pShowMouseCursor)0x00755A50;
pSetSystemMouseCursorPosition setSystemMouseCursorPosition = (pSetSystemMouseCursorPosition)0x00755AC0;

pResize resize = (pResize)0x00754E40;
pFlushResources flushResources = (pFlushResources)0x00755520;

pTextureListReloadTextures textureListReloadTextures = (pTextureListReloadTextures)0x00764B70;
}


static std::vector<void(*)(float elapsedTime)> preUpdateCallback;
static std::vector<void(*)(float elapsedTime)> postUpdateCallback;

static std::vector<void(*)()> preBeginSceneCallback;
static std::vector<void(*)()> postBeginSceneCallback;

static std::vector<void(*)()> preEndSceneCallback;
static std::vector<void(*)()> postEndSceneCallback;

static std::vector<void(*)(HWND hwnd, int width, int height)> prePresentWindowCallback;
static std::vector<void(*)(HWND hwnd, int width, int height)> postPresentWindowCallback;

static std::vector<void(*)()> prePresentCallback;
static std::vector<void(*)()> postPresentCallback;

namespace utinni
{
void Graphics::addPreUpdateLoopCallback(void(*func)(float elapsedTime))
{
    preUpdateCallback.emplace_back(func);
}

void Graphics::addPostUpdateLoopCallback(void(*func)(float elapsedTime))
{
    postUpdateCallback.emplace_back(func);
}

void Graphics::addPreBeginSceneCallback(void(*func)())
{
    preBeginSceneCallback.emplace_back(func);
}

void Graphics::addPostBeginSceneCallback(void(*func)())
{
    postBeginSceneCallback.emplace_back(func);
}

void Graphics::addPreEndSceneCallback(void(*func)())
{
    preEndSceneCallback.emplace_back(func);
}

void Graphics::addPostEndSceneCallback(void(*func)())
{
    postEndSceneCallback.emplace_back(func);
}

void Graphics::addPrePresentWindowCallback(void(*func)(HWND hwnd, int width, int height))
{
    prePresentWindowCallback.emplace_back(func);
}

void Graphics::addPostPresentWindowCallback(void(*func)(HWND hwnd, int width, int height))
{
    postPresentWindowCallback.emplace_back(func);
}

void Graphics::addPrePresentCallback(void(*func)())
{
    prePresentCallback.emplace_back(func);
}

void Graphics::addPostPresentCallback(void(*func)())
{
    postPresentCallback.emplace_back(func);
}

bool __cdecl hkInstall()
{
    bool result = swg::graphics::install();

    directX::detour();

    return result;
}

void __cdecl hkUpdate(float elapsedTime)
{
    for (const auto& func : preUpdateCallback)
    {
        func(elapsedTime);
    }

    swg::graphics::update(elapsedTime);

    for (const auto& func : postUpdateCallback)
    {
        func(elapsedTime);
    }
}

void __cdecl hkBeginScene()
{
    for (const auto& func : preBeginSceneCallback)
    {
        func();
    }

    swg::graphics::beginScene();

    for (const auto& func : postBeginSceneCallback)
    {
        func();
    }
}

int oldWidth = 0;
int oldHeight = 0;
void __cdecl hkEndScene()
{
    for (const auto& func : preEndSceneCallback)
    {
        func();
    }

    swg::graphics::endScene();

    for (const auto& func : postEndSceneCallback)
    {
        func();
    }

    RECT rect;
    if (Client::getIsEditorChild() && GetWindowRect(Client::getHwnd(), &rect))
    {
        int newWidth = rect.right - rect.left;
        int newHeight = rect.bottom - rect.top;

        if (newWidth != oldWidth || newHeight != oldHeight)
        {
            oldWidth = newWidth;
            oldHeight = newHeight;
            swg::graphics::resize(newWidth, newHeight);
            swg::graphics::flushResources(false);
            CuiManager::setSize(newWidth, newHeight);
        }
    }
}

void __cdecl hkPresentWindow(HWND hwnd, int width, int height)
{
    for (const auto& func : prePresentWindowCallback)
    {
        func(hwnd, width, height);
    }

    swg::graphics::presentWindow(hwnd, width, height);

    for (const auto& func : postPresentWindowCallback)
    {
        func(hwnd, width, height);
    }
}

void __cdecl hkPresent()
{
    for (const auto& func : prePresentCallback)
    {
        func();
    }

    swg::graphics::present();

    for (const auto& func : postPresentCallback)
    {
        func();
    }
}

void Graphics::detour()
{
    swg::graphics::install = (swg::graphics::pInstall)Detour::Create(swg::graphics::install, hkInstall, DETOUR_TYPE_PUSH_RET);

    swg::graphics::update = (swg::graphics::pUpdate)Detour::Create(swg::graphics::update, hkUpdate, DETOUR_TYPE_PUSH_RET);
    swg::graphics::beginScene = (swg::graphics::pBeginScene)Detour::Create(swg::graphics::beginScene, hkBeginScene, DETOUR_TYPE_JMP, 5);
    swg::graphics::endScene = (swg::graphics::pEndScene)Detour::Create(swg::graphics::endScene, hkEndScene, DETOUR_TYPE_JMP, 5);

    swg::graphics::presentWindow = (swg::graphics::pPresentWindow)Detour::Create(swg::graphics::presentWindow, hkPresentWindow, DETOUR_TYPE_JMP, 5);
    swg::graphics::present = (swg::graphics::pPresent)Detour::Create(swg::graphics::present, hkPresent, DETOUR_TYPE_JMP, 5);
}

void Graphics::useHardwareCursor(bool value)
{
    swg::graphics::useHardwareCursor(value);
}

void Graphics::showMouseCursor(bool isShown)
{
    swg::graphics::showMouseCursor(isShown);
}

void Graphics::setSystemMouseCursorPosition(int X, int Y)
{
    swg::graphics::setSystemMouseCursorPosition(X, Y);
}

int Graphics::getCurrentRenderTargetWidth() // 0x00754DB0 is the clients function address
{
    return memory::read<int>(0x1922E64); // static ptr to RenderTargetWidth
}

int Graphics::getCurrentRenderTargetHeight() // 0x00754DC0 is the clients function address
{
    return memory::read<int>(0x1922E60); // static ptr to RenderTargetHeight
}

void Graphics::flushResources(bool fullFlush)
{
    swg::graphics::flushResources(fullFlush);
}

void Graphics::reloadTextures()
{
    swg::graphics::textureListReloadTextures();
}

}

