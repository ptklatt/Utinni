#include "config.h"
#include "swg_utility.h"

namespace swg::config
{
using pLoadConfigFileBuffer = bool(__cdecl*)(byte* buffer, int bufferLength);
using pLoadConfigFileString = bool(__cdecl*)(const char* filename);
using pLoadOverrideConfig = int(__cdecl*)();

pLoadConfigFileBuffer loadConfigFileBuffer = (pLoadConfigFileBuffer)0x00A9C6C0;
pLoadConfigFileString loadConfigFileString = (pLoadConfigFileString)0x00A9C780;
pLoadOverrideConfig loadOverrideConfig = (pLoadOverrideConfig)0x00401000;

bool loadConfigFile(byte* buffer, int bufferLength)
{
    return loadConfigFileBuffer(buffer, bufferLength);
}

bool loadConfigFile(const char* fileName)
{
    return loadConfigFileString(fileName);
}

int __cdecl hkLoadOverrideConfig()
{
    const int result = loadOverrideConfig();

    swgptr pFile = utinni::treeFileOpen((utinni::getPath() + utinni::getSwgCfgFilename()).c_str(), 1, true);

    if (utinni::getConfig().getBool("UtinniCore", "useSwgOverrideCfg") && pFile != 0)
    {
        // ToDo clean this IDA pseudo paste up
        int length = (*(int(__thiscall**)(int))(*(swgptr*)pFile + 8))(pFile);
        byte* data = (byte*)(*(int(__thiscall**)(int))(*(swgptr*)pFile + 36))(pFile);
        loadConfigFileBuffer(data, length);
        delete[] data;
        pFile = (**(int(__thiscall***)(swgptr, swgptr))pFile)(pFile, 1);
    }

    return result;
}

void detour()
{
    loadOverrideConfig = (pLoadOverrideConfig)Detour::Create(loadOverrideConfig, hkLoadOverrideConfig, DETOUR_TYPE_PUSH_RET);
}

}

namespace swg::config::clientGame
{
const char* getSceneAvatarFilename()
{
    return memory::read<const char*>(0x1911218); // static address for "avatarSelection" in [ClientGame]
}

const char* getSceneTerrainFilename()
{
    return memory::read<const char*>(0x1911240); // static address for "groundScene" in [ClientGame]
}
}
