#pragma once
#include "utinni.h"

namespace swg::config
{
extern bool loadConfigFile(byte* buffer, int bufferLength);
extern bool loadConfigFile(const char* fileName);

extern void detour();

}

namespace swg::config::clientGame
{
UTINNI_API extern const char* getSceneAvatarFilename();
UTINNI_API extern const char* getSceneTerrainFilename();
}
