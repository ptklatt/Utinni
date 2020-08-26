#include "utinni_command_parser.h"

namespace utinni
{

static const CommandParser::CommandData commands[] =
{
    {"test1", 0, "", "Test Command 1"},
    {"test2", 0, "", "Test Command 2"}
};

UtinniCommandParser::UtinniCommandParser() : CommandParser("utinni", 0, "...", "Utinni related commands.", nullptr)
{
    for (const auto& command : commands)
    {
        addSubCommand(swg_new<CommandParser>(command, this));
    }
}

bool UtinniCommandParser::performParsing(const int64_t& userId, const std::vector<swg::WString>& args, const wchar_t* originalCommand, const wchar_t* result, const CommandParser* node)
{
    auto& cmd = args[0];

    if (cmd == "test1")
    {
        utility::showMessageBox("1");
        return true;
    }

    swg::WString test2 = "test2";

    if (cmd == test2)
    {
        utility::showMessageBox("2");
        return true;
    }

    return false;
}
}

