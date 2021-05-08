#include "Menu_xtra.h"
#include "SaveGame.h"
#include "FRONTEND.h"
#include <windows.h>
#include <thread>
#include <iostream>
#include <iomanip>
#include <conio.h>
#define ARR_UP 72
#define ARR_DOWN 80
#define ARR_LEFT 75
#define ARR_RIGHT 77

using namespace std;

FRONTEND objFend;
Processing objProc;

void Menu_xtra::selectSubMech(int n)
{
    nofsubOptions = n;

    keyPressed = _getch();
    if(sounds)PlaySound("menu.wav", NULL , SND_ASYNC);
    if(keyPressed == '\r'){ selected = true;}
    if(keyPressed == ARR_LEFT){ pointingToSubOpt--; if(pointingToSubOpt<1) pointingToSubOpt = 1;}
    if(keyPressed == ARR_RIGHT){ pointingToSubOpt++; if(pointingToSubOpt>nofsubOptions) pointingToSubOpt = nofsubOptions;}
}

void Menu_xtra::selectMech(int n, int Align = 0)
{
    nofOptions = n;
    placeCursor(SCREEN_WIDTH/2 - 8 - Align, 2*SCREEN_HIEGHT/3 - 4 + pointingTo);
    cout << (char)219;

    keyPressed = _getch();
    if(sounds)PlaySound("menu.wav", NULL , SND_ASYNC );
    if(keyPressed == '\r'){ selected = true;}
    if(keyPressed == ARR_UP){ pointingTo--; if(pointingTo<1) pointingTo = 1;}
    if(keyPressed == ARR_DOWN){ pointingTo++; if(pointingTo>nofOptions) pointingTo = nofOptions;}
}

void Menu_xtra::printTitle()
{


    for(int t = 0; t<SCREEN_HIEGHT; t++){cout  << setfill(' ') << setw(SCREEN_WIDTH) << '\n';}
                                                                                    placeCursor(SCREEN_WIDTH/2 - 20, SCREEN_HIEGHT/4);
    printf("_|_|_|    _|_|_|  _|      _|    _|_|  ");                               placeCursor(SCREEN_WIDTH/2 - 20, SCREEN_HIEGHT/4 + 1);
    printf("_|    _|    _|    _|_|    _|  _|    _|");        placeCursor(SCREEN_WIDTH/2 - 20, SCREEN_HIEGHT/4 + 2);
    printf("_|    _|    _|    _|  _|  _|  _|    _|");        placeCursor(SCREEN_WIDTH/2 - 20, SCREEN_HIEGHT/4 + 3);
    printf("_|    _|    _|    _|    _|_|  _|    _|");        placeCursor(SCREEN_WIDTH/2 - 20, SCREEN_HIEGHT/4 + 4);
    printf("_|_|_|    _|_|_|  _|      _|    _|_|  ");        placeCursor(SCREEN_WIDTH/2 - 20, SCREEN_HIEGHT/4 + 6);
    printf("    --< THE AGE OF EXTINCTION >--    ");         placeCursor(SCREEN_WIDTH - 25, SCREEN_HIEGHT+2);

    printf("build 2.0-rc2-20200514");


    objFend.printSurface();
    objFend.printDinoAnywhere(14, 28, 1);
    objFend.printEgg(60,0);


}

void Menu_xtra::cls()
{
    placeCursor(0,0);
    this_thread::sleep_for(chrono::milliseconds(1));
}


void Menu_xtra::hideCursor()
{
    static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    static CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(console, &info);
}

void Menu_xtra::placeCursor(short int x, short int y )
{
    static HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
    static COORD place;
    place.X = x;
    place.Y = y;
    SetConsoleCursorPosition(cons, place);
}


void Menu_xtra::mainMenu(int W, int H)
{
    cls();//system("cls");
    SCREEN_HIEGHT = H; SCREEN_WIDTH = W;
    selected = false;
    printTitle();
    pointingTo = 1;

    while(!selected)
    {
                                      placeCursor(SCREEN_WIDTH/2 - 8 , 2*SCREEN_HIEGHT/3 - 3);
        printf("  Play");             placeCursor(SCREEN_WIDTH/2 - 8, 2*SCREEN_HIEGHT/3 - 2);
        printf("  Settings");         placeCursor(SCREEN_WIDTH/2 - 8, 2*SCREEN_HIEGHT/3 - 1);
        printf("  Help");             placeCursor(SCREEN_WIDTH/2 - 8, 2*SCREEN_HIEGHT/3 );
        printf("  Quit");

        selectMech(4);
    }
    if(sounds)PlaySound("selected.wav", NULL , SND_ASYNC);
    selected = false;
     if(pointingTo == 1)
     {
        if(running)objFend.video();
        objProc.resetGame();
        system("cls");
     }

     if(pointingTo == 2)
     {
         settings();
     }
     if(pointingTo == 3)
     {
         help();
     }
     if(pointingTo == 4)
     {
         quit();
     }
}



void Menu_xtra::settings()
{
    cls();//system("cls");
    printTitle();
    pointingTo = 1;
    selected = false;
    while(!selected)
    {
                                                                    placeCursor(SCREEN_WIDTH/2 - 16, 2*SCREEN_HIEGHT/3 - 5);
        printf("           SETTINGS           ");                   placeCursor(SCREEN_WIDTH/2 - 16, 2*SCREEN_HIEGHT/3 - 3);
        printf("  Challenge   ");
        if(difficulty == 2) printf("    Normal    ");
        if(difficulty == 3) printf("     Hard     " );
        if(difficulty == 4) printf("   Nightmare  " );              placeCursor(SCREEN_WIDTH/2 - 16, 2*SCREEN_HIEGHT/3 - 2)  ;
        printf("  Sounds      ");
        if(sounds == 1) printf("      ON      ");
        if(sounds == 0) printf("     OFF      ") ;                  placeCursor(SCREEN_WIDTH/2 - 16, 2*SCREEN_HIEGHT/3 - 1);
        printf("  Back");
        selectMech(3, 8);
    }
    if(sounds)PlaySound("selected.wav", NULL , SND_ASYNC);
    selected = false;

    if(pointingTo == 1)
    {
        pointingToSubOpt = difficulty-1;
        while(!selected)
        {
            placeCursor(SCREEN_WIDTH/2 - 2, 2*SCREEN_HIEGHT/3 - 3);
            if(pointingToSubOpt == 1) printf("    Normal   >");
            if(pointingToSubOpt == 2) printf("<    Hard    >");
            if(pointingToSubOpt == 3) printf("<  Nightmare  ");
            selectSubMech(3);
        }
        difficulty = pointingToSubOpt+1;
        settings();
    }

    if(pointingTo == 2)
    {
        while(!selected)
        {
            placeCursor(SCREEN_WIDTH/2 - 2, 2*SCREEN_HIEGHT/3 - 2);
            if(pointingToSubOpt == 1) printf("      ON     >");
            if(pointingToSubOpt == 2) printf("<    OFF      ");
            selectSubMech(2);
        }
        if(sounds)PlaySound("selected.wav", NULL , SND_ASYNC);
        if(pointingToSubOpt == 1) sounds = true;
        else if(pointingToSubOpt == 2) sounds = false;
        settings();
    }

    if(pointingTo == 3) mainMenu(SCREEN_WIDTH, SCREEN_HIEGHT);
}


void Menu_xtra::help()
{
    cls();//system("cls");
    printTitle();
    pointingTo = 1;
    selected = false;
                                                                            placeCursor(SCREEN_WIDTH/2 - 8,  2*SCREEN_HIEGHT/3 - 5);
    printf("   HELP");                                                      placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 - 3);
    printf("In the Cretaceous age, meteors are showering and you have ");     placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 - 2);
    printf("   to save the one of the last few dinosaurs from the   ");     placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 - 1);
    printf("         incoming obstacles from going extinct.         ");     placeCursor(SCREEN_WIDTH/2 - 8, 2*SCREEN_HIEGHT/3 + 1);
    printf(" CONTROLS");                                                    placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 + 3);
    printf("                  P - Pause  Q - Quit                 ");     placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 + 4);
    printf("               SPACE - Jump  Z - AI Mode              ");

    if(cin.get())
    {
        selected = true;
        mainMenu(SCREEN_WIDTH, SCREEN_HIEGHT);
    }
}

void Menu_xtra::quit()
{
    quitIt = true;
}
