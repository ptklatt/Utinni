#pragma once

#include "utinni.h"

namespace utinni
{
class CommandParser;

class UTINNI_API CuiChatWindow
{
public:
    static void addCommandParser(CommandParser* commandParser);
    static void detour();
};

}