#include <Windows.h>
#include <string>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <stdexcept>
#include <filesystem>

// import EnvDTE to allow the auto attaching of VisualStudio to the created process
#include <atlbase.h>
#include <cassert>
#pragma warning(disable : 4278)
#pragma warning(disable : 4146)
#import "libid:80cc9f66-e7d8-4ddd-85b6-d9e6cd0e93e2" version("16.0") lcid("0") raw_interfaces_only named_guids
#pragma warning(default : 4146)
#pragma warning(default : 4278)

#include "UtINI/utini.h"

// ToDo Current issues: It doesn't seem to reliably attach and it seems to detect the first available VS instance, if multiple are open
EnvDTE::Process* findVisualStudioProcess(DWORD targetPID)
{
    CoInitialize(nullptr);

    CLSID Clsid;
    CLSIDFromProgID(L"VisualStudio.DTE", &Clsid);

    HRESULT hr;

    IUnknown* unk;
    hr = GetActiveObject(Clsid, nullptr, &unk);
    assert(SUCCEEDED(hr));

    EnvDTE::_DTE* dteInterface;
    hr = unk->QueryInterface(&dteInterface);
    assert(SUCCEEDED(hr));

    EnvDTE::Debugger* debugger;
    hr = dteInterface->get_Debugger(&debugger);
    assert(SUCCEEDED(hr));

    EnvDTE::Processes* processes;
    hr = debugger->get_LocalProcesses(&processes);
    long count = 0;
    assert(SUCCEEDED(hr));

    hr = processes->get_Count(&count);
    for (int i = 0; i < count; i++)
    {
        EnvDTE::Process* process;
        hr = processes->Item(variant_t(i), &process);
        if (FAILED(hr))
            continue;

        long pid;
        hr = process->get_ProcessID(&pid);
        assert(SUCCEEDED(hr));
        if (pid == targetPID)
        {
            return process;
        }
    }

    return nullptr;
}

void attachToVisualStudio(DWORD targetPID)
{
    EnvDTE::Process* process = findVisualStudioProcess(targetPID);

    if (process != nullptr)
    {
        process->Attach();
    }

    CoUninitialize();
}

void inject(PROCESS_INFORMATION procInfo)
{
    char curDirBuffer[MAX_PATH];
    GetModuleFileName(nullptr, curDirBuffer, MAX_PATH);
    std::string currentDir = std::string(curDirBuffer);
    currentDir = currentDir.substr(0, currentDir.find_last_of('\\') + 1);

    std::string dllFilename = currentDir + "UtinniCore.dll";
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

std::string swgClientPath;

std::string getSwgClientFilename()
{
    char curDirBuffer[MAX_PATH];
    HMODULE handle = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&inject, &handle);
    GetModuleFileNameA(handle, curDirBuffer, sizeof(curDirBuffer));
    const std::string path = std::string(curDirBuffer);
    std::string iniFilename = path.substr(0, path.find_last_of("\\/")) + "\\ut.ini";

    utinni::UtINI ini(iniFilename.c_str());

    swgClientPath = ini.getString("Launcher", "swgClientPath");
    std::string swgClientName = ini.getString("Launcher", "swgClientName");

    if (swgClientPath.empty() || swgClientName.empty() || !swgClientName.find(".exe") || !std::filesystem::exists(swgClientPath + swgClientName))
    {
        char filenameBuffer[MAX_PATH];

        OPENFILENAME ofn;
        ZeroMemory(&filenameBuffer, sizeof(filenameBuffer));
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = nullptr;
        ofn.lpstrFilter = "Executable Files\0*.exe\0";
        ofn.lpstrFile = filenameBuffer;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrTitle = "Please select your SWG Client";
        ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

        if (GetOpenFileNameA(&ofn))
        {
            const std::string filename = std::string(filenameBuffer);
            const int lastSlashPos = filename.find_last_of('\\');
            swgClientPath = filename.substr(0, lastSlashPos + 1);
            swgClientName = filename.substr(lastSlashPos + 1);

            ini.setValue("Launcher", "swgClientPath", swgClientPath);
            ini.setValue("Launcher", "swgClientName", swgClientName);

            ini.save();
        }
        else
        {
            throw std::runtime_error("[ERROR] Can't open the selected file.");
        }
    }

    return swgClientPath + swgClientName;
}

void loadDll()
{
    STARTUPINFOA StartupInfo = { 0 };
    StartupInfo.cb = sizeof(StartupInfo);
    PROCESS_INFORMATION procInfo;

    const std::string swgClientFilename = getSwgClientFilename();
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

            // Attach the debugger before we inject, only do this in RelWithDbgInfo or Debug configuration 
            #if defined RELDBG  || defined  _DEBUG 
            // ToDo add an .ini setting to enable or disable it, commented out for now until there is a setting
            //attachToVisualStudio(procInfo.dwProcessId);
            #endif

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


