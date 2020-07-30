#pragma once

#include "utinni.h"

namespace utinni::log
{
UTINNI_API extern void critical(const char* text);
UTINNI_API extern void debug(const char* text);
UTINNI_API extern void error(const char* text);
UTINNI_API extern void info(const char* text);
UTINNI_API extern void warning(const char* text);
}