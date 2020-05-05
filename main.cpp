#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <mmsystem.h>
#include <math.h>

#include "Menu_xtra.h"
#include "PrintPaster.h"
#include "DATAS.h"
#include "SaveGame.h"
#include "Processing.h"
#include "FRONTEND.h"

#define SCREEN_WIDTH 160
#define SCREEN_HIEGHT 40

#pragma comment(a, "libwinmm.a")
#pragma comment(lib, "Winmm.lib")
using namespace std;


// RPERESENTS OBJECTS AND THEIR POSITIONS
int surface  = 35;
int treeP, tree2P;
int dino = surface;


//TO BE SAVED NECCESSARY
int HiJumps = 0;
int HiScore = 0;
bool sounds = true;
int score = 0;
int jumps = 0;
int difficulty = 2;


//EXTRA
char d;
char j;


// O B J E C T S
static Menu_xtra obj;
static PrintPaster objPP;
static SaveGame objSave;
static Processing objProc;
static FRONTEND objFend;

//SUPPORT BOOLEANS AND FOR REAL TIME INFORMATION
bool NewGame = false;
bool hit = 0;
long int frame =0;
bool stillJumping = false;
bool powerOff = 0;
bool jumped = false;
bool running = true;
bool treeVanish = true;
bool tree2Vanish = true;
int whenjumped ;
int TimeUnit;
bool paused = false;
bool quitIt = false;
bool cheatOn = false;


//saving the info that user pressed enter
void jump()
{
	while(running && !quitIt)
	{
	    if(!running) return;

		j=getch();
		if(((j==32 || j==10) && ! stillJumping)  && !cheatOn)
		{
			jumped = true;
			if(sounds)PlaySound(TEXT("JUMP.wav"), NULL ,SND_ASYNC);
		}
		if(j == 'p' || j == 'P')
        {
            paused = true;
        }
        if(j == 'q' || j == 'Q')
        {
            quitIt = true;
        }
        if(j == 'z' || j == 'Z')
        {
            if(cheatOn) cheatOn = false;
            else if(!cheatOn) cheatOn = true;
        }
	}
}

int main()
{
    objPP.openScreen();
	if(frame == 0 )
	{
	    system("MODE  CON COLS=160 LINES=45");

	    obj.hideCursor();

	    srand(time(NULL));
        treeP = 120 + rand()%180;
        tree2P = 120 + rand()%180;

        objProc.linkToMain(obj, objPP,objSave);

        objSave.Loading(objSave.openSaveFile());

	    obj.mainMenu(SCREEN_WIDTH, SCREEN_HIEGHT);

		system("cls");
	}

    static thread in_air{jump};

	obj.cls();

    if(quitIt){ running = false;  powerOff = 1;}

    if(paused)
    {
        obj.placeCursor(0, SCREEN_HIEGHT/2);
        cout << setw(SCREEN_WIDTH/2) << "P A U S E D";
        cin.ignore();
        system("cls");
        paused = false;
    }

    if(cheatOn)
    {
        if(( tree2P- dino == 2 ||  treeP- dino == 2) && ! stillJumping)
        {
            jumped  = true;
        }
    }

	objProc.treesAI();

	//making the jump
	if(jumped)
	{
		whenjumped =  frame;
		 dino--;
		 score+=5;
		 jumps++;
		jumped = false;
		 stillJumping = true;
	}

    objProc.smoothingJump();

    objPP.PrinterEngine();

    objPP.screenDisplay();

	objProc.gameOver();

	if(powerOff ) {
        running = false;

        system("CLS");obj.placeCursor(0, SCREEN_HIEGHT/2);cout << setw(SCREEN_WIDTH/2) << "Come back when you've improved!";

        objProc.updateDatas();

        objSave.Saving(objSave.openSaveFile());

        in_air.join();
        return 0;
    }

     tree2P-=difficulty;
     treeP-=difficulty;

    main();

    running = false;

    return 0;
}

