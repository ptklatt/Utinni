#include "cui_chat_window.h"
#include "command_parser.h"
#include "utinni_command_parser.h"
#include "swg/misc/swg_memory.h"

namespace swg::cuiChatWindow
{
using pCtor = DWORD (__thiscall*)(DWORD pThis, DWORD uiPage, DWORD unk1, DWORD unk2, DWORD unk3);

pCtor ctor = (pCtor)0x00F364B0;
}

static std::vector<utinni::CommandParser*> commandParsers;

namespace utinni
{

void CuiChatWindow::addCommandParser(CommandParser* commandParser)
{
    commandParsers.emplace_back(commandParser);
}

DWORD __fastcall hkCtor(DWORD pThis, void* useless, DWORD uiPage, DWORD unk1, DWORD unk2, DWORD unk3)
{
    commandParsers.emplace_back(swg_new<UtinniCommandParser>()); 
    return swg::cuiChatWindow::ctor(pThis, uiPage, unk1, unk2, unk3);
}

CommandParser* mainCommandParser;
DWORD return_midCtor = 0x00F3679D;
__declspec(naked) void midCtor()
{
    DWORD pMainCommandParser;
    __asm
    {
        mov pMainCommandParser, edx
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
        mov eax, dword ptr ss : [esi + 0xE4]
        jmp[return_midCtor]
    }
}

void CuiChatWindow::detour()
{
    swg::cuiChatWindow::ctor = (swg::cuiChatWindow::pCtor)Detour::Create(swg::cuiChatWindow::ctor, hkCtor, DETOUR_TYPE_PUSH_RET);

    memory::createJMP(0x00F36797, (swgptr)midCtor, 6); // Mid CuiChatWindow::ctor detour
}
}
