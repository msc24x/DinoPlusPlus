#include "Processing.h"

#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
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

SaveGame objSave;

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
	{   hit = 0;

	    if(sounds) PlaySound("OVER.wav", NULL, SND_ASYNC);

	    running = false;
                                    obj.placeCursor(SCREEN_WIDTH/2-9, SCREEN_HIEGHT/2);
	    cout << "G A M E   O V E R";
		cin.get();
		frame = 0;

		objSave.Saving(objSave.openSaveFile());
		//powerOff = true;
	}
}


void Processing::treesAI()
{
    if(birdP <= 0)
    {
        if((frame/5)%2) birdHeight = 25;
        else birdHeight = 10;
        birdP = 300 + rand()%300;
    }

    //displacing the trees if they're too close to star , at the beginning and at the point when any tree passes

    if(tree2Vanish || treeVanish)
    {
		if(treeVanish)
		{
             while(( tree2P - treeP<80 &&  treeP- tree2P<80) || ( birdP - treeP<80 &&  treeP- birdP<80)) { treeP = 120 + (rand()%300); }
		}
		if(tree2Vanish)
		{
             while(( tree2P- treeP<80 &&  treeP- tree2P<80) || ( tree2P- birdP<80 &&  birdP- tree2P<80)) {tree2P = 120 + (rand()%300); }
		}
		treeVanish = false;
		tree2Vanish = false;
	}

	//saving the info for the next frame to tell that previous i.e. in this frame a tree was vanished



	if( treeP<=0)
	{
		treeVanish = true;
		 treeP = 120 + (rand()%300);
	}
	if( tree2P <= 0)
	{
		 tree2P = 120 + (rand()%300);
		tree2Vanish = true;
	}
}

void Processing::resetGame()
{
     hit = 0;
     surface =35;
    quitIt = false;
     dino = surface;
     jumps = 0;
     stillJumping = false;
   // srand(time(NULL));
     treeP = 120 + (rand()%300);
     tree2P = 120 + (rand()%300);
     birdP = 300 + rand()%300;
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


