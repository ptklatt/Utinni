#pragma once

#include "utinni.h"

namespace utinni
{

UTINNI_API extern unsigned int calculateCrc(const char* string);

UTINNI_API extern swgptr treeFileOpen(const char* filename, int priorityType, bool allowFail);

}
