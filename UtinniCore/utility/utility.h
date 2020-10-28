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

namespace utility
{
UTINNI_API extern void showMessageBox(const std::string& title, const std::string& text);
UTINNI_API extern void showMessageBox(const std::string& text);
UTINNI_API extern void showMessageBoxEmpty();
UTINNI_API extern void showLastErrorMessageBox();

UTINNI_API extern std::string getWorkingDirectory();

template <class T1, class T2>
UTINNI_API extern T1 union_cast(T2 v)
{
    static_assert(sizeof(T1) >= sizeof(T2), "Bad union_cast -- Size T1 is larger than T2");
    union UT { T1 t1; T2 t2; } u{};
    u.t2 = v;
    return u.t1;
}

}
