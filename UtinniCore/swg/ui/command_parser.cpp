#include "command_parser.h"

namespace swg::commandParser
{
using pCtor1 = utinni::CommandParser* (__thiscall*)(utinni::CommandParser* pThis, const char* command, size_t argCount, const char* args, const char* helpInfo, utinni::CommandParser* delegate);
using pCtor2 = utinni::CommandParser*(__thiscall*)(utinni::CommandParser* pThis, const utinni::CommandParser::CommandData& commandData, utinni::CommandParser* delegate);

using pCreateDelegateCommands = void(__thiscall*)(utinni::CommandParser* pThis, const utinni::CommandParser::CommandData commands[]);
using pAddSubCommand = utinni::CommandParser* (__thiscall*)(utinni::CommandParser* pThis, utinni::CommandParser* subCommand);

pCtor1 ctor1 = (pCtor1)0x00A83EF0;
pCtor2 ctor2 = (pCtor2)0x00A84130;

pCreateDelegateCommands createDelegateCommands = (pCreateDelegateCommands)0x00A862F0;
pAddSubCommand addSubCommand = (pAddSubCommand)0x00A85CD0;
}

namespace utinni
{
// Dummy virtual functions for the vtable that's to be overwritten by SWG's ctor
CommandParser::~CommandParser() { }
bool CommandParser::performParsing(const int64_t& userId, const std::vector<swg::WString>& args, const wchar_t* originalCommand, const wchar_t* result, const CommandParser* node) { return false; }
void CommandParser::unk_161E72C() { }

CommandParser::CommandParser(const char* command, size_t argCount, const char* args, const char* helpInfo, utinni::CommandParser* delegate)
{
    swg::commandParser::ctor1(this, command, argCount, args, helpInfo, delegate);
}

CommandParser::CommandParser(const CommandData& commandInfo, CommandParser* delegate)
{
    swg::commandParser::ctor2(this, commandInfo, delegate);
}

CommandParser* CommandParser::ctor(const CommandData& commandInfo, CommandParser* delegate)
{
    return swg::commandParser::ctor2((CommandParser*)allocate(sizeof(CommandParser)), commandInfo, delegate);
}

void CommandParser::createDelegateCommands(const CommandData commands[])
{
    swg::commandParser::createDelegateCommands(this, commands);
}

CommandParser* CommandParser::addSubCommand(CommandParser* subCommand)
{
    return swg::commandParser::addSubCommand(this, subCommand);
}


}
