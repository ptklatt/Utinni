#pragma once

#include "utinni.h"

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

    DWORD vtbl;
    std::wstring command;
    size_t argCount;
    std::wstring args;
    std::wstring helpInfo;
    bool unk0;

    CommandParser* parentParser;
    CommandParser* delegate;

    DWORD unk1;
    DWORD unk2;
    DWORD unk3;
    DWORD unk4;
    DWORD unk5;
    DWORD unk6;
    DWORD unk7;

    static CommandParser* create(const CommandData& commandInfo, CommandParser* delegate);

    CommandParser* addSubCommand(CommandParser* subCommand);

};

}


