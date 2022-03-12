#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include "memproc.h"
#include "civ.h"

class GameShell {
public:
	GameShell();
	void showSplash();
	void shellMain();
private:
	civ Civ;
	std::vector<char*> args{};
	char command[255];
	void cmdParse();
	void setNode();
	void getNode();
	void clearScreen();
	void cleanCmdBuffer();
	void cleanVector();
	void helpNode();
	void toggleNode();
	void procKill();
	void cmdExec();
	void error(const char* err);
};