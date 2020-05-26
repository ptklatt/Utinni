#pragma once

#include "windows.h"
#include "windowsx.h"
#include <iostream>
#include "io.h"
#include "fcntl.h"
#include "Tlhelp32.h"
#include "atlstr.h"
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cassert>
#include <string>

#include "DetourXS/detourxs.h"

#include "UtINI/utini.h"

#include "utility/utility.h"
#include "utility/memory.h"

#define UTINNI_API  __declspec(dllexport)

namespace utinni
{
	 extern std::string getPath();
	 extern std::string getSwgCfgFilename();
	 extern UtINI getConfig();
};
