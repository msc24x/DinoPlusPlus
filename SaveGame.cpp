#include "SaveGame.h"
#include "Menu_xtra.h"
#include <fstream>
#include "DATAS.h"
#define SCREEN_WIDTH 160
#define SCREEN_HIEGHT 40
using namespace std;

fstream SAVEFILE;

SaveGame::SaveGame(){}


bool SaveGame::openSaveFile()
{
    SAVEFILE.open("SavedData.txt", ios::in | ios::out);
    if(!(SAVEFILE.is_open()))
    {
        SAVEFILE.open("SavedData.txt", ios::trunc | ios::in | ios::out);
    }
    return true;
}


void SaveGame::Loading(bool file_opened)
{
    if(file_opened)
    {
        SAVEFILE.seekp(0);
        //  SAVING MANNER   // High Score -- Highest jumps -- Difficulty -- sounds
        SAVEFILE >> HiScore;      if(HiScore<0)          HiScore = 0;
        SAVEFILE >> HiJumps;      if(HiJumps<0)          HiJumps = 0;
        SAVEFILE >> difficulty;   if(!(difficulty >= 2  && difficulty<=4) )      difficulty = 2;
        SAVEFILE >> sounds;       if(sounds != 1 && sounds != 0)           sounds = true;
    }
    if(file_opened)
    {
        SAVEFILE.close();
    }
}

void SaveGame::Saving(bool file_opened)
{
    if(file_opened)
    {
        SAVEFILE.seekp(0);
        SAVEFILE << HiScore;
        SAVEFILE << ' ' << HiJumps;
        SAVEFILE << ' ' << difficulty;
        SAVEFILE << ' ' << (int)sounds;
        SAVEFILE.close();
    }
}
