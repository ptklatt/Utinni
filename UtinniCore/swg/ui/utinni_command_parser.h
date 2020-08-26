#pragma once

#include "utinni.h"
#include "command_parser.h"
#include "swg/misc/swg_string.h"

namespace utinni
{
class UTINNI_API UtinniCommandParser : public CommandParser
{
public:
    UtinniCommandParser();
    bool performParsing(const int64_t& userId, const std::vector<swg::WString>& args, const wchar_t* originalCommand, const wchar_t* result, const CommandParser* node) override;
};
}
