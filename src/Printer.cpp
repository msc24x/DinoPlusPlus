
#include "Printer.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "RuntimeInfo.h"
#include <string>

#define SCREEN_WIDTH 40*siz
#define SCREEN_HIEGHT  10*siz

#define FULL_B (char)219
#define LO_B (char)220
#define UP_B (char)223

#include "Utils.h"

using namespace std;

static fstream Screen;

void Printer::printUS()
{
	/*Screen.seekp(-1, ios_base::cur);//putchar('\b');
	Screen.get(d);
	if(d == 'T') { hit = 1; }*/
	Screen.seekp(-1, ios_base::cur);
	Screen << 'U';
}

void Printer::printLS()
{
	/*Screen.seekp(-1, ios_base::cur);
	Screen.get(d);
	if(d == 'T') { hit = 1; }*/
	Screen.seekp(-1, ios_base::cur);
	Screen << 'L';
}

void Printer::PrinterEngine()
{

	//the frame construction using positions of objects
	score += difficulty;
	Screen << '\n' << "\tJUMPS    : ";
	for (int z = 0; z < 3 - Utils::nofDigits(jumps); z++)
	{
		Screen << '0';
	}

	Screen << jumps << string(SCREEN_WIDTH - 45, ' ') << "SCORE    : ";
	for (int z = 0; z < 5 - Utils::nofDigits(score / 10); z++)
	{
		Screen << '0';
	}
	Screen << score / 10;

	Screen << '\n' << "\tHI JUMPS : ";
	for (int z = 0; z < 3 - Utils::nofDigits(HiJumps); z++)
	{
		Screen << '0';
	}
	Screen << HiJumps << string(SCREEN_WIDTH - 45, ' ') << "HI SCORE : ";
	for (int z = 0; z < 5 - Utils::nofDigits(HiScore); z++)
	{
		Screen << '0';
	}
	Screen << HiScore;
	for (int r = 0; r < SCREEN_HIEGHT; r++)
	{
		Screen << '\n';
		for (int c = 0; c < SCREEN_WIDTH; c++)
		{
			//the surface
			if (r == surface - 1)
			{
				Screen << '_';
			}
			else /*if((((r<surface-1 && r>=surface-6) || r == surface-25) || ( (r<=surface-5 && r>=surface-40 && r !=  surface-25) && c < 23 ) ) || r >=surface)*/ { Screen << ' '; }

			//BIRD

			if (
				/*((r == surface -birdHeight)  && ( c == birdP))
				||            ((r == surface -birdHeight+1) && ( c == birdP || c == birdP+1 || c == birdP+2 ))
				||*/          ((r == surface - birdHeight + 2) && (c >= birdP - 5 && c <= birdP - 2))
				|| ((r == surface - birdHeight + 3) && (c >= birdP - 5 && c <= birdP + 8))
				|| ((r == surface - birdHeight + 4) && (c >= birdP - 2 && c <= birdP + 6))

				)

			{
				printTree();
				/*if(r == surface-birdHeight && c == birdP) printLS();
				if((r == surface-birdHeight+1) && ((c <= birdP-4 && c >= birdP-7) || c == birdP +2)) printLS();*/
				if ((r == surface - birdHeight + 2) && (c == birdP - 2 || c == birdP - 5)) printLS();
				if ((r == surface - birdHeight + 3) && (c == birdP - 5 || c >= birdP + 4)) printUS();
				if ((r == surface - birdHeight + 4) && (c == birdP - 2 || c >= birdP + 4)) printUS();


			}

			if ((frame / 5) % 2)
			{
				if (
					((r == surface - birdHeight) && (c == birdP))
					|| ((r == surface - birdHeight + 1) && (c == birdP || c == birdP + 1 || c == birdP + 2))
					|| ((r == surface - birdHeight + 2) && (c >= birdP && c <= birdP + 3))
					)
				{
					printTree();
					if (r == surface - birdHeight && c == birdP) printLS();
					if ((r == surface - birdHeight + 1) && ((c <= birdP - 4 && c >= birdP - 7) || c == birdP + 2)) printLS();
					if ((r == surface - birdHeight + 2) && (c == birdP + 3)) printLS();
				}
			}
			else {

				if ((r == surface - birdHeight + 5) && (c == birdP || c == birdP + 1 || c == birdP + 2))
				{
					printTree();
					if (c == birdP + 2) printUS();
				}
				if ((r == surface - birdHeight + 6) && (c == birdP)) printUS();
			}

			//placing trees on surface

			if (
				(r == surface && (c == treeP || c == treeP + 1))
				|| (r == surface - 1 && (c == treeP || c == treeP + 1))
				|| (r == surface - 2 && (c == treeP || c == treeP + 1 || c == treeP + 2 || c == treeP + 3 || c == treeP + 4))
				|| (r == surface - 3 && (c == treeP || c == treeP + 1 || c == treeP - 1 || c == treeP - 2 || c == treeP - 3 || c == treeP + 3 || c == treeP + 4))
				|| (r == surface - 4 && (c == treeP || c == treeP + 1 || c == treeP - 3 || c == treeP - 2 || c == treeP + 3 || c == treeP + 4))
				|| (r == surface - 5 && (c == treeP - 2 || c == treeP - 3 || c == treeP + 3 || c == treeP + 4))
				|| (r == surface - 6 && (c == treeP - 2 || c == treeP - 3))

				)
			{
				printTree();
			}


			if (
				(r == surface && (c == tree2P || c == tree2P + 1))
				|| (r == surface - 1 && (c == tree2P || c == tree2P + 1))
				|| (r == surface - 2 && (c == tree2P || c == tree2P + 1 || c == tree2P + 2 || c == tree2P + 3 || c == tree2P + 4))
				|| (r == surface - 3 && (c == tree2P || c == tree2P + 1 || c == tree2P - 1 || c == tree2P - 2 || c == tree2P - 3 || c == tree2P + 3 || c == tree2P + 4))
				|| (r == surface - 4 && (c == tree2P || c == tree2P + 1 || c == tree2P - 3 || c == tree2P - 2 || c == tree2P + 3 || c == tree2P + 4))
				|| (r == surface - 5 && (c == tree2P - 2 || c == tree2P - 3 || c == tree2P + 3 || c == tree2P + 4))
				|| (r == surface - 6 && (c == tree2P + 3 || c == tree2P + 4))

				)
			{
				printTree();
			}


			//fixed Dino
			if (
				((r == dino) && (c == 15 || c == 14 || c == 10 || c == 9))
				|| ((r == dino - 1) && (c >= 8 && c <= 16))
				|| ((r == dino - 2) && (c >= 6 && c <= 18))
				|| ((r == dino - 3) && ((c >= 5 && c <= 19)))
				|| ((r == dino - 4) && ((c >= 9 && c <= 21) || c == 4 || c == 5))
				|| ((r == dino - 5) && ((c >= 11 && c <= 20) || c == 4))
				|| ((r == dino - 6) && ((c >= 13 && c <= 19)))
				|| ((r == dino - 7) && ((c >= 14 && c <= 21)))
				|| ((r == dino - 8) && ((c >= 14 && c <= 22)))
				|| ((r == dino - 9) && ((c >= 14 && c <= 22)))
				|| ((r == dino - 10) && ((c >= 14 && c <= 21)))

				)
			{
				printBlock();
				if (r == dino && (c == 15 || c == 10)) printLS();
				if (r == dino - 1 && (c == 8 || c == 16)) printUS();
				if (r == dino - 2 && (c == 6 || c == 18)) printUS();
				if (r == dino - 3 && (c == 19)) printUS();
				if (r == dino - 4 && (c == 20)) printUS();
				if (r == dino - 4 && (c == 9)) printLS();
				if (r == dino - 5 && (c == 11 || c == 20)) printLS();
				if (r == dino - 6 && (c == 19 || c == 13)) printLS();
				if (r == dino - 7 && (c == 21)) printLS();
				if (r == dino - 9 && (c == 17) && !hit) { Screen.seekp(-1, ios_base::cur); if ((frame / 5) % 30)Screen << ' '; else Screen << 'B'; }
				else if (r == dino - 9 && (c == 17) && hit) { Screen << 'B'; }
				if ((r == dino - 10) && ((c == 14 || c == 21))) printLS();
				if (!stillJumping)
				{
					if ((frame / 5) % 2) { if ((r == dino) && (c == 9 || c == 10)) printUS(); }
					else { if ((r == dino) && (c == 15 || c == 14)) printUS(); }
				}
			}
		}

	}
}

void Printer::screenDisplay()
{
	Screen.seekp(0);

	while (!Screen.eof())
	{
		static string scr;
		getline(Screen, scr);
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			if (scr[x] == 'B' || scr[x] == 'T') { scr[x] = FULL_B; }
			if (scr[x] == 'L') { scr[x] = LO_B; }
			if (scr[x] == 'U' && scr[x - 1] != 'J') { scr[x] = UP_B; }
		}
		//wprintf(L"%s\n", scr);//
		cout << scr << '\n';
	}
	frame++;
	Screen.close();
}

void Printer::openScreen()
{
	Screen.open("cScreen.txt", ios::in | ios::out | ios::trunc);
	if (!Screen.is_open())    Screen.open("cScreen.txt", ios::in | ios::out | ios::trunc);
}

void Printer::printBlock()
{
	Screen.seekp(-1, ios_base::cur);
	Screen.get(d);
	if (d == 'T') { hit = 1; }
	Screen.seekp(-1, ios_base::cur);
	Screen << 'B';
}

//FOR SIMPLICITY THE BBIRD WILL ALSO BE CONTRUCTED FROM THIS TYPE OF BLOCK THAT IT TREE
void Printer::printTree()
{
	Screen.seekp(-1, ios_base::cur);
	Screen.get(d);
	if (d == 'B') { hit = 1; }
	Screen.seekp(-1, ios_base::cur);
	Screen << 'T';
}

