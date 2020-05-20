#pragma once

#include "utinni.h"

namespace utility
{
extern void showMessageBox(const std::string& title, const std::string& text);
extern void showMessageBox(const std::string& text);
extern void showMessageBoxEmpty();
extern void showLastErrorMessageBox();
}