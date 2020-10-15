#pragma once

#include "utinni.h"

namespace utinni
{
class CommandParser;

class UTINNI_API CuiChatWindow // ToDo change to non static with getChatWindow func
{
public:
    static void addCreateCommandParserCallback(void(*func)(CommandParser* commandParser));

    static void enableTextInput(bool value);
    static void writeToAllTabs(const char* str);
    static void writeToCurrentTab(const char* str);
    static void sendMessage(const char* msg, bool addToChatHistory);

    static void detour();
};

}