#include "cui_misc.h"
#include "utinni.h"

namespace utinni::cuiMisc
{
void patch()
{
    if (getConfig().getBool("UtinniCore", "enableOfflineScenes"))
    {
        // Enable the Load Scene button inside the login screen
        memory::nopAddress(0x00C8D250, 15);

        // Enable the Location button inside the ESC menu inside a scene
        byte locationBtnPatchBuffer[] = { 0x6A, 0x01, // push 1
                                          0x51, // push ecx
                                          0x8B, 0xCE, // mov ecx, esi
                                          0xE8, 0x17, 0x43, 0xD4, 0xFF }; // call client.9C18A0
        memory::copy(0x00C7D57F, locationBtnPatchBuffer);

    }
}
}