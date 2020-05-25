#pragma once

#include "LeksysINI/iniparser.hpp"

namespace utinni
{
extern void loadConfig();
extern void saveConfig();
extern INI::File getConfig();

extern INI::Value getConfigValue(const char* sectionName, const char* valueName);
extern const char* getConfigString(const char* sectionName, const char* valueName);
extern bool getConfigBool(const char* sectionName, const char* valueName);
extern int getConfigInt(const char* sectionName, const char* valueName);
extern float getConfigFloat(const char* sectionName, const char* valueName);

extern void setConfigValue(const char* sectionName, const char* valueName, const INI::Value& value);
extern void setConfigString(const char* sectionName, const char* valueName, const char* value);
extern void setConfigBool(const char* sectionName, const char* valueName, bool value);
extern void setConfigInt(const char* sectionName, const char* valueName, int value);
extern void setConfigFloat(const char* sectionName, const char* valueName, float value);
}
