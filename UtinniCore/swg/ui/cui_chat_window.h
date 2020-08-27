#pragma once

#include "utinni.h"

namespace utinni
{
class CommandParser;

class UTINNI_API CuiChatWindow
{
public:
    static void addCommandParser(CommandParser* commandParser);

    static void writeToAllTabs(const char* str);
    static void writeToCurrentTab(const char* str);
    static void sendMessage(const char* msg, bool addToChatHistory);

    static void detour();
};

}