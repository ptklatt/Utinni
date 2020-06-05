#include "log.h"
#include "spdlog/spdlog.h"

namespace utinni::log
{
void debug(const char* text)
{
    spdlog::debug(text);
}

void critical(const char* text)
{
    spdlog::critical(text);
}

void error(const char* text)
{
    spdlog::error(text);
}
void info(const char* text)
{
    spdlog::info(text);
}
}
