#include "io_win.h"

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
