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
#include "swg_memory.h"
#include "utility/string_utility.h"

// STLPort 4.5.3 wide string implementation that SWG uses

namespace swg
{
template<typename TChar>
class StringAllocator
{
public:
    static TChar* allocate(const size_t size)
    {
        const size_t sizeTotal = size * sizeof(TChar);

        if (sizeTotal <= 128)
        {
            return (TChar*)utinni::allocateString(sizeTotal);
        }

        // Uses the main allocator if size is above 0x80 / 128, see 0x00A8D365:
        /*
        if ((unsigned int)(12 * v15) <= 0x80)
            v17 = sub_12EA770(v22); // string allocator
        else
            v17 = (char*)sub_AC15C0(v22); // main allocator
        */

        return (TChar*)utinni::allocate(sizeTotal);
    }

    static void deallocate(TChar* address, const size_t size)
    {
        const size_t sizeTotal = size * sizeof(TChar);

        if (sizeTotal <= 128)
        {
            utinni::deallocateString((void*)address, sizeTotal);
        }
        else
        {
            utinni::deallocate((void*)address, sizeTotal);
        }
    }
};

class UTINNI_API WString
{
private:
    char16_t* begin{};
    char16_t* end{};
    char16_t* allocEnd{};

private:
    template<typename TChar>
    void create(const TChar* value)
    {
        const size_t size = constCharUtility::length(value);

        begin = StringAllocator<char16_t>::allocate(size + 1);
        end = begin + size;
        allocEnd = end + 1;

        for (uint32_t i = 0; i < size; ++i)
        {
            begin[i] = value[i];
        }

        memory::write<char16_t>((swgptr)end, 0); // Ensure the end is zero'd
    }

    template<typename TCharRhs>
    bool compare(const TCharRhs* rhs) const 
    {
        const char16_t* iterLhs = begin;
        const TCharRhs* iterRhs = rhs;

        while (*iterLhs)
        {
            if (*iterLhs++ != *iterRhs++)
            {
                return false;
            }
        }

        return *iterRhs == 0;
    }

public:
    WString();
    WString(const size_t size);
    WString(const WString& value);
    WString(const wchar_t* value);
    WString(const char16_t* value);
    WString(const char* value);

    ~WString();

    bool operator==(const WString& rhs) const;
    bool operator==(const wchar_t* rhs) const;
    bool operator==(const char16_t* rhs) const;
    bool operator==(const char* rhs) const;

    bool operator!=(const WString& rhs) const;
    bool operator!=(const wchar_t* rhs) const;
    bool operator!=(const char16_t* rhs) const;
    bool operator!=(const char* rhs) const;

    size_t size() const;
    bool isEmpty() const;

    std::string toString() const;

private:


};
}

