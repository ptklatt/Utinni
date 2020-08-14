#include "cui_chat_window.h"
#include "command_parser.h"

namespace swg::cuiChatWindow
{

}

static std::vector<utinni::CommandParser*> commandParsers;

namespace utinni
{

void CuiChatWindow::addCommandParser(CommandParser* commandParser)
{
    commandParsers.emplace_back(commandParser);
}
CommandParser* mainCommandParser;
DWORD return_midCtor = 0x00F3679D;
__declspec(naked) void midCtor()
{
    DWORD pMainCommandParser;
    __asm
    {
        mov pMainCommandParser, ecx
        pushad
        pushfd
    }

    mainCommandParser = (CommandParser*)pMainCommandParser;
    for (CommandParser* commandParser : commandParsers)
    {
        mainCommandParser->addSubCommand(commandParser);
    }

    __asm
    {
        popfd
        popad
        mov eax, dword ptr ss : [esi - 0xE4]
        jmp[return_midCtor]
    }
}

void CuiChatWindow::detour()
{
    memory::createJMP((PBYTE)0x00F36797, (DWORD)midCtor, 6); // Mid CuiChatWindow::ctor detour
}
}
