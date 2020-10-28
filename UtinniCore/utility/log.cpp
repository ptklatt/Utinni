/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

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
