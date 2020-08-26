#pragma once

#include "utinni.h"

namespace utility
{
extern void showMessageBox(const std::string& title, const std::string& text);
extern void showMessageBox(const std::string& text);
extern void showMessageBoxEmpty();
extern void showLastErrorMessageBox();

extern std::string getWorkingDirectory();

extern std::string wstring_to_string(const std::wstring& wstr);

template<typename TChar>
extern size_t stringLength(TChar* value)
{
    size_t i = 0;
    while (value[i] != 0)
    {
        i++;
    }

    return i;
}
}
