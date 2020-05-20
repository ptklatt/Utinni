#include <Windows.h>
#include <tchar.h>
#include <string>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <cstdio>
#include <stdexcept>

void inject(PROCESS_INFORMATION procInfo)
{
    char curDirBuffer[MAX_PATH];
    GetModuleFileName(nullptr, curDirBuffer, MAX_PATH);
    std::string curDir_tmp = std::string(curDirBuffer);
    std::string currentDir = curDir_tmp.substr(0, curDir_tmp.find_last_of('\\'));

    std::string dllFilename = currentDir + "\\UtinniCore.dll";
    LPVOID lpMemory = (LPVOID)VirtualAllocEx(procInfo.hProcess, nullptr, dllFilename.length(), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(procInfo.hProcess, lpMemory, (LPVOID)dllFilename.c_str(), dllFilename.length(), nullptr);

    LPVOID lpLoadLibraryA = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    HANDLE hThread = CreateRemoteThread(procInfo.hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)lpLoadLibraryA, lpMemory, 0, nullptr);
    if (!hThread)
        throw std::runtime_error("[ERROR] Couldn't open LoadLibraryA thread. Dll not injected.");

    if (WaitForSingleObject(hThread, INFINITE))
        throw std::runtime_error("[ERROR] Thread didn't return 0. Dll not injected.");

    DWORD hDll;
    if (!GetExitCodeThread(hThread, &hDll))
        throw std::runtime_error("[ERROR] Can't get LoadLibraryA return handle.");

    if (hDll == 0x00000000)
        throw std::runtime_error("[ERROR] LoadLibraryA couldn't inject dll.");
}

void loadDll()
{
    STARTUPINFOA StartupInfo = { 0 };
    StartupInfo.cb = sizeof(StartupInfo);
    PROCESS_INFORMATION procInfo;

    std::string swgClientPath = "G:/SWG Related/LoadTest/";
    std::string swgClientName = "MtgClient_LoadScene.exe";

    std::string swgClientFilename = swgClientPath + swgClientName;
    if (CreateProcess(swgClientFilename.c_str(), nullptr, nullptr, nullptr, false, CREATE_SUSPENDED, nullptr, swgClientPath.c_str(), &StartupInfo, &procInfo))
    {
        const HANDLE hProcess(procInfo.hProcess);

        try
        {
            // Locate the entry point
            HANDLE hFile = CreateFileA(swgClientFilename.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            LPVOID hFileMapping = CreateFileMapping(hFile, nullptr, PAGE_READONLY, 0, 0, nullptr);
            PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
            PIMAGE_NT_HEADERS peHeader = (PIMAGE_NT_HEADERS)((u_char*)dosHeader + dosHeader->e_lfanew);
            LPVOID entry = (LPVOID)(peHeader->OptionalHeader.ImageBase + peHeader->OptionalHeader.AddressOfEntryPoint);

            // store original entry point
            unsigned char oep[2];
            ReadProcessMemory(hProcess, entry, oep, 2, nullptr);

            // patch original entry point with ian infinite loop
            unsigned char patchedOep[]{ 0xEB, 0xFE };
            WriteProcessMemory(hProcess, entry, patchedOep, 2, nullptr);

            // Do patching here

            // Resume the main thread
            ResumeThread(procInfo.hThread);
            CONTEXT context{};

            // Wait until the main thread is stuck at the entry point
            for (unsigned int i = 0; i < 50 && context.Eip != (DWORD)entry; ++i)
            {
                Sleep(100);
                context.ContextFlags = CONTEXT_CONTROL;
                GetThreadContext(procInfo.hThread, &context);
            }
            if (context.Eip != (DWORD)entry)
            {
                // Wait timed out
                throw std::runtime_error("Timed out trying to reach the entry point");
            }

            // inject DLL
            inject(procInfo);

            SuspendThread(procInfo.hThread);
            WriteProcessMemory(hProcess, entry, oep, 2, nullptr); // Restore original entry point
            ResumeThread(procInfo.hThread);
        }
        catch (...)
        {
            TerminateProcess(hProcess, -1);
            throw;
        }
    }
    else
    {
        throw std::runtime_error("Unable to load the specified executable");
    }
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int main()
{
    loadDll();
    return 0;
}

