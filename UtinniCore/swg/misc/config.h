#pragma once
#include "utinni.h"

namespace swg::config
{
extern bool loadConfigFile(byte* buffer, int bufferLength);
extern bool loadConfigFile(const char* fileName);
UTINNI_API void enableModalChat(bool value);

extern void detour();
}

namespace swg::config::clientGame
{
UTINNI_API extern const char* getSceneAvatarFilename();
UTINNI_API extern const char* getSceneTerrainFilename();
}
