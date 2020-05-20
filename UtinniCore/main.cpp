#include "utinni.h"

UtinniBase* utinniBase = nullptr;

void main()
{
	 utinniBase = UtinniBase::instance();
	 if (!utinniBase->initialize())
	 {
		  MessageBox(0, "Failed", "Failed to initialize", MB_OK); // ToDo Add this to log
	 }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) 
{
	 switch (fdwReason) 
	 {
	 case DLL_PROCESS_ATTACH:
		  CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
		  return true;

	 case DLL_PROCESS_DETACH:
		  utinniBase->cleanUpHook();
		  SAFE_DELETE(utinniBase);
		  return true;
	 }
	 return false;
}