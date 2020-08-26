#pragma once

#include "utinni.h"

namespace utinni
{

extern unsigned int calculateCrc(const char* string);

extern DWORD treeFileOpen(const char* filename, int priorityType, bool allowFail);

}
