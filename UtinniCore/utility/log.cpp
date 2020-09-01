#include "log.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/basic_file_sink.h>

namespace utinni::log
{

UtINI create()
{
    spdlog::set_level(spdlog::level::debug);

    spdlog::set_pattern("[%H:%M:%S] [%l]%! %v");
    spdlog::flush_on(spdlog::level::info);

    std::string logName = "utinni";
    std::string previousLogFilename = getPath() + logName + "_previous.log";
    std::string logFilename = getPath() + logName + ".log";

    // Delete previous log and rename the current log to previous log, so spdlog can create a clean new log
    std::remove(previousLogFilename.c_str());
    std::rename(logFilename.c_str(), previousLogFilename.c_str());

    auto file_logger = spdlog::basic_logger_mt("UtinniLog", logFilename);
    spdlog::set_default_logger(file_logger);

    return UtINI(std::string(getPath() + "ut.ini").c_str());
}

void critical(const char* text)
{
    spdlog::critical(text);
}

void debug(const char* text)
{
    spdlog::debug(text);
}

void error(const char* text)
{
    spdlog::error(text);
}

void info(const char* text)
{
    spdlog::info(text);
}

void warning(const char* text)
{
    spdlog::warn(text);
}
}
