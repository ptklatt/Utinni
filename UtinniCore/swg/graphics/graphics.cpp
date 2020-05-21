#include "graphics.h"
#include "swg/scene/ground_scene.h"
#include "swg/client/client.h"
#include "swg/ui/cui_manager.h"

namespace swg::graphics
{
using pUpdate = void(__cdecl*)(float elapsedTime);
using pBeginScene = void(__cdecl*)();
using pEndScene = void(__cdecl*)();

using pPresentWindow = int(__cdecl*)(HWND hwnd, int width, int height);
using pPresent = void(__cdecl*)();

using pShowMouseCursor = bool(__cdecl*)(bool isShown);
using pSetSystemMouseCursorPosition = void(__cdecl*)(int X, int Y);

using pResize = void(__cdecl*)(int width, int height);
using pFlushResources = void(__cdecl*)(bool reset);

using pTextureListReloadTextures = void(__cdecl*)();

pUpdate update = (pUpdate)0x00755700; 
pBeginScene beginScene = (pBeginScene)0x00755730; 
pEndScene endScene = (pEndScene)0x00755740;

pPresentWindow presentWindow = (pPresentWindow)0x00755810;
pPresent present = (pPresent)0x00755800; 

pShowMouseCursor showMouseCursor = (pShowMouseCursor)0x00755A50;
pSetSystemMouseCursorPosition setSystemMouseCursorPosition = (pSetSystemMouseCursorPosition)0x00755AC0;

pResize resize = (pResize)0x00754E40;
pFlushResources flushResources = (pFlushResources)0x00755520;

pTextureListReloadTextures textureListReloadTextures = (pTextureListReloadTextures)0x00764B70;
}

namespace utinni
{
void __cdecl hkUpdate(float elapsedTime)
{
    swg::graphics::update(elapsedTime);
}

void __cdecl hkBeginScene()
{
    swg::graphics::beginScene();
}

int oldWidth = 0;
int oldHeight = 0;
void __cdecl hkEndScene()
{
    swg::graphics::endScene();

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
    swg::graphics::presentWindow(hwnd, width, height);
}

void __cdecl hkPresent()
{
    swg::graphics::present();
}

void Graphics::detour()
{
    swg::graphics::update = (swg::graphics::pUpdate)Detour::Create((LPVOID)swg::graphics::update, hkUpdate, DETOUR_TYPE_PUSH_RET);
    swg::graphics::beginScene = (swg::graphics::pBeginScene)Detour::Create((LPVOID)swg::graphics::beginScene, hkBeginScene, DETOUR_TYPE_JMP, 5);
    swg::graphics::endScene = (swg::graphics::pEndScene)Detour::Create((LPVOID)swg::graphics::endScene, hkEndScene, DETOUR_TYPE_JMP, 5);

    swg::graphics::presentWindow = (swg::graphics::pPresentWindow)Detour::Create((LPVOID)swg::graphics::presentWindow, hkPresentWindow, DETOUR_TYPE_JMP, 5);
    swg::graphics::present = (swg::graphics::pPresent)Detour::Create((LPVOID)0x00755800, hkPresent, DETOUR_TYPE_JMP, 5);
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

