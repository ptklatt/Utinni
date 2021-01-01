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

#pragma once

#include "utinni.h"
#include <set>
#include "swg/misc/swg_string.h"

namespace utinni
{

class UTINNI_API CommandParser // Size 0x3C / 60?
{
public:

    struct UTINNI_API CommandData
    {
        const char* command;
        size_t       argCount;
        const char* args;
        const char* helpInfo;
    };

    //swgptr vtbl;
    const swg::WString command;
    size_t argCount;
    swg::WString args;
    swg::WString helpInfo;
    bool unk0;

    CommandParser* parentParser;
    CommandParser* delegate;

    std::set<CommandParser*, swgptr>* subCommands;

    // Dummy virtual functions for the vtable that's to be overwritten by SWG's ctor
    virtual ~CommandParser() {}
    virtual bool performParsing(const int64_t& userId, const std::vector<swg::WString>& args, const wchar_t* originalCommand, const wchar_t* result, const CommandParser* node) { return false; }
    virtual void unk_161E72C() {}

    CommandParser(const char* command, size_t argCount, const char* args, const char* helpInfo, utinni::CommandParser* delegate);
    CommandParser(const CommandData& commandInfo, CommandParser* delegate);

    static CommandParser* ctor(const CommandData& commandInfo, CommandParser* delegate);

    void createDelegateCommands(const CommandData commands[]);
    CommandParser* addSubCommand(CommandParser* subCommand);

};

}


