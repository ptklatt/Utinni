#include "utinini.h"
#include <windows.h>
#include <libloaderapi.h>

namespace utinni
{
static INI::File ini;

std::string currentDir;
std::string iniName = "ut.ini";

struct IniValue
{
    std::string sectionName;
    std::string valueName;
    INI::Value value;
};

const static IniValue values[] = {

    // Launcher settings
    { "Launcher", "swgClientName", ""},
    { "Launcher", "swgClientName", ""},

    // UtinniCore settings
    { "UtinniCore", "isEditorChild", false}
};

std::string getIniFilename()
{
    return currentDir + iniName;
}

void loadConfig()
{
    char curDirBuffer[MAX_PATH];
    HMODULE handle = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&getIniFilename, &handle);
    GetModuleFileNameA(handle, curDirBuffer, sizeof(curDirBuffer));
    const std::string path = std::string(curDirBuffer);
    currentDir = path.substr(0, path.find_last_of("\\/")) + "\\";

    if (!ini.Load(getIniFilename()))
    {
        // Save the default values to file
        for (const auto& iniValue : values)
        {
            ini.GetSection(iniValue.sectionName)->SetValue(iniValue.valueName, iniValue.value);
        }

        saveConfig();
    }
    else
    {
        // Validate the loaded values to make sure all needed values exist, if not, create them
        bool missingValues = false;
        for (const auto& iniValue : values)
        {
            if (ini.GetSection(iniValue.sectionName)->GetValue(iniValue.valueName).AsString().empty())
            {
                ini.GetSection(iniValue.sectionName)->SetValue(iniValue.valueName, iniValue.value);
                missingValues = true;
            }
        }

        if (missingValues)
        {
            saveConfig();
        }
    }
}
void saveConfig()
{
    ini.Save(getIniFilename());
}

INI::File getConfig()
{
    return ini;
}

INI::Value getConfigValue(const std::string& sectionName, const std::string& valueName)
{
    return ini.GetSection(sectionName)->GetValue(valueName);
}

void setConfigValue(const std::string& sectionName, const std::string& valueName, const INI::Value& value)
{
    ini.GetSection(sectionName)->SetValue(valueName, value);
}

}