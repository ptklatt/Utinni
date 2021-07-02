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

#include "io_win.h"

namespace swg::ioWin
{
using pDraw = void(__thiscall*)(utinni::IoWin* pThis);

pDraw draw = (pDraw)0x00AB58E0;
}

namespace swg::messageQueue
{
using pGetCount = int(__thiscall*)(utinni::MessageQueue* pThis);
using pGetMessage = void(__thiscall*)(utinni::MessageQueue* pThis, int index, int* msg, float* value, uint32_t* flags);
using pAppendMessage = void(__thiscall*)(utinni::MessageQueue* pThis, int msg, float value, uint32_t* flags);
using pAppendMessageData = void(__thiscall*)(utinni::MessageQueue* pThis, int msg, float value, swgptr data, uint32_t* flags);

pGetCount getCount = (pGetCount)0x00AA6660;
pGetMessage getMessage = (pGetMessage)0x00AA63B0;
pAppendMessage appendMessage = (pAppendMessage)0x00AA6640;
pAppendMessageData appendMessageData = (pAppendMessageData)0x00AA6480;
}

namespace utinni
{

void __fastcall hkDraw(IoWin* pThis, swgptr EDX)
{
    swg::ioWin::draw(pThis);
}
void IoWin::detour()
{
    //swg::ioWin::draw = (swg::ioWin::pDraw)Detour::Create(swg::ioWin::draw, hkDraw, DETOUR_TYPE_PUSH_RET);
}

int MessageQueue::getCount()
{
    return swg::messageQueue::getCount(this);
}

void MessageQueue::getMessage(int index, int* msg, float* value)
{
    swg::messageQueue::getMessage(this, index, msg, value, nullptr);
}

void MessageQueue::appendMessage(int msg, float value)
{
    swg::messageQueue::appendMessage(this, msg, value, nullptr);
}

void MessageQueue::appendMessage(int msg, float value, swgptr data)
{
    swg::messageQueue::appendMessageData(this, msg, value, data, nullptr);
}
}
