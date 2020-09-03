#include "example_command_parser.h"


namespace example
{
static const utinni::CommandParser::CommandData commands[] =
{
    {"test1", 0, "", "Example Test Command 1"},
    {"test2", 0, "", "Example Test Command 2"}
};

ExampleCommandParser::ExampleCommandParser() : utinni::CommandParser("example", 0, "...", "Example related commands.", nullptr)
{
    for (const auto& command : commands)
    {
        addSubCommand(utinni::swg_new<CommandParser>(command, this));
    }
}

bool ExampleCommandParser::performParsing(const int64_t& userId, const std::vector<swg::WString>& args, const wchar_t* originalCommand, const wchar_t* result, const CommandParser* node)
{
    auto& cmd = args[0];

    if (cmd == "test1")
    {
        utility::showMessageBox("Example 1");
        return true;
    }

    swg::WString test2 = "test2";

    if (cmd == test2)
    {
        utility::showMessageBox("Example 2");
        return true;
    }

    return false;
}

void ExampleCommandParser::create(CommandParser* mainCommandParser)
{
    mainCommandParser->addSubCommand(utinni::swg_new<ExampleCommandParser>());
}
}
