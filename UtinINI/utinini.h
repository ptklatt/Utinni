#pragma once

#include "LeksysINI/iniparser.hpp"

namespace utinni
{
extern void loadConfig();
extern void saveConfig();
extern INI::File getConfig();

extern INI::Value getConfigValue(const std::string& sectionName, const std::string& valueName);
extern void setConfigValue(const std::string& sectionName, const std::string& valueName, const INI::Value& value);

}