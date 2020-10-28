/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#include "config.h"
#include "swg_utility.h"

namespace swg::config
{
using pLoadConfigFileBuffer = bool(__cdecl*)(byte* buffer, int bufferLength);
using pLoadConfigFileString = bool(__cdecl*)(const char* filename);
using pLoadOverrideConfig = int(__cdecl*)();

using pSetModalChat = void(__cdecl*)(bool value);
using pGetModalChat = bool(__cdecl*)();

pLoadConfigFileBuffer loadConfigFileBuffer = (pLoadConfigFileBuffer)0x00A9C6C0;
pLoadConfigFileString loadConfigFileString = (pLoadConfigFileString)0x00A9C780;
pLoadOverrideConfig loadOverrideConfig = (pLoadOverrideConfig)0x00401000;

pSetModalChat setModalChat = (pSetModalChat)0x00910A70;
pGetModalChat getModalChat = (pGetModalChat)0x00910D40;

bool loadConfigFile(byte* buffer, int bufferLength)
{
    return loadConfigFileBuffer(buffer, bufferLength);
}

bool loadConfigFile(const char* fileName)
{
    return loadConfigFileString(fileName);
}

void enableModalChat(bool value)
{
    setModalChat(value);
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
