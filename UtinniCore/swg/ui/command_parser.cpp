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
