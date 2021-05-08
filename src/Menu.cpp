
#include "RuntimeInfo.h"
#include <windows.h>
#include <thread>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <sstream>

#define ARR_UP 72
#define ARR_DOWN 80
#define ARR_LEFT 75
#define ARR_RIGHT 77

#define SCREEN_WIDTH 40*siz
#define SCREEN_HIEGHT  10*siz

#include "Menu.h"
#include "Utils.h"

using namespace std;

void Menu::selectSubMech(int n)
{
	nofsubOptions = n;

	keyPressed = _getch();
	if (sounds)PlaySound(TEXT("menu.wav"), NULL, SND_ASYNC);
	if (keyPressed == '\r') { selected = true; }
	else if (keyPressed == ARR_LEFT) { pointingToSubOpt--; if (pointingToSubOpt<1) pointingToSubOpt = 1; }
	else if (keyPressed == ARR_RIGHT) { pointingToSubOpt++; if (pointingToSubOpt>nofsubOptions) pointingToSubOpt = nofsubOptions; }
}

void Menu::selectMech(int n, int Align = 0)
{
	nofOptions = n;
	Utils::placeCursor(SCREEN_WIDTH / 2 - 8 - Align, 2 * SCREEN_HIEGHT / 3 - 4 + pointingTo);
	cout << (char)219;

	keyPressed = _getch();
	if (sounds)PlaySound(TEXT("menu.wav"), NULL, SND_ASYNC);
	if (keyPressed == '\r') { selected = true; }
	if (keyPressed == ARR_UP) { pointingTo--; if (pointingTo<1) pointingTo = 1; }
	if (keyPressed == ARR_DOWN) { pointingTo++; if (pointingTo>nofOptions) pointingTo = nofOptions; }
}
/*
void Menu::printTitle()
{

for (int t = 0; t<SCREEN_HIEGHT; t++) { cout << setfill(' ') << setw(SCREEN_WIDTH) << '\n'; }
Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4);
printf("_|_|_|    _|_|_|  _|      _|    _|_|  ");		 Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 1);
printf("_|    _|    _|    _|_|    _|  _|    _|");        Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 2);
printf("_|    _|    _|    _|  _|  _|  _|    _|");        Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 3);
printf("_|    _|    _|    _|    _|_|  _|    _|");        Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 4);
printf("_|_|_|    _|_|_|  _|      _|    _|_|  ");        Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 6);
printf("    --< THE AGE OF EXTINCTION >--    ");         Utils::placeCursor(SCREEN_WIDTH - 25, SCREEN_HIEGHT + 2);

printf("build 2.0-rc2-20200514");

Utils::printSurface();
Utils::printDinoAnywhere(14, SCREEN_HIEGHT - 5 - 10, 1);
Utils::printEgg(60, 0);


}*/


void Menu::mainMenu(int W, int H)
{
	Utils::cls();//system("cls");
				 //SCREEN_HIEGHT = H; SCREEN_WIDTH = W;
	selected = false;
	Utils::printTitle();
	pointingTo = 1;

	while (!selected)
	{
		Utils::placeCursor(SCREEN_WIDTH / 2 - 8, 2 * SCREEN_HIEGHT / 3 - 3);
		printf("  Play");             Utils::placeCursor(SCREEN_WIDTH / 2 - 8, 2 * SCREEN_HIEGHT / 3 - 2);
		printf("  Settings");         Utils::placeCursor(SCREEN_WIDTH / 2 - 8, 2 * SCREEN_HIEGHT / 3 - 1);
		printf("  Help");             Utils::placeCursor(SCREEN_WIDTH / 2 - 8, 2 * SCREEN_HIEGHT / 3);
		printf("  Quit");

		selectMech(4);
	}
	if (sounds)PlaySound(TEXT("selected.wav"), NULL, SND_ASYNC);
	selected = false;
	if (pointingTo == 1)
	{
		//if (running) objFend.video();
		Utils::resetGame();

		system("cls");
	}

	if (pointingTo == 2)
	{
		settings();
	}
	if (pointingTo == 3)
	{
		help();
	}
	if (pointingTo == 4)
	{
		quit();
	}
}



void Menu::settings()
{
	Utils::cls();//system("cls");

	Utils::printTitle();
	pointingTo = 1;
	selected = false;
	while (!selected)
	{
		Utils::placeCursor(SCREEN_WIDTH / 2 - 16, 2 * SCREEN_HIEGHT / 3 - 5);
		printf("           SETTINGS           ");                   Utils::placeCursor(SCREEN_WIDTH / 2 - 16, 2 * SCREEN_HIEGHT / 3 - 3);
		printf("  Challenge   ");
		if (difficulty == 2) printf("    Normal    ");
		if (difficulty == 3) printf("     Hard     ");
		if (difficulty == 4) printf("   Nightmare  ");              Utils::placeCursor(SCREEN_WIDTH / 2 - 16, 2 * SCREEN_HIEGHT / 3 - 2);
		printf("  Sounds      ");
		if (sounds == 1) printf("      ON      ");
		if (sounds == 0) printf("     OFF      ");                  Utils::placeCursor(SCREEN_WIDTH / 2 - 16, 2 * SCREEN_HIEGHT / 3 - 1);
		printf("  Window Size       %d", siz);                     Utils::placeCursor(SCREEN_WIDTH / 2 - 16, 2 * SCREEN_HIEGHT / 3);
		printf("  Back");
		selectMech(4, 8);
	}
	if (sounds)PlaySound(TEXT("selected.wav"), NULL, SND_ASYNC);
	selected = false;

	if (pointingTo == 1)
	{
		pointingToSubOpt = difficulty - 1;
		while (!selected)
		{
			Utils::placeCursor(SCREEN_WIDTH / 2 - 2, 2 * SCREEN_HIEGHT / 3 - 3);
			if (pointingToSubOpt == 1) printf("    Normal   >");
			if (pointingToSubOpt == 2) printf("<    Hard    >");
			if (pointingToSubOpt == 3) printf("<  Nightmare  ");
			selectSubMech(3);
		}
		difficulty = pointingToSubOpt + 1;
		settings();
	}

	if (pointingTo == 2)
	{
		while (!selected)
		{
			Utils::placeCursor(SCREEN_WIDTH / 2 - 2, 2 * SCREEN_HIEGHT / 3 - 2);
			if (pointingToSubOpt == 1) printf("      ON     >");
			if (pointingToSubOpt == 2) printf("<    OFF      ");
			selectSubMech(2);
		}
		if (sounds)PlaySound(TEXT("selected.wav"), NULL, SND_ASYNC);
		if (pointingToSubOpt == 1) sounds = true;
		else if (pointingToSubOpt == 2) sounds = false;
		settings();
	}
	if (pointingTo == 3)
	{
		pointingToSubOpt = siz - 1;
		while (!selected)
		{
			Utils::placeCursor(SCREEN_WIDTH / 2 - 2, 2 * SCREEN_HIEGHT / 3 - 1);
			if (pointingToSubOpt == 1) printf("      %d     >", pointingToSubOpt + 1);
			else if (pointingToSubOpt == 5) printf("<     %d      ", pointingToSubOpt + 1);
			else printf("<     %d     >", pointingToSubOpt + 1);

			selectSubMech(5);
		}
		siz = pointingToSubOpt + 1;

		stringstream cmd; cmd << "MODE  CON COLS=" << SCREEN_WIDTH << " LINES=" << SCREEN_HIEGHT + 5; system(cmd.str().c_str());

		settings();
	}
	if (pointingTo == 4) mainMenu(SCREEN_WIDTH, SCREEN_HIEGHT);
}


void Menu::help()
{
	Utils::cls();
	Utils::printTitle();
	pointingTo = 1;
	selected = false;
	Utils::placeCursor(SCREEN_WIDTH / 2 - 8, 2 * SCREEN_HIEGHT / 3 - 5);
	printf("   HELP");                                                      Utils::placeCursor(SCREEN_WIDTH / 2 - 30, 2 * SCREEN_HIEGHT / 3 - 3);
	printf("In the Cretaceous age, meteors are showering and you have ");     Utils::placeCursor(SCREEN_WIDTH / 2 - 30, 2 * SCREEN_HIEGHT / 3 - 2);
	printf("   to save the one of the last few dinosaurs from the   ");     Utils::placeCursor(SCREEN_WIDTH / 2 - 30, 2 * SCREEN_HIEGHT / 3 - 1);
	printf("         incoming obstacles from going extinct.         ");     Utils::placeCursor(SCREEN_WIDTH / 2 - 8, 2 * SCREEN_HIEGHT / 3 + 1);
	printf(" CONTROLS");                                                    Utils::placeCursor(SCREEN_WIDTH / 2 - 30, 2 * SCREEN_HIEGHT / 3 + 3);
	printf("                  P - Pause  Q - Quit                 ");     Utils::placeCursor(SCREEN_WIDTH / 2 - 30, 2 * SCREEN_HIEGHT / 3 + 4);
	printf("               SPACE - Jump  Z - AI Mode              ");

	if (cin.get())
	{
		selected = true;
		mainMenu(SCREEN_WIDTH, SCREEN_HIEGHT);
	}
}

void Menu::quit()
{
	//Utils::resetGame();
	quitIt = true;
}
