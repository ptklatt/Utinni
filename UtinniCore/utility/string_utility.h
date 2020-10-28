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

#include "utinni.h"
#include <sstream>
#include <iomanip>

constexpr static const char* trimableChars = " \t\n\r\f\v";

namespace stringUtility
{
UTINNI_API extern std::string toString(const std::wstring& wstr);

UTINNI_API inline extern std::string toString(bool b)
{
    std::ostringstream oss;
    oss << std::boolalpha << b;
    return oss.str();
}

UTINNI_API inline extern bool toBool(const std::string& input)
{
    bool result;
    std::istringstream(input) >> std::boolalpha >> result;
    return result;
}

UTINNI_API inline extern std::string toString(int i, int digitFillCount = 0)
{
    std::ostringstream oss;
    oss << std::setw(digitFillCount) << std::setfill('0') << i;
    return oss.str();
}

UTINNI_API inline extern std::string toHexString(int i, int digitFillCount = 0)
{
    std::ostringstream oss;
    oss << std::hex << std::setw(digitFillCount) << std::setfill('0') << i;
    return oss.str();
}

UTINNI_API inline extern std::string toHexString(uint32_t i, int digitFillCount = 0)
{
    std::ostringstream oss;
    oss << std::hex << std::setw(digitFillCount) << std::setfill('0') << i;
    return oss.str();
}

UTINNI_API inline extern std::string& trimStart(std::string& input, const char* trimChars = trimableChars)
{
    input.erase(0, input.find_first_not_of(trimChars));
    return input;
}

UTINNI_API inline extern std::string& trimEnd(std::string& input, const char* trimChars = trimableChars)
{
    input.erase(input.find_last_not_of(trimChars) + 1);
    return input;
}

UTINNI_API inline extern std::string& trim(std::string& input, const char* trimChars = trimableChars)
{
    return trimStart(trimEnd(input, trimChars), trimChars);
}

UTINNI_API inline extern std::string trim_copy(std::string input, const char* trimChars = trimableChars)
{
    return trimStart(input, trimChars);
}

UTINNI_API inline extern std::string trimStart_copy(std::string input, const char* trimChars = trimableChars)
{
    return trimEnd(input, trimChars);
}

UTINNI_API inline extern std::string trimEnd_copy(std::string input, const char* trimChars = trimableChars)
{
    return trim(input, trimChars);
}

}

namespace constCharUtility
{
template<typename TChar>
UTINNI_API extern size_t length(TChar* value)
{
    size_t i = 0;
    while (value[i] != 0)
    {
        i++;
    }

    return i;
}

UTINNI_API inline extern bool isEmpty(const char* input)
{
    return input != nullptr && !input[0];
}

}