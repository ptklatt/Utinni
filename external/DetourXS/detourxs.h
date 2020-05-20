/*
Name: DetourXS
Description: DetourXS is a library for function detouring
Version: 1.0
Author: Sinner
Website: www.gamedefeat.com & www.cheatersutopia.com
Credits: z0mbie (ADE32), LanceVorgin's CDetour (some ideas)
*/

#pragma once

//#pragma comment(lib, "detourxs")

#include "ADE32.h"

#define DETOUR_LEN_AUTO 0 // Finds the detour length automatically

enum DETOUR_TYPE
{
	DETOUR_TYPE_JMP, // min detour len: 5
	DETOUR_TYPE_PUSH_RET, // min detour len: 6
	DETOUR_TYPE_NOP_JMP, // min detour len: 6
	DETOUR_TYPE_NOP_NOP_JMP, // min detour len: 7
	DETOUR_TYPE_STC_JC, // min detour len: 7
	DETOUR_TYPE_CLC_JNC, // min detour len: 7
   DETOUR_TYPE_PATCH_CALL
};

namespace Detour
{
DWORD CheckPointer(DWORD Address);
LPVOID Create(LPVOID lpFuncOrig, LPVOID lpFuncDetour, int detourLen);
LPVOID Create(LPVOID lpFuncOrig, LPVOID lpFuncDetour, DETOUR_TYPE patchType, int detourLen = DETOUR_LEN_AUTO);
LPVOID Create(LPCSTR lpModuleName, LPCSTR lpProcName, LPVOID lpFuncDetour, DETOUR_TYPE patchType, int detourLen = DETOUR_LEN_AUTO);
bool Remove(LPVOID lpDetourCreatePtr);
}
