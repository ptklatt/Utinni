#pragma once

#include "utinni.h"

namespace utility
{
UTINNI_API extern void showMessageBox(const std::string& title, const std::string& text);
UTINNI_API extern void showMessageBox(const std::string& text);
UTINNI_API extern void showMessageBoxEmpty();
UTINNI_API extern void showLastErrorMessageBox();

UTINNI_API extern std::string getWorkingDirectory();
}
