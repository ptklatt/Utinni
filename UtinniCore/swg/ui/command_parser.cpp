#include "command_parser.h"
#include "swg/misc/swg_utility.h"

namespace swg::commandParser
{
using pCtor = utinni::CommandParser*(__thiscall*)(utinni::CommandParser* pThis, const utinni::CommandParser::CommandData& commandData, utinni::CommandParser* delegate);
using pAddSubCommand = utinni::CommandParser* (__thiscall*)(utinni::CommandParser* pThis, utinni::CommandParser* subCommand);

pCtor ctor = (pCtor)0x00A84130;
pAddSubCommand addSubCommand = (pAddSubCommand)0x00A85CD0;
}

namespace utinni
{
CommandParser* CommandParser::create(const CommandData& commandInfo, CommandParser* delegate)
{
    return swg::commandParser::ctor((CommandParser*)allocateMemory(sizeof(CommandParser)), commandInfo, delegate);
}

CommandParser* CommandParser::addSubCommand(CommandParser* subCommand)
{
    return swg::commandParser::addSubCommand(this, subCommand);
}

}
