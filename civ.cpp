#include "civ.h"
#include <iostream>
#include <Windows.h>
#include <string>


civ::civ() {

	modDllName = L"CvGameCoreDLLFinal\u0020Release.dll";
	procName = L"CivilizationV_DX11.exe";
	init();
}

void civ::init() {

	std::cout << "Initilizing Civ V trainer..." << std::endl;
	procId = getProcessId(procName);
	while (!procId) {

		std::cout << "Please open Civ V." << std::endl;
		system("pause");
		system("cls");
		procId = getProcessId(procName);
		
	}
	hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	gameCoreDllBaseAddr = getCoreDllBaseAddr();
	gameExeBaseAddr = getGameExeBaseAddr();
	goldHackEnabled = false;
	system("cls");
	
}

uintptr_t civ::getCoreDllBaseAddr() {
	return GetModuleBaseAddress(civ::procId, modDllName);
}

uintptr_t civ::getGameExeBaseAddr() {
	return GetModuleBaseAddress(civ::procId, civ::procName);
}

uintptr_t civ::getGoldAddress() {

	uintptr_t buffer = GetModuleBaseAddress(procId, modDllName);
	std::vector<unsigned int> offsets{ 0x2B5A48, 0xF3E0, 0x08 };
	/*
	
	buffer += offsets[0]; // dll_base+2B5A48
	std::cout << "base+2B5A48 = " << buffer << std::endl;
	ReadProcessMemory(hProc, (LPVOID)buffer, &buffer, sizeof(buffer), 0);
	std::cout << buffer << std::endl;
	buffer += offsets[1]; //buffer+F3E0
	std::cout << "base+F3E0 = " << buffer << std::endl;
	ReadProcessMemory(hProc, (LPVOID)buffer, &buffer, 4, 0);
	std::cout << buffer << std::endl;
	buffer += offsets[2]; //buffer+08
	std::cout << "base+08 = " << buffer << std::endl;
	system("pause");
	return (uintptr_t)buffer; */

	return FindDynamicAddr(hProc, buffer, offsets);

}

void civ::setGold(unsigned int amt) {

	uintptr_t goldAddr = civ::getGoldAddress();
	WriteProcessMemory(hProc, (LPVOID)goldAddr, &amt, sizeof(amt), 0);

}

int civ::getGold() {

	int buff = 0;
	uintptr_t goldAddr = civ::getGoldAddress();
	ReadProcessMemory(hProc, (LPCVOID)goldAddr, &buff, sizeof(buff), 0);
	return buff;

}

int civ::getPrimaryCityFood() {

	int buff = 0;
	uintptr_t priAddr = civ::getPrimaryCityFoodAddr();
	ReadProcessMemory(hProc, (LPCVOID)priAddr, &buff, sizeof(buff), 0);
	return buff;
}

void civ::freezeGold() {

	system("cls");
	if (goldHackEnabled == false) {

		uintptr_t goldWriteAddr = gameCoreDllBaseAddr + 0x189519;
		nopEx(hProc, (LPVOID)goldWriteAddr, 3);
		goldHackEnabled = true;
	}
	else {
		unfreezeGold();
	}
	
}

void civ::unfreezeGold() {

	if (goldHackEnabled == true) {

		uintptr_t goldWriteAddr = (gameCoreDllBaseAddr + 0x189519);
		patchEx(hProc, (LPVOID)goldWriteAddr, (LPCVOID)("\x89\x41\x08"), 3);
		goldHackEnabled = false;
	}
	else {
		freezeGold();
	}
}

uintptr_t civ::getPrimaryCityFoodAddr() {

	uintptr_t buffer = GetModuleBaseAddress(procId, procName);
	std::vector<unsigned int> offsets{ 0x2B5A3C, 0x08, 0x94, 0x2C, 0x0C, 0x0C, 0x138, 0x18, 0x0 };
	return FindDynamicAddr(hProc, buffer, offsets);

}

uintptr_t civ::getMinorCityFoodAddr(int cityIndex) {

	uintptr_t buffer = getPrimaryCityFoodAddr();
	for (int i = 0; i < cityIndex; i++) {
		buffer += 0x1BEA0;
	}
	return buffer;
}

std::string civ::isGoldFrozen() {
	
	if (goldHackEnabled == true) {
		return "Enabled";
	}
	else {
		return "Disabled"; 
	}
}