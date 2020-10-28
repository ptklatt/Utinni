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

#include "utility.h"

namespace utility
{
void showMessageBox(const std::string& title, const std::string& text)
{
    MessageBoxA(nullptr, text.c_str(), title.c_str(), MB_OK);
}

void showMessageBox(const std::string& text)
{
    MessageBoxA(nullptr, text.c_str(), "", MB_OK);
}

void showMessageBoxEmpty()
{
    MessageBoxA(nullptr, "", "", MB_OK);
}

void showLastErrorMessageBox()
{
    DWORD errorMessageId = GetLastError();

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, errorMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, nullptr);

    std::string message(messageBuffer, size);

    LocalFree(messageBuffer);
    MessageBox(0, message.c_str(), "Error", MB_OK);
}

std::string getWorkingDirectory()
{
    char buffer[FILENAME_MAX];
    GetCurrentDirectory(FILENAME_MAX, buffer);
    return buffer;
}

std::string wstring_to_string(const std::wstring& wstr)
{
    if (wstr.empty()) 
        return std::string();

    int strSize = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string str(strSize, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], strSize, nullptr, nullptr);
    return str;
}


}
