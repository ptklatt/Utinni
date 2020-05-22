#include "direct_input.h"
#include "swg/client/client.h"
#include "swg/graphics/graphics.h"

namespace swg::directInput
{
using pSuspend = void(__cdecl*)();
using pResume = void(__cdecl*)();
using pSetupInstall = int(__cdecl*)(HINSTANCE hInstance, HWND hwnd, DWORD menuKey, DWORD unk);

pSuspend suspend = (pSuspend)0x00420880;
pSuspend resume = (pSuspend)0x00420890;

pSetupInstall setupInstall = (pSetupInstall)0x00421490;
}

namespace utinni
{
void DirectInput::suspend()
{
    swg::directInput::suspend();
}

void DirectInput::resume()
{
    swg::directInput::resume();
}

int __cdecl hkSetupInstall(HINSTANCE hInstance, HWND hwnd, DWORD menuKey, DWORD unk)
{
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

    // Create the main cursor and write its pointer to the global SWG Cursor address
    memory::write<HCURSOR>(0x0193C5E0, LoadCursor(nullptr, IDC_ARROW)); // SWG's HCURSOR address

    Graphics::useHardwareCursor(false); // Turning this to false makes the game render its own cursor

    return swg::directInput::setupInstall(GetModuleHandle(NULL), result, menuKey, unk);
}

void DirectInput::detour()
{
    swg::directInput::setupInstall = (swg::directInput::pSetupInstall)Detour::Create((LPVOID)swg::directInput::setupInstall, hkSetupInstall, DETOUR_TYPE_PUSH_RET);
}
}
