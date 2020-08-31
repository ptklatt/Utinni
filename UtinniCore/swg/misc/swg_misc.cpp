#include "swg_misc.h"

namespace swg::report
{
using pPrint = void(__cdecl*)(const char* msg);

pPrint print = (pPrint)0x00A88F90;
}

namespace utinni::report
{
void __cdecl hkPrint(const char* msg)
{
    swg::report::print(msg);

    std::string output = msg;

    // Check if the message contains newline's and remove them to not clog up the log
    if (output[output.length() - 1] == '\n')
    {
        output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
    }

    log::info(("[SWG] " + output).c_str());
}
void detour()
{
    swg::report::print = (swg::report::pPrint)Detour::Create(swg::report::print, hkPrint, DETOUR_TYPE_PUSH_RET);
}
}

