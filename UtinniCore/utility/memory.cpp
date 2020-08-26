#include "memory.h"
#include <TlHelp32.h>
#include <Psapi.h>

namespace memory
{

swgptr findPattern(swgptr startAddress, size_t length, const char* pattern, const char* mask)
{
	 swgptr pos = 0;
    const size_t searchLength = strlen(mask) - 1;
	 for (swgptr returnAddress = startAddress; returnAddress < startAddress + length; returnAddress++)
	 {
		  if (*(PBYTE)returnAddress == ((PBYTE)pattern)[pos] || mask[pos] == '?')
		  {
				if (mask[pos + 1] == '\0')
				{
					 return returnAddress - searchLength;
				}
				pos++;
		  }
		  else
		  {
				pos = 0;
		  }
	 }
	 return 0;
}

swgptr findPattern(const char* moduleName, const char* pattern, const char* mask)
{
	 HINSTANCE moduleHandle = GetModuleHandle(moduleName);
	 MODULEINFO moduleInfo;
	 GetModuleInformation(GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(MODULEINFO));

	 return findPattern((swgptr)moduleHandle, moduleInfo.SizeOfImage, pattern, mask);
}

void copy(swgptr pDest, swgptr pSource, size_t length)
{
	 DWORD oldProtect;
	 DWORD newProtect;

	 const LPVOID addr = (LPVOID)pDest;
	 VirtualProtect(addr, length, PAGE_EXECUTE_READWRITE, &oldProtect);
	 memcpy(addr, (LPVOID)pSource, length);
	 VirtualProtect(addr, length, oldProtect, &newProtect);
}

void write(swgptr address, swgptr value, int length)
{
	 copy(address, value, length);
}

void set(swgptr pDest, swgptr value, size_t length)
{
	 DWORD oldProtect;
	 DWORD newProtect;

	 const LPVOID addr = (LPVOID)pDest;
	 VirtualProtect(addr, length, PAGE_EXECUTE_READWRITE, &oldProtect);
	 memset(addr, value, length);
	 VirtualProtect(addr, length, oldProtect, &newProtect);
}

void patchAddress(swgptr address, swgptr value)
{
	 set(address, value, 4); // ToDo check if this works right, doesn't it need write or copy vs set?
}

void nopAddress(swgptr address, int nopCount) 
{
	 set(address, 0x90, nopCount); // 0x90 = NOP
}

void createJMP(swgptr address, swgptr jumpToAddress, size_t overrideLength)
{
	 DWORD oldProtect;
	 DWORD newProtect;

    VirtualProtect((LPVOID)address, overrideLength, PAGE_EXECUTE_READWRITE, &oldProtect);
	 write<char>(address, 0xE9); // 0xE9 = JMP
	 write<swgptr>(address + 0x1, (jumpToAddress - address) - 5); 
	 for (swgptr i = 0x5; i < overrideLength; i++)
	 {
		  write<char>(address + i, 0x90); // 0x90 = NOP
	 }
	 VirtualProtect((LPVOID)address, overrideLength, oldProtect, &newProtect);
}

swgptr getAddress(swgptr baseAddress, int ptrDepth)
{
	 swgptr address = read<swgptr>(baseAddress);
	 for (int i = 0; i < ptrDepth; ++i)
	 {
		  address = read<swgptr>(address);
	 }
	 return address;
}

swgptr getAddress(swgptr baseAddress, std::vector<int>& offsets)
{
	 swgptr address = read<swgptr>(baseAddress);
	 for (swgptr offset : offsets)
	 {
		  address = read<swgptr>(address + offset);
	 }
	 return address;
}



}


