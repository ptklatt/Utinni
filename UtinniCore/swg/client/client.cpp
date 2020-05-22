#include "client.h"
#include "swg/graphics/graphics.h"
#include "swg/game/game.h"
#include "swg/misc/direct_input.h"

namespace swg::client
{
using pSetupInstall = int(__cdecl*)(utinni::StartupData* pStartupData);
using pMainLoop = int(__cdecl*)(HINSTANCE hInstance, int a2, int a3);

using pWndProc = int(__stdcall*)(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

pSetupInstall setupStartDataInstall = (pSetupInstall)0x00A9F970;
pMainLoop clientMain = (pMainLoop)0x00401050;

pWndProc wndProc = (pWndProc)0x00AA0970; // SWG's WndProc

}

bool isEditorChild = false;
HWND hwnd = nullptr;
HINSTANCE hInstance = nullptr;

namespace utinni
{
void Client::setIsEditorChild(bool value)
{
    isEditorChild = value;
}

bool Client::getIsEditorChild()
{
    return isEditorChild;
}

void Client::setHwnd(void* newHwnd)
{
    hwnd = (HWND)newHwnd;
}

HWND Client::getHwnd()
{
    return hwnd;
}

void Client::setHInstance(void* newHInstance)
{
    hInstance = (HINSTANCE)newHInstance;
}

HINSTANCE Client::getHInstance()
{
    return hInstance;
}

void Client::suspendInput()
{
    if (Game::isRunning())
    {
        Graphics::showMouseCursor(false);
        DirectInput::suspend();
    }
}

void Client::resumeInput()
{
    if (Game::isRunning())
    {
        Graphics::showMouseCursor(true);
        DirectInput::resume();
    }
}

int __cdecl hkSetupStartInstall(StartupData* pStartupData)
{
    if (Client::getIsEditorChild())
    {
        pStartupData->createOwnWindow = false;
        pStartupData->hInstance = nullptr;
        pStartupData->useNewWindowHandle = true;
        pStartupData->windowHandle = Client::getHwnd();
        pStartupData->processMessagePump = true;
        pStartupData->lostFocusCallback = 0;
    }

    return swg::client::setupStartDataInstall(pStartupData);
}

LRESULT CALLBACK hkWndProc(HWND Hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (Client::getIsEditorChild())
    {
    }
    return CallWindowProc((WNDPROC)swg::client::wndProc, Hwnd, msg, wParam, lParam);
}

int __cdecl hkMainLoop(HINSTANCE hInstance, int unk1, int unk2)
{
    if (Client::getIsEditorChild())
    {
        while (Client::getHInstance() == nullptr)
        {
            Sleep(1); // Wait until the Editor has set the HWND and HInstance the game should use
             // ToDo add a timeout
        }
        return swg::client::clientMain(GetModuleHandle(nullptr), unk1, unk2);
    }
    else
    {
        return swg::client::clientMain(hInstance, unk1, unk2);
    }
}

void Client::detour()
{
    swg::client::setupStartDataInstall = (swg::client::pSetupInstall)Detour::Create((LPVOID)swg::client::setupStartDataInstall, hkSetupStartInstall, DETOUR_TYPE_PUSH_RET);
    swg::client::clientMain = (swg::client::pMainLoop)Detour::Create((LPVOID)swg::client::clientMain, hkMainLoop, DETOUR_TYPE_PUSH_RET);

    DirectInput::detour();
}

}
