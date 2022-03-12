#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

DWORD getProcessId(const wchar_t* procName);
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
uintptr_t FindDynamicAddr(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets);
void patchEx(HANDLE hProc, LPVOID Addr, LPCVOID buffer, SIZE_T size);
void nopEx(HANDLE hProc, LPVOID Addr, SIZE_T size);