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

#include "swg_string.h"

namespace swg
{
constexpr int defaultInititalSize = 8; // 8 Is the default size in STLPort

WString::WString()
{
    begin = StringAllocator<char16_t>::allocate(defaultInititalSize);
    end = begin;
    allocEnd = end + defaultInititalSize;
}

WString::WString(const size_t size)
{
    begin = StringAllocator<char16_t>::allocate(size);
    end = begin;
    allocEnd = end + size;
}

WString::WString(const WString& value)
{
    create<char16_t>(value.begin);
}

WString::WString(const wchar_t* value)
{
    create<wchar_t>(value);
}

WString::WString(const char16_t* value)
{
    create<char16_t>(value);
}

WString::WString(const char* value)
{
    create<char>(value);
}

WString::~WString()
{
    if (begin != nullptr)
    {
        StringAllocator<char16_t>::deallocate(begin, allocEnd - begin);
    }
}

bool WString::operator==(const WString& rhs) const
{
    return compare<char16_t>(rhs.begin);
}

bool WString::operator==(const wchar_t* rhs) const
{
    return compare<wchar_t>(rhs);
}

bool WString::operator==(const char16_t* rhs) const
{
    return compare<char16_t>(rhs);
}

bool WString::operator==(const char* rhs) const
{
    return compare<char>(rhs);
}

bool WString::operator!=(const WString& rhs) const
{
    return !compare<char16_t>(rhs.begin);
}

bool WString::operator!=(const wchar_t* rhs) const
{
    return !compare<wchar_t>(rhs);
}

bool WString::operator!=(const char16_t* rhs) const
{
    return !compare<char16_t>(rhs);
}

bool WString::operator!=(const char* rhs) const
{
    return !compare<char>(rhs);
}

size_t WString::size() const
{
    return end - begin;
}

bool WString::isEmpty() const
{
    return size() == 0;
}

std::string WString::toString() const
{
    if (isEmpty())
    {
        return std::string();
    }

    const int strSize = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)begin, (int)size(), nullptr, 0, nullptr, nullptr);
    std::string result(strSize, 0);
    WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)begin, (int)size(), &result[0], strSize, nullptr, nullptr);
    return result;
}
}
