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

#include "UtinINI/utinini.h"

#include "utility/utility.h"
#include "utility/memory.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(a) { if((a)) { delete (a); (a) = NULL; } }
#endif
#define UTINNI_API  __declspec(dllexport)

class UtinniBase
{
private:
	 UtinniBase();

public:
	 static UtinniBase* instance();

	 bool initialize();
	 ~UtinniBase();

	 void cleanUpHook();
};

class Utinni
{
private:
	 Utinni();

public:
	 ~Utinni();
	 static Utinni* instance();

	 static std::string getPath();
	 static std::string getSwgCfgFilename();
};
