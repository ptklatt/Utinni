#pragma once

#include "utinni.h"

namespace utility
{
UTINNI_API extern void showMessageBox(const std::string& title, const std::string& text);
UTINNI_API extern void showMessageBox(const std::string& text);
UTINNI_API extern void showMessageBoxEmpty();
UTINNI_API extern void showLastErrorMessageBox();

UTINNI_API extern std::string getWorkingDirectory();

template <class T1, class T2>
UTINNI_API extern T1 union_cast(T2 v)
{
    static_assert(sizeof(T1) >= sizeof(T2), "Bad union_cast -- Size T1 is larger than T2");
    union UT { T1 t1; T2 t2; } u{};
    u.t2 = v;
    return u.t1;
}

}
