
#include "Processor.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <conio.h>

#include "Menu.h"
#include "RuntimeInfo.h"
#include "Save.h"
#include "Utils.h"


//#pragma comment(a, "libwinmm.a")
#pragma comment(lib, "Winmm.lib")

#define SCREEN_WIDTH 40*siz
#define SCREEN_HIEGHT  10*siz

using namespace std;

void Processor::linkToMain(Menu OM, Save OS)
{
	Processor::menu = Menu(OM);
	//Processor::printer = Printer(OP);
	Processor::save = Save(OS);
}

void Processor::smoothingJump()
{
	TimeUnit = frame - whenjumped;
	if (stillJumping)
	{
		TimeUnit = frame - whenjumped;

		if (TimeUnit < 11)
		{
			dino -= 2;
		}

		else if (TimeUnit >= 16)
		{
			dino += 2;
		}
	}
	if (TimeUnit == 26) { stillJumping = false;  dino = surface; }
}



void Processor::gameOver()
{
	if (hit)
	{
		//Utils::resetGame();
		hit = 0;

		if (sounds) PlaySound(TEXT("OVER.wav"), NULL, SND_ASYNC);

		running = false;
		Utils::placeCursor(SCREEN_WIDTH / 2 - 9, SCREEN_HIEGHT / 2);
		cout << "G A M E   O V E R";
		_getch();
		frame = 0;

		Processor::updateRuntimeInfo();

		save.Saving(save.openSaveFile());

		//powerOff = true;
	}
}


void Processor::treesAI()
{
	if (birdP <= 0)
	{
		if ((frame / 5) % 2) birdHeight = 25;
		else birdHeight = 10;

		do { birdP = 300 + rand() % 300; } while ((birdP - treeP<80 && treeP - birdP<80) || (tree2P - birdP<80 && birdP - tree2P<80));

	}

	//displacing the trees if they're too close to star , at the beginning and at the point when any tree passes

	if (tree2Vanish || treeVanish)
	{
		if (treeVanish)
		{
			while ((tree2P - treeP<80 && treeP - tree2P<80) || (birdP - treeP<80 && treeP - birdP<80)) { treeP = 120 + (rand() % 300); }
		}
		if (tree2Vanish)
		{
			while ((tree2P - treeP<80 && treeP - tree2P<80) || (tree2P - birdP<80 && birdP - tree2P<80)) { tree2P = 120 + (rand() % 300); }
		}
		treeVanish = false;
		tree2Vanish = false;
	}

	//saving the info for the next frame to tell that previous i.e. in this frame a tree was vanished



	if (treeP <= 0)
	{
		treeVanish = true;
		treeP = 120 + (rand() % 300);
	}
	if (tree2P <= 0)
	{
		tree2P = 120 + (rand() % 300);
		tree2Vanish = true;
	}
}

/*
void Processor::resetGame()
{
hit = 0;
surface = SCREEN_HIEGHT-5;
quitIt = false;
dino = surface;
jumps = 0;
powerOff = false;
stillJumping = false;
// srand(time(NULL));
treeP = 120 + (rand() % 300);
tree2P = 120 + (rand() % 300);
birdP = 300 + rand() % 300;
score = 0;
running = true;
treeVanish = true;
tree2Vanish = true;
frame = 0;
if (difficulty == 2) bestJump = 5;
if (difficulty == 3) bestJump = 35;
if (difficulty == 4) bestJump = 60;
}
*/

void Processor::updateRuntimeInfo()
{
	if (HiScore <= score / 10)    HiScore = score / 10;
	if (HiJumps <= jumps)    HiJumps = jumps;
}


