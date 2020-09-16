#include "string_utility.h"

namespace stringUtility
{
std::string toString(const std::wstring& wstr)
{
    if (wstr.empty())
    {
        return std::string();
    }

    const int strSize = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string result(strSize, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &result[0], strSize, nullptr, nullptr);
    return result;
}

}

namespace constCharUtility
{

}