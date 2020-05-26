#pragma once

#include "LeksysINI/iniparser.hpp"

#define UTINNI_API  __declspec(dllexport)

namespace utinni
{
UTINNI_API class UtINI
{
private:
    const char* filename;
    INI::File ini;

public:
    UtINI();
    UtINI(const char* filename);

    void load();
    void save();

    INI::Value getValue(const char* sectionName, const char* valueName);
    const char* getString(const char* sectionName, const char* valueName);
    bool getBool(const char* sectionName, const char* valueName);
    int getInt(const char* sectionName, const char* valueName);
    float getFloat(const char* sectionName, const char* valueName);

    void setValue(const char* sectionName, const char* valueName, const INI::Value& value);
    void setString(const char* sectionName, const char* valueName, const char* value);
    void setBool(const char* sectionName, const char* valueName, bool value);
    void setInt(const char* sectionName, const char* valueName, int value);
    void setFloat(const char* sectionName, const char* valueName, float value);
};
}
