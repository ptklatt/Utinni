#pragma once

#include <string>

#define UTINNI_API  __declspec(dllexport)

namespace utinni
{
class UTINNI_API UtINI
{
public:
    UTINNI_API struct Value
    {
        enum Types
        {
            vt_iniValue,
            vt_string,
            vt_bool,
            vt_int,
            vt_float,
            vt_array,
            vt_map
        };

        std::string sectionName;
        std::string valueName;
        std::string value;
        Types type;
    };

    UtINI();
    UtINI(const std::string& filename);
    ~UtINI();

    void load() const;
    void load(const std::string& filename);
    void save() const;

    void createUtinniSettings() const;
    void addSetting(const Value& value) const;
    void addSetting(const char* sectionName, const char* valueName, const char* value, Value::Types type) const;

    std::string getString(const char* sectionName, const char* valueName) const;
    bool getBool(const char* sectionName, const char* valueName) const;
    int getInt(const char* sectionName, const char* valueName) const;
    float getFloat(const char* sectionName, const char* valueName) const;

    void setString(const char* sectionName, const char* valueName, const char* value) const;
    void setBool(const char* sectionName, const char* valueName, bool value) const;
    void setInt(const char* sectionName, const char* valueName, int value) const;
    void setFloat(const char* sectionName, const char* valueName, float value) const;

private:
    std::string iniFilename;

    // Need to use PIMPL to hide the std::vector<Value> settings, as cppSharp doesn't play nice with them
    struct Impl;
    Impl* pImpl{};

};
}
