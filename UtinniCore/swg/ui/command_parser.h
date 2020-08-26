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
    virtual ~CommandParser();
    virtual bool performParsing(const int64_t& userId, const std::vector<swg::WString>& args, const wchar_t* originalCommand, const wchar_t* result, const CommandParser* node);
    virtual void unk_161E72C();

    CommandParser(const char* command, size_t argCount, const char* args, const char* helpInfo, utinni::CommandParser* delegate);
    CommandParser(const CommandData& commandInfo, CommandParser* delegate);

    static CommandParser* ctor(const CommandData& commandInfo, CommandParser* delegate);

    void createDelegateCommands(const CommandData commands[]);
    CommandParser* addSubCommand(CommandParser* subCommand);

};

}


