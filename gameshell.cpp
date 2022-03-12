#include "gameshell.h"

enum ARG_INDEX
{
	COMMAND,
	ARG1,
	ARG2,
	ARG3
};

enum BASE_INDEX
{
	GET,
	SET,
	CLEAR,
	EXIT,
	HELP,
	QUESTION,
	KILL,
	TOGGLE
};

std::vector<std::string> baseCmds{

	"get",
	"set",
	"clear",
	"exit",
	"help",
	"?",
	"kill",
	"toggle"
};

std::vector<std::string> setCmds{

	"city_food",
	"city_production",
	"city_gold",
	"city_culture",
	"city_research",
	"city_citizens"
	"player_gold",
	"happiness"
};

enum SET_INDEX
{

	CITY_FOOD,
	CITY_PRODUCTION,
	CITY_GOLD,
	CITY_CULTURE,
	CITY_RESEARCH,
	CITY_CITIZEN,
	PLAYER_GOLD,
	HAPPINESS
};

std::vector<std::string> getArgs{

	"cities",
	"city_food",
	"city_production",
	"city_gold",
	"city_culture",
	"city_research",
	"city_citizens"
	"player_gold",
	"address_value",
	"happiness"
};

GameShell::GameShell() {

	system("color 4");
	showSplash();
}

void GameShell::clearScreen() {

	system("cls");
}

void GameShell::showSplash() {

	std::cout << "Civ V Trainer (1.0.3.279)\nWritten with love by zer0dox\nGithub: https://github.com/zer0dox";
	Sleep(2000);
	clearScreen();
}

void GameShell::shellMain() {

	while (1) {

		std::cout << "civ-shell~# ";
		std::cin >> command;
		cmdParse();
	}
}

void GameShell::error(const char* err) {

	std::cout << "Error: " << err << std::endl;
}

void GameShell::setNode() {
	
	bool cmdFound = false;
	for (int i = 0; i < sizeof(setCmds); i++) {

		if (args[ARG1] == setCmds[i]) {
			
			cmdFound = true;
			if (i == SET_INDEX::PLAYER_GOLD) {

				if (sizeof(args) < 3) {
					error("3 arguments required\nUsage: set player_gold [value]");
					break;
				}
				else {
					unsigned int gold;
					memcpy(&gold, &args[ARG3], sizeof(unsigned int));
					Civ.setGold(gold);
					std::cout << "Player gold set: " << gold << std::endl;
					break;
				}
			}
		}
	}
}

void GameShell::cmdExec() {

	bool cmdFound = false;
	for (int i = 0; i < sizeof(baseCmds); i++) {

		if (args[COMMAND] == baseCmds[i]) {

			cmdFound = true; 
			if (i == BASE_INDEX::GET)
				getNode();
			else if (i == BASE_INDEX::SET)
				setNode();
			else if (i == BASE_INDEX::CLEAR)
				clearScreen();
			else if (i == BASE_INDEX::HELP || i == BASE_INDEX::QUESTION)
				helpNode();
			else if (i == BASE_INDEX::TOGGLE)
				toggleNode();
			else if (i == BASE_INDEX::EXIT)
				exit(0);
			else if (i == BASE_INDEX::KILL)
				procKill();
		}
		else {
			continue;
		}
	}
	if (cmdFound == false) {

		std::cout << "Error: command " << args[COMMAND] << " not found.\n" << std::endl;
		helpNode();
	}
	else {
		cleanVector();
		return;
	}
}

void GameShell::cleanVector() {
	
	args.clear();
}

void GameShell::getNode() {}
void GameShell::helpNode() {}
void GameShell::toggleNode() {}
void GameShell::procKill() {}

void GameShell::cleanCmdBuffer() {

	memset(&(command[0]), 0, sizeof(command));
}

void GameShell::cmdParse() {

	char buff[255]{};
	for (int i = 0; i < sizeof(command); i++) {

		for (int x = 0; x < sizeof(buff); x++) {

			if (command[i] == *" " || command[i] == *"\n") {

				args.push_back(buff);
				memset(&(buff[0]), 0, sizeof(buff));
				x = 0;
			}
			else {
				buff[x] = command[i];
			}
		}
	}
	cleanCmdBuffer();
	cmdExec();
}