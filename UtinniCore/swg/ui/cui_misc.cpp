#include "cui_misc.h"

namespace swg::cuiMisc
{
using pSwgCuiHudFactoryReloadUi = void(__cdecl*)();

pSwgCuiHudFactoryReloadUi swgCuiHudFactoryReloadUi = (pSwgCuiHudFactoryReloadUi)0x00BAA7E0;
}

namespace utinni::cuiMisc
{
void reloadUi()
{
    memory::write<bool>(0x01926138, true); // Todo what is this again?
    swg::cuiMisc::swgCuiHudFactoryReloadUi();
}

void patch()
{
    if (getConfig().getBool("UtinniCore", "enableOfflineScenes"))
    {
        // Enable the Load Scene button inside the login screen
        memory::nopAddress(0x00C8D250, 15);

        // Enable the Location button inside the ESC menu inside a scene
        static constexpr byte locationBtnPatchBuffer[] = { 0x6A, 0x01, // push 1
                                          0x51, // push ecx
                                          0x8B, 0xCE, // mov ecx, esi
                                          0xE8, 0x17, 0x43, 0xD4, 0xFF }; // call client.9C18A0
        memory::copy(0x00C7D57F, locationBtnPatchBuffer);


        // Disable the CUI resize based on RESO chunk in settings
        memory::nopAddress(0x009CC385, 6); // Removes RESO.Y changing CUI.X
        memory::nopAddress(0x009CC39C, 5); // Removes RESO.Y changing CUI.Y
        memory::nopAddress(0x009CC3BD, 3); // Removes isOk bool being set to false
    }
}
}