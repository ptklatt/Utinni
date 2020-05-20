#include "utinni.h"

UtinniBase* baseUtinniInstance = nullptr;
Utinni* utinniInstance;

std::string utinniPath;

UtinniBase* UtinniBase::instance() 
{
	 if (!baseUtinniInstance)
	 {
        baseUtinniInstance = new UtinniBase();
	 }
	 return baseUtinniInstance;
}

void UtinniBase::cleanUpHook() 
{
	 SAFE_DELETE(utinniInstance);
}

UtinniBase::UtinniBase() 
{
	 DisableThreadLibraryCalls(GetModuleHandle(nullptr));
}

bool UtinniBase::initialize() 
{
    utinniInstance = Utinni::instance();
	 return true;
}

UtinniBase::~UtinniBase() 
{
	 SAFE_DELETE(utinniInstance);
    baseUtinniInstance = nullptr;
}

Utinni* Utinni::instance()
{
    baseUtinniInstance = UtinniBase::instance();
    if (!utinniInstance && baseUtinniInstance)
    {
        utinniInstance = new Utinni();
    }
    return utinniInstance;
}

Utinni::Utinni()
{
    char dllPathbuffer[MAX_PATH];
    HMODULE handle = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&Utinni::instance, &handle);
    GetModuleFileNameA(handle, dllPathbuffer, sizeof(dllPathbuffer));
    std::string dllPath = std::string(dllPathbuffer);
    utinniPath = dllPath.substr(0, dllPath.find_last_of("\\/")) + "\\";
}

Utinni::~Utinni() {}

std::string Utinni::getUtinniPath()
{
    return utinniPath;
}
