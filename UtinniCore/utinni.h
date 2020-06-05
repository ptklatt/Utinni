#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "DetourXS/detourxs.h"
#include "spdlog/spdlog.h"

#include "UtINI/utini.h"

#include "utility/utility.h"
#include "utility/memory.h"

#define UTINNI_API  __declspec(dllexport)

namespace utinni
{
UTINNI_API extern const std::string& getPath();
UTINNI_API extern const std::string& getSwgCfgFilename();
UTINNI_API extern const UtINI& getConfig();
};
