#pragma once

#include "utinni.h"

namespace utinni
{
struct StartupData
{
    bool createOwnWindow; //0x0000 
    const char* windowName; //0x0004 
    HICON normalIcon; //0x0008 
    HICON smallIcon; //0x000C 
    HINSTANCE hInstance; //0x0010 

    bool useNewWindowHandle; //0x0014 
    bool processMessagePump; //0x0015 
    HWND windowHandle; //0x0018 

    bool writeMiniDumps; //0x001C 
    bool unk1; //0x001D 
    bool unk2; //0x001E 

    const char* commandLine; //0x0020 
    int argc; //0x0024 
    char** argv; //0x0028 
    const char* configFile; //0x002C 
    const char* unk3; //0x0030

    float frameRateLimit; //0x0034

    bool unk4; //0x0038 
    bool unk5;
    swgptr lostFocusCallback;
};

class UTINNI_API Client
{
public:
    static void setEditorMode(bool enable);
    static bool getEditorMode();

    static void setHwnd(void* newHwnd);
    static HWND getHwnd();
    static void setHInstance(void* newHInstance);
    static HINSTANCE getHInstance();

    static void setSize(int width, int height);
    static int getWidth();
    static int getHeight();

    static void suspendInput();
    static void resumeInput();
    static bool isInputAllowed();

    static void detour();
};


}
