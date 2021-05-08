

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <conio.h>
#include <windows.h>
#include <functional>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <mmsystem.h>
#include <math.h>

//------------------developed-by-msc24x-------------------------//

#include "Menu.h"
#include "Printer.h"
#include "RuntimeInfo.h"
#include "Save.h"
#include "Processor.h"
#include "Utils.h"

//#pragma comment(a, "libwinmm.a")
#pragma comment(lib, "Winmm.lib")
using namespace std;

//TO BE SAVED NECCESSARY
bool incmngBirds = false;
int HiJumps = 0;
int HiScore = 0;
bool sounds = true;
int score = 0;
int jumps = 0;
int difficulty = 2;
int siz = 4;

// RPERESENTS OBJECTS AND THEIR POSITIONS
#define SCREEN_WIDTH 40*siz
#define SCREEN_HIEGHT  10*siz
int surface = SCREEN_HIEGHT - 5;
int treeP, tree2P, birdP;
int dino = surface;
int birdHeight = 25;

//EXTRA
char d;
char j;


// O B J E C T S
static Menu menu;
static Printer printer;
static Save save;
static Processor proc;

//SUPPORT BOOLEANS AND FOR REAL TIME INFORMATION
int bestJump;
bool NewGame = false;
bool hit = 0;
long int frame = 0;
bool stillJumping = false;
bool powerOff = 0;
bool jumped = false;
bool running = true;
bool treeVanish = true;
bool tree2Vanish = true;
int whenjumped;
int TimeUnit;
bool paused = false;
bool quitIt = false;
bool cheatOn = false;



//saving the info that user pressed enter
void jump()
{
	while (1)
	{
		if (quitIt) break;

		if (running) j = _getch();

		if (((j == 32 || j == 10) && !stillJumping) && !cheatOn)
		{
			jumped = true;
			if (sounds)		PlaySound(TEXT("JUMP.wav"), NULL, SND_ASYNC);
		}
		if (j == 'p' || j == 'P')
		{
			paused = true;
		}
		if (j == 'q' || j == 'Q')
		{
			quitIt = true;
		}
		if (j == 'z' || j == 'Z')
		{
			if (cheatOn) cheatOn = false;
			else if (!cheatOn) cheatOn = true;
		}
		if (score > HiScore)
		{
			proc.updateRuntimeInfo();
			save.Saving(save.openSaveFile());
		}
	}
}

int main()
{
	printer.openScreen();
	if (frame == 0)
	{
		save.Loading(save.openSaveFile());

		SetConsoleTitle(TEXT("Dino : The Age of Extinction"));
		stringstream cmd;
		cmd << "MODE  CON COLS=" << SCREEN_WIDTH << " LINES=" << SCREEN_HIEGHT + 5;
		system(cmd.str().c_str());

		Utils::hideCursor();

		//srand((unsigned int)time(NULL));

		treeP = 120 + rand() % 180;
		tree2P = 120 + rand() % 180;
		birdP = 300 + rand() % 300;

		proc.linkToMain(menu, save);


		menu.mainMenu(SCREEN_WIDTH, SCREEN_HIEGHT);

		system("cls");
	}

	static thread in_air{ jump };
	Utils::cls();
	if (quitIt) { running = false;  powerOff = 1; }

	if (powerOff) {
		powerOff = false;

		running = false;

		//system("CLS");

		Utils::credits();

		proc.updateRuntimeInfo();

		save.Saving(save.openSaveFile());

		in_air.join();

		_getch();
		return 0;
	}

	if (paused)
	{
		Utils::placeCursor(0, SCREEN_HIEGHT / 2);
		cout << setfill(' ') << setw(SCREEN_WIDTH / 2) << "P A U S E D";
		cin.ignore();
		system("cls");
		paused = false;
	}

	if (cheatOn)
	{
		if (((tree2P - dino <= bestJump && dino < tree2P) || (treeP - dino <= bestJump  && dino < treeP) || (birdP - dino <= bestJump && birdHeight == 10 && dino < birdP)) && !stillJumping)
		{
			jumped = true;
			if (sounds)PlaySound(TEXT("JUMP.wav"), NULL, SND_ASYNC);
		}
	}

	proc.treesAI();
	//making the jump
	if (jumped)
	{
		jumped = false;

		whenjumped = frame;

		dino--;     score += 5;   jumps++;

		stillJumping = true;
	}

	proc.smoothingJump();
	printer.PrinterEngine();
	printer.screenDisplay();
	proc.gameOver();
	if (powerOff) {
		powerOff = false;

		running = false;

		system("CLS");

		Utils::credits();

		proc.updateRuntimeInfo();

		save.Saving(save.openSaveFile());

		in_air.join();

		_getch();
		return 0;
	}

	tree2P -= difficulty;
	treeP -= difficulty;
	birdP -= difficulty;

	main();

	running = false;

	return 0;
}

