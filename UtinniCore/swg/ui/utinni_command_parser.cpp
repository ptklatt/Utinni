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

