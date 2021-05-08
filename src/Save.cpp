
#include "Save.h"
#include <fstream>
#include <iostream>
#include "RuntimeInfo.h"


#define SCREEN_WIDTH 40*siz
#define SCREEN_HIEGHT  10*siz

//int SCREEN_WIDTH = 40*siz;
//int SCREEN_HIEGHT = 10*siz;
using namespace std;

//fstream SAVEFILE;

//void Save() {  }


fstream SAVEFILE;

bool Save::openSaveFile()
{
	SAVEFILE.open("SavedData.txt", ios::in | ios::out);
	if (!(SAVEFILE.is_open()))
	{
		SAVEFILE.open("SavedData.txt", ios::trunc | ios::in | ios::out);
	}
	return true;
}

void Save::Loading(bool file_opened)
{
	if (file_opened)
	{
		SAVEFILE.seekp(0);
		//  SAVING MANNER   // High Score -- Highest jumps -- Difficulty -- sounds
		SAVEFILE >> HiScore;      if (HiScore<0)          HiScore = 0;
		SAVEFILE >> HiJumps;      if (HiJumps<0)          HiJumps = 0;
		SAVEFILE >> difficulty;   if (!(difficulty >= 2 && difficulty <= 4))      difficulty = 2;
		SAVEFILE >> sounds;       if (sounds != 1 && sounds != 0)           sounds = true;
		SAVEFILE >> siz;          if (siz < 0) siz = 4;
	}
	if (file_opened)
	{
		SAVEFILE.close();
	}
	if (difficulty == 2) bestJump = 5;
	if (difficulty == 3) bestJump = 35;
	if (difficulty == 4) bestJump = 60;
}

void Save::Saving(bool file_opened)
{
	if (file_opened)
	{
		SAVEFILE.seekp(0);
		SAVEFILE << HiScore;
		SAVEFILE << ' ' << HiJumps;
		SAVEFILE << ' ' << difficulty;
		SAVEFILE << ' ' << (int)sounds;
		SAVEFILE << ' ' << siz << ' ';
		SAVEFILE.close();
	}
	if (difficulty == 2) bestJump = 5;
	if (difficulty == 3) bestJump = 35;
	if (difficulty == 4) bestJump = 60;
}
