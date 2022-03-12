#pragma once
#include "memproc.h"
#include <string>

class civ
{

private:
	const wchar_t* procName;
	const wchar_t* modDllName;
	DWORD procId;
	HANDLE hProc;
	uintptr_t gameCoreDllBaseAddr;
	uintptr_t gameExeBaseAddr;
	uintptr_t getPrimaryCityFoodAddr();
	uintptr_t getMinorCityFoodAddr(int cityIndex);
	uintptr_t getGoldAddress();
	uintptr_t getCoreDllBaseAddr();
	uintptr_t getGameExeBaseAddr();
	bool goldHackEnabled;
	void init();

public: 
	civ();
	void setGold(unsigned int amt);
	void freezeGold();
	void unfreezeGold();
	int getGold();
	int getPrimaryCityFood();
	std::string isGoldFrozen();
};

