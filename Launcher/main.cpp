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

#include <Windows.h>
#include <string>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <stdexcept>
#include <filesystem>

// Import EnvDTE to allow the auto attaching of VisualStudio to the created process
//#if defined RELDBG  || defined  _DEBUG 
//#include <atlbase.h>
//#include <cassert>
//#pragma warning(disable : 4278)
//#pragma warning(disable : 4146)
//#import "libid:80cc9f66-e7d8-4ddd-85b6-d9e6cd0e93e2" version("8.0") lcid("0") raw_interfaces_only named_guids
//#pragma warning(default : 4146)
//#pragma warning(default : 4278)
//#endif

#include "UtINI/utini.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // Disables the popping up of the console
#pragma comment(lib, "version.lib") // To use GetFileVersionInfo, etc

void throwError(const std::string& message)
{
    MessageBoxA(nullptr, message.c_str(), "Error", MB_OK);
    throw std::runtime_error(message);
}

//DWORD getParentPID()
//{
//    const DWORD PID = GetCurrentProcessId();
//    DWORD parentPID = 0;
//
//    PROCESSENTRY32 pe32;
//    pe32.dwSize = sizeof(pe32);
//
//    const HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//    if (hSnapshot == INVALID_HANDLE_VALUE || !Process32First(hSnapshot, &pe32))
//        return 0;
//
//    do 
//    {
//        if (pe32.th32ProcessID == PID) 
//        {
//            parentPID = pe32.th32ParentProcessID;
//            break;
//        }
//    } while (Process32Next(hSnapshot, &pe32));
//
//    CloseHandle(hSnapshot);
//    return parentPID;
//}

// ToDo Current issues: It doesn't seem to reliably attach
//EnvDTE::Process* findVisualStudioProcess(DWORD targetPID)
//{
//    CoInitialize(nullptr);
//
//    HRESULT hr;
//
//    // Gets the Running Object Table, which contains all display names of current processes
//    CComPtr<IRunningObjectTable> pROT;
//    hr = GetRunningObjectTable(0, &pROT);
//    assert(SUCCEEDED(hr));
//
//    IEnumMoniker* enumMoniker;
//    pROT->EnumRunning(&enumMoniker);
//
//    DWORD fetched;
//    CComPtr<IMoniker> pMoniker;
//
//    IUnknown* pObj = nullptr;
//    while (enumMoniker->Next(1, &pMoniker, &fetched) == 0)
//    {
//        IBindCtx* bindCtx;
//        CreateBindCtx(0, &bindCtx);
//
//        LPOLESTR pRunningObjectName;
//        pMoniker[0].GetDisplayName(bindCtx, nullptr, &pRunningObjectName);
//
//        // Following is needed to turn LPOLESTR to std::string, else we can't do any checks on it
//        USES_CONVERSION;
//        std::string runningObjectName = ( ((_lpw = pRunningObjectName) == NULL) ? NULL : ( (_convert = (static_cast<int>(wcslen(_lpw))+1), (_convert>INT_MAX/2) ? NULL : ATLW2AHELPER((LPSTR) malloc(_convert*sizeof(WCHAR)), _lpw, _convert*sizeof(WCHAR), _acp))));
//
//        // Conver tthe parentPID to string to be able to compare it with the runningObjectName
//        std::string parentPID = std::to_string(getParentPID());
//        if (parentPID.size() > runningObjectName.size())
//            continue;
//
//        // Check if the running object is Visual Studio and if the PID matches the parent of the current Visual Studio that is attached to the Launcher
//        if (runningObjectName._Starts_with("!VisualStudio.DTE") && std::equal(parentPID.rbegin(), parentPID.rend(), runningObjectName.rbegin()))
//        {
//            // Grabs the object from the Running Object Table so that we can get the DTE from it
//            hr = pROT->GetObjectA(pMoniker, &pObj);
//            assert(SUCCEEDED(hr));
//            break;
//        }
//        else
//        {
//            continue; // Continue to loop through until we find the current instance of Visual Studio
//        }
//    }
//
//    EnvDTE::_DTE* dteInterface;
//    hr = pObj->QueryInterface(&dteInterface);
//    assert(SUCCEEDED(hr));
//
//    EnvDTE::Debugger* debugger;
//    hr = dteInterface->get_Debugger(&debugger);
//    assert(SUCCEEDED(hr));
//
//    EnvDTE::Processes* processes;
//    hr = debugger->get_LocalProcesses(&processes);
//    long count = 0;
//    assert(SUCCEEDED(hr));
//
//    // Goes through all the current DTE processes that matches the PID we got from CreateProcess, which we'll then attach the DTE to
//    hr = processes->get_Count(&count);
//    for (int i = 0; i < count; i++)
//    {
//        EnvDTE::Process* process;
//        hr = processes->Item(variant_t(i), &process);
//        if (FAILED(hr))
//            continue;
//
//        long pid;
//        hr = process->get_ProcessID(&pid);
//        assert(SUCCEEDED(hr));
//        if (pid == targetPID)
//        {
//            return process;
//        }
//    }
//    return nullptr;
//}

//void attachToVisualStudio(DWORD targetPID)
//{
//    EnvDTE::Process* process = findVisualStudioProcess(targetPID);
//
//    if (process != nullptr)
//    {
//        process->Attach();
//    }
//
//    CoUninitialize();
//}

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

    WaitForInputIdle(procInfo.hProcess, 5000);

    if (!hThread)
    {
        throwError("[ERROR] Couldn't open LoadLibraryA thread. Dll not injected.");
    }

    if (WaitForSingleObject(hThread, INFINITE))
    {
        throwError("[ERROR] Thread didn't return 0. Dll not injected.");
    }

    DWORD hDll;
    if (!GetExitCodeThread(hThread, &hDll))
    {
        throwError("[ERROR] Can't get LoadLibraryA return handle.");
    }

    if (hDll == 0x00000000)
    {
        throwError("[ERROR] LoadLibraryA couldn't inject dll.");
    }
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

    utinni::UtINI ini(iniFilename);
    ini.createUtinniSettings();
    ini.load();

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

            ini.setString("Launcher", "swgClientPath", swgClientPath.c_str());
            ini.setString("Launcher", "swgClientName", swgClientName.c_str());

            ini.save();
        }
        else
        {
            throwError("[ERROR] Can't open the selected file.");
        }
    }

    std::string result = swgClientPath + swgClientName;

    if (result.size() > 4 && result.compare(result.size() - 3, 3, "exe") != 0)
    {
        throwError("[ERROR] Target SWG client is not an executable.");
    }

    DWORD targetHandle = 0;
    const DWORD targetSize = GetFileVersionInfoSize(result.c_str(), &targetHandle);
    if (targetSize <= 0)
    {
        throwError("[ERROR] Target SWG client size is invalid.");
    }

    uint32_t verInfoSize;
    const char* targetProductName;
    BYTE* targetVersionInfo = new BYTE[targetSize];
    if (GetFileVersionInfo(result.c_str(), targetHandle, targetSize, targetVersionInfo))
    {
        if (VerQueryValue(targetVersionInfo, TEXT("\\StringFileInfo\\040904B0\\ProductName"), (LPVOID*)&targetProductName, &verInfoSize) && strcmp(targetProductName, "Star Wars Galaxies") != 0)
        {
            delete[] targetVersionInfo;

            ini.setString("Launcher", "swgClientPath", "");
            ini.setString("Launcher", "swgClientName", "");

            ini.save();

            throwError("[ERROR] Target client is not a valid SWG client.");
        }
        delete[] targetVersionInfo;
    }

    return result;
}

void loadDll(const std::string& cmdLine)
{
    STARTUPINFOA StartupInfo = { 0 };
    StartupInfo.cb = sizeof(StartupInfo);
    PROCESS_INFORMATION procInfo;

    const std::string swgClientFilename = getSwgClientFilename();
    if (CreateProcess(swgClientFilename.c_str(), const_cast<char*>(cmdLine.c_str()), nullptr, nullptr, false, CREATE_SUSPENDED, nullptr, swgClientPath.c_str(), &StartupInfo, &procInfo))
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
                throwError("Timed out trying to reach the entry point");
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
        throwError("Unable to load the specified executable");
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

int main(int argc, char* argv[])
{
    std::string argsCombined;

    for (int i = 1; i < argc; ++i)
    {
        // Syntax for passing swg configs is as follows: '--' marks the start of args, -s marks the start of a section followed by variables separated by whitespace
        // Inside the .cfg, sections are marked by being wrapped in brackets, ie [ClientGame]
        // Example: -- -s SectionName1 variable1=true variable2=false -s SectionName2 variable1=true variable2=false
        // Real world example: -- -s ClientGame loginClientID=Local groundScene=terrain/lok.trn
        argsCombined.append(" " + std::string(argv[i]));
    }

    loadDll(argsCombined);
    return 0;
}


