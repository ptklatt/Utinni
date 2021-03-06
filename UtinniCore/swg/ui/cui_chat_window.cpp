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

#include "cui_chat_window.h"
#include "command_parser.h"
#include "utinni_command_parser.h"
#include "swg/misc/swg_memory.h"

namespace swg::cuiChatWindow
{
using pCtor = swgptr(__thiscall*)(swgptr pThis, swgptr uiPage, DWORD unk1, DWORD unk2, DWORD unk3);
using pEnableTextInput = void(__thiscall*)(swgptr pThis, bool value, bool setKeyboardInput, bool unfocus);
using pWriteToTab = swgptr(__thiscall*)(swgptr pThis, const WString& str);

pCtor ctor = (pCtor)0x00F364B0;
pEnableTextInput enableTextInput = (pEnableTextInput)0x00F38500;
pWriteToTab writeToAllTabs = (pWriteToTab)0x00F3BFD0;
pWriteToTab writeToCurrentTab = (pWriteToTab)0x00F3C1F0;
}

namespace swg::cuiConsoleHelper
{
using pSendInput = bool(__thiscall*)(swgptr pThis, const swg::WString& str, swgptr unk, bool addToChatHistory);
pSendInput sendInput = (pSendInput)0x009141D0;

}

static swgptr pCuiChatWindow; // ToDo use the getChatWindow function instead of the ctor detour?
static swgptr pCuiConsoleHelper;
static std::vector<void(*)(utinni::CommandParser* mainCommandParser)> addCommandParserCallback;

namespace utinni
{
bool enableInput;

void CuiChatWindow::addCreateCommandParserCallback(void(*func)(CommandParser* commandParser))
{
    addCommandParserCallback.emplace_back(func);
}

void CuiChatWindow::enableTextInput(bool value) // Accepts color codes by prefixing them with \\, ie "\\#888888 test"
{
    enableInput = value;
}

void CuiChatWindow::writeToAllTabs(const char* str)
{
    if (pCuiChatWindow == 0)
    {
        return;
    }

    swg::cuiChatWindow::writeToAllTabs(pCuiChatWindow, swg::WString(str));
}

void CuiChatWindow::writeToCurrentTab(const char* str) // Accepts color codes by prefixing them with \\, ie "\\#888888 test"
{
    if (pCuiChatWindow == 0)
    {
        return;
    }

    swg::cuiChatWindow::writeToCurrentTab(pCuiChatWindow, swg::WString(str));
}

void CuiChatWindow::sendMessage(const char* msg, bool addToChatHistory)
{
    if (pCuiChatWindow == 0 || pCuiConsoleHelper == 0)
    {
        return;
    }

    // Due to the unknown, most likely old std parameter in sendInput,
    // which we don't need for the purpose of this function anyway,
    // we need to patch out calls utilizing that parameter inside the SWG function,
    // else we crash due to access violations
    const auto origBytes1 = memory::nopAddress(0x00914245, 5);
    const auto origBytes2 = memory::nopAddress(0x00914250, 5);
    const auto origBytes3 = memory::nopAddress(0x0091425D, 5);
    const auto origBytes4 = memory::nopAddress(0x0091427D, 5);
    const auto origBytes5 = memory::nopAddress(0x009142E4, 5);

    memory::set(0x0091428C, 0x75, 1);

    swg::cuiConsoleHelper::sendInput(pCuiConsoleHelper, swg::WString(msg), 0, addToChatHistory);

    // Once the call has been made, the function needs to be restored
    // for potential swg calls that might utilize the parameter
    memory::restoreBytes(origBytes1);
    memory::restoreBytes(origBytes2);
    memory::restoreBytes(origBytes3);
    memory::restoreBytes(origBytes4);
    memory::restoreBytes(origBytes5);

    memory::set(0x0091428C, 0x74, 1);
}

void __fastcall hkEnableTextInput(swgptr pThis, swgptr EDX, bool value, bool setKeyboardInput, bool unfocus)
{
    swg::cuiChatWindow::enableTextInput(pCuiChatWindow, value, setKeyboardInput, unfocus);
}

CommandParser* mainCommandParser;
swgptr __fastcall hkCtor(swgptr pThis, swgptr EDX, swgptr uiPage, DWORD unk1, DWORD unk2, DWORD unk3)
{
    swgptr result = swg::cuiChatWindow::ctor(pThis, uiPage, unk1, unk2, unk3);
    pCuiChatWindow = pThis;
    pCuiConsoleHelper = memory::read<swgptr>(pThis + 0xBC); // Store the CuiConsoleHelper* for later use

    mainCommandParser->addSubCommand(swg_new<UtinniCommandParser>());

    for (const auto& func : addCommandParserCallback)
    {
        func(mainCommandParser);
    }

    return result;
}

swgptr return_midCtor = 0x00F3679D;
__declspec(naked) void midCtor()
{
    swgptr pMainCommandParser;
    __asm
    {
        mov pMainCommandParser, edx
        pushad
        pushfd
    }

    mainCommandParser = (CommandParser*)pMainCommandParser;

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
    //swg::cuiChatWindow::enableTextInput = (swg::cuiChatWindow::pEnableTextInput)Detour::Create(swg::cuiChatWindow::enableTextInput, hkEnableTextInput, DETOUR_TYPE_PUSH_RET);

    memory::createJMP(0x00F36797, (swgptr)midCtor, 6); // Mid CuiChatWindow::ctor detour
}

}
