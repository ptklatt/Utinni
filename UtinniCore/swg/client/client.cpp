#include "client.h"

namespace swg::client
{
using pSetupInstall = int(__cdecl*)(utinni::StartupData* pStartupData);
using pSetupDirectInputInstall = int(__cdecl*)(HINSTANCE hInstance, HWND hwnd, DWORD menuKey, bool isWindowed);
using pMainLoop = int(__cdecl*)(HINSTANCE hInstance, int a2, int a3);

pSetupInstall setupStartDataInstall = (pSetupInstall)0x00A9F970;
pSetupDirectInputInstall setupDirectInputInstall = (pSetupDirectInputInstall)0x00421490;
pMainLoop clientMain = (pMainLoop)0x00401050;

DWORD wndProc = 0x00AA0970; // Address to SWG's WndProc
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

int __cdecl hkSetupStartInstall(StartupData* pStartupData)
{
    if (Client::getIsEditorChild())
    {
        pStartupData->createOwnWindow = false;
        pStartupData->hInstance = Client::getHInstance();
        pStartupData->processMessagePump = true;
        pStartupData->useNewWindowHandle = true;
        pStartupData->windowHandle = Client::getHwnd();
    }

    return swg::client::setupStartDataInstall(pStartupData);
}

int __cdecl hkSetupDirectInputInstall(HINSTANCE hInstance, HWND hwnd, DWORD menuKey, DWORD unk)
{
    memory::nopAddress(0x0041E51C, 5); // NOPs setCooperativeLevel inside KeyboardDevice(), modify it to skip the isWindowKeyEnabled check, source of the issues?

    HWND result = Client::getHwnd();
    HWND topWindow;
    do
    {
        topWindow = GetParent(result);
        if (topWindow)
        {
            result = topWindow;
        }
    } while (topWindow);

    return swg::client::setupDirectInputInstall(hInstance, result, menuKey, unk);
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

        SetWindowLongPtr(Client::getHwnd(), GWL_WNDPROC, (LONG_PTR)swg::client::wndProc); // Sets WndProc to SWG's

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
    swg::client::setupDirectInputInstall = (swg::client::pSetupDirectInputInstall)Detour::Create((LPVOID)swg::client::setupDirectInputInstall, hkSetupDirectInputInstall, DETOUR_TYPE_PUSH_RET);
    swg::client::clientMain = (swg::client::pMainLoop)Detour::Create((LPVOID)swg::client::clientMain, hkMainLoop, DETOUR_TYPE_PUSH_RET);
}
}
