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
#include <mmsystem.h>
#include <math.h>

                                //------------------developed-by-msc24x-------------------------//

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
int treeP, tree2P, birdP;
int dino = surface;
int birdHeight = 25;


//TO BE SAVED NECCESSARY
bool incmngBirds = false;
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
int bestJump;
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
	while(1)
	{
	    if(quitIt ) break;

	    if(running) j=getch();

		if(((j==32 || j==10) && ! stillJumping) && !cheatOn)
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
        if(score <= HiScore)
        {
            objProc.updateDatas();
            objSave.Saving(objSave.openSaveFile());
        }
	}
}

int main()
{
    objPP.openScreen();
	if(frame == 0 )
	{
	    SetConsoleTitle("Dino : The Age of Extinction");

	    system("MODE  CON COLS=160 LINES=45");

	    obj.hideCursor();

	    srand(time(NULL));

        treeP = 120 + rand()%180;
        tree2P = 120 + rand()%180;
        birdP = 300 + rand()%300;

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
        cout << setfill(' ') << setw(SCREEN_WIDTH/2) << "P A U S E D";
        cin.ignore();
        system("cls");
        paused = false;
    }

    if(cheatOn)
    {
        if(( (tree2P- dino <= bestJump && dino < tree2P) ||  (treeP- dino <= bestJump  && dino < treeP) || (birdP - dino <= bestJump && birdHeight == 10 && dino < birdP)) && !stillJumping)
        {
            jumped  = true;
			if(sounds)PlaySound(TEXT("JUMP.wav"), NULL ,SND_ASYNC);
        }
    }

	objProc.treesAI();

	//making the jump
	if(jumped)
	{  jumped = false;

		whenjumped =  frame;

        dino--;     score+=5;   jumps++;

        stillJumping = true;
	}

    objProc.smoothingJump();

    objPP.PrinterEngine();

    objPP.screenDisplay();

	objProc.gameOver();

	if(powerOff ) { powerOff = false;

        running = false;

        system("CLS");

        objFend.credits();

        objProc.updateDatas();

        objSave.Saving(objSave.openSaveFile());

        in_air.join();

        getch();
        return 0;
    }

     tree2P-=difficulty;
     treeP-=difficulty;
     birdP-= difficulty;

    main();

    running = false;

    return 0;
}

