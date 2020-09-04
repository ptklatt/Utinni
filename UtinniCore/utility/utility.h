#pragma once

#include "utinni.h"

namespace utility
{
UTINNI_API extern void showMessageBox(const std::string& title, const std::string& text);
UTINNI_API extern void showMessageBox(const std::string& text);
UTINNI_API extern void showMessageBoxEmpty();
UTINNI_API extern void showLastErrorMessageBox();

UTINNI_API extern std::string getWorkingDirectory();

UTINNI_API extern std::string wstring_to_string(const std::wstring& wstr);

template<typename TChar>
UTINNI_API extern size_t stringLength(TChar* value)
{
    size_t i = 0;
    while (value[i] != 0)
    {
        i++;
    }

    return i;
}

UTINNI_API extern bool isEmpty(const char* input);
}
