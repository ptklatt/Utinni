#include "log.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/basic_file_sink.h>

static std::vector<std::string> logMessageBuffer;
static std::vector<void(*)(const char* msg)> outputSinkCallbacks;

namespace utinni::log
{
class OutputSink : public spdlog::sinks::base_sink<std::mutex>
{
public:
    OutputSink()
    {
        set_pattern("[%H:%M:%S] [%l]%! %v");
    }

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override
    {
        spdlog::memory_buf_t formatted;
        base_sink<std::mutex>::formatter_->format(msg, formatted);

        const std::string formattedString = fmt::to_string(formatted);

        logMessageBuffer.emplace_back(formattedString);
        for (const auto& func : outputSinkCallbacks)
        {
            func(formattedString.c_str());
        }
    }

    void flush_() override { }
};
    
void create()
{
    spdlog::set_level(spdlog::level::debug);

    spdlog::set_pattern("[%H:%M:%S] [%l]%! %v");
    spdlog::flush_on(spdlog::level::info);

    const std::string logName = "utinni";
    const std::string previousLogFilename = getPath() + logName + "_previous.log";
    const std::string logFilename = getPath() + logName + ".log";

    // Delete previous log and rename the current log to previous log, so spdlog can create a clean new log
    std::remove(previousLogFilename.c_str());
    std::rename(logFilename.c_str(), previousLogFilename.c_str());

    auto file_logger = spdlog::basic_logger_mt("UtinniLog", logFilename);
    file_logger->sinks().emplace_back(std::make_shared<OutputSink>());
    spdlog::set_default_logger(file_logger);

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

void addOutputSinkCallback(void(*func)(const char* msg))
{
    outputSinkCallbacks.emplace_back(func);
}

int getMessageBufferCount()
{
    return logMessageBuffer.size();
}

const char* getMessageAt(int i)
{
    return logMessageBuffer[i].c_str();
}

}
