#include "Processing.h"

#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <ctime>
#include <conio.h>

#include "Menu_xtra.h"
#include "PrintPaster.h"
#include "DATAS.h"
#include "SaveGame.h"


#pragma comment(a, "libwinmm.a")
#pragma comment(lib, "Winmm.lib")

#define SCREEN_WIDTH 160
#define SCREEN_HIEGHT 40

using namespace std;


void Processing::linkToMain(Menu_xtra OM,        PrintPaster OP,       SaveGame OS)
{
    obj = Menu_xtra(OM);
    objPP = PrintPaster(OP);
    objSave = SaveGame(OS);
}


void Processing::smoothingJump()
{
    TimeUnit =  frame - whenjumped;
    if(stillJumping)
    {
        TimeUnit =  frame - whenjumped;

        if(TimeUnit < 11)
        {
             dino-=2;
        }

        else if(TimeUnit >= 16)
        {
             dino+=2;
        }
    }
	if(TimeUnit == 26){   stillJumping = false;  dino = surface;}
}



void Processing::gameOver()
{
    if( hit)
	{
	    if(sounds) PlaySound("OVER.wav", NULL, SND_ASYNC);

	    running = false;
	    hit = 0; quitIt = 0;
		obj.placeCursor(SCREEN_WIDTH/2-9, SCREEN_HIEGHT/2);
		cout << "G A M E   O V E R";


		cin.get();
		powerOff = true;
	}
}


void Processing::treesAI()
{
    //displacing the trees if they're too close to star , at the beginning and at the point when any tree passes

    if(tree2Vanish || treeVanish)
    {
        srand(time(NULL));
		while(treeVanish && ( tree2P - treeP<50 &&  treeP- tree2P<50))
		{
             treeP = 120 + (rand()%180);
		}
		while(tree2Vanish && ( tree2P- treeP<50 &&  treeP- tree2P<50))
		{
             tree2P = 120 + (rand()%180);
		}
		treeVanish = false;
		tree2Vanish = false;
	}

	//saving the info for the next frame to tell that previous i.e. in this frame a tree was vanished


	if( treeP<=0)
	{
		treeVanish = true;
		 treeP = 120 + (rand()%180);
	}
	if( tree2P <= 0)
	{
		 tree2P = 120 + (rand()%180);
		tree2Vanish = true;
	}
}

void Processing::resetGame()
{
     hit = 0;
    quitIt = false;
     dino = surface;
     jumps = 0;
     stillJumping = false;
    srand(time(NULL));
     treeP = 120 + (rand()%180);
     tree2P = 120 + (rand()%180);
     score = 0;
    running = true;
    treeVanish=true;
    tree2Vanish=true;
     frame = 0;
}


void Processing::updateDatas()
{
    if(HiScore <= score/10)    HiScore = score/10;
    if(HiJumps <= jumps)    HiJumps = jumps;
}


