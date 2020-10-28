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

    void DeleteSection(const char* sectionName);

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
