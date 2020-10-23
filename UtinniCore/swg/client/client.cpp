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

bool enableEditorMode = false;
HWND hwnd = nullptr;
HINSTANCE hInstance = nullptr;
bool allowInput = false;

namespace utinni
{
void Client::setEditorMode(bool enable)
{
    enableEditorMode = enable;
}

bool Client::getEditorMode()
{
    return enableEditorMode;
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
        SetFocus(nullptr);
        Graphics::showMouseCursor(false);
        DirectInput::suspend();
        allowInput = false;
    }
}

void Client::resumeInput()
{
    if (Game::isRunning())
    {
        SetFocus(Client::getHwnd());
        Graphics::showMouseCursor(true);
        DirectInput::resume();
        allowInput = true;
    }
}

bool Client::isInputAllowed()
{
    return allowInput;
}

int __cdecl hkSetupStartInstall(StartupData* pStartupData)
{
    if (Client::getEditorMode())
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
    if (Client::getEditorMode())
    {
    }

    return CallWindowProc((WNDPROC)swg::client::wndProc, Hwnd, msg, wParam, lParam);
}

int __cdecl hkMainLoop(HINSTANCE hInstance, int unk1, int unk2)
{
    if (Client::getEditorMode())
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
    //swg::client::wndProc = (swg::client::pWndProc)Detour::Create((LPVOID)swg::client::wndProc, hkWndProc, DETOUR_TYPE_PUSH_RET);

    DirectInput::detour();
}

}
