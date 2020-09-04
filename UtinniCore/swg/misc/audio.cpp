#include "audio.h"

namespace swg::audio
{
using pSetMasterVolume = void(__cdecl*)(float volume);
pSetMasterVolume setMasterVolume = (pSetMasterVolume)0x00412C20;

using pGetMasterVolume = float(__cdecl*)();
pGetMasterVolume getMasterVolume = (pGetMasterVolume)0x00412C70;
}

namespace utinni::audio
{
void setMasterVolume(float volume)
{
    swg::audio::setMasterVolume(volume);
}

float getMasterVolume()
{
    return swg::audio::getMasterVolume();
}

}