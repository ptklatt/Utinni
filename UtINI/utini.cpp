#include "utini.h"

namespace utinni
{
struct IniValue
{
    std::string sectionName;
    std::string valueName;
    INI::Value value;
};

    // ToDo make a different array that's settable for other plugins
const static IniValue values[] = {

    // Launcher settings
    { "Launcher", "swgClientName", ""},
    { "Launcher", "swgClientName", ""},

    // UtinniCore settings
    { "UtinniCore", "isEditorChild", false},
    { "UtinniCore", "useSwgOverrideCfg", false},
    { "UtinniCore", "autoLoadScene", false},

    // Log settings
    { "Log", "writeClassName", false},
    { "Log", "writeFunctionName", false},
};

UtINI::UtINI() : filename(nullptr)
{
}

UtINI::UtINI(const char* filename) : filename(filename)
{
    load();
}

void UtINI::load()
{
    if (!ini.Load(filename))
    {
        // Save the default values to file
        for (const auto& iniValue : values)
        {
            ini.GetSection(iniValue.sectionName)->SetValue(iniValue.valueName, iniValue.value);
        }

        save();
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
            save();
        }
    }
}

void UtINI::save()
{
    ini.Save(filename);
}


INI::Value UtINI::getValue(const char* sectionName, const char* valueName)
{
    return ini.GetSection(sectionName)->GetValue(valueName);
}

const char* UtINI::getString(const char* sectionName, const char* valueName)
{
    static std::string result; // Temporary hack, fix it up the ini lib
    result = ini.GetSection(sectionName)->GetValue(valueName).AsString(); 
    return result.c_str();
}

bool UtINI::getBool(const char* sectionName, const char* valueName)
{
    return ini.GetSection(sectionName)->GetValue(valueName).AsBool();
}

int UtINI::getInt(const char* sectionName, const char* valueName)
{
    return ini.GetSection(sectionName)->GetValue(valueName).AsInt();
}

float UtINI::getFloat(const char* sectionName, const char* valueName)
{
    return ini.GetSection(sectionName)->GetValue(valueName).AsDouble();
}

void UtINI::setValue(const char* sectionName, const char* valueName, const INI::Value& value)
{
    ini.GetSection(sectionName)->SetValue(valueName, value);
}

void UtINI::setString(const char* sectionName, const char* valueName, const char* value)
{
    ini.GetSection(sectionName)->SetValue(valueName, value);
}

void UtINI::setBool(const char* sectionName, const char* valueName, bool value)
{
    ini.GetSection(sectionName)->SetValue(valueName, value);
}

void UtINI::setInt(const char* sectionName, const char* valueName, int value)
{
    ini.GetSection(sectionName)->SetValue(valueName, value);
}

void UtINI::setFloat(const char* sectionName, const char* valueName, float value)
{
    ini.GetSection(sectionName)->SetValue(valueName, value);
}
}
