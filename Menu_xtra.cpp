#include "Menu_xtra.h"
#include "SaveGame.h"
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

void Menu_xtra::selectSubMech(int n)
{
    nofsubOptions = n;

    keyPressed = _getch();
    if(sounds)PlaySound("JUMP.wav", NULL , SND_ASYNC);
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
    if(sounds)PlaySound("JUMP.wav", NULL , SND_ASYNC );
    if(keyPressed == '\r'){ selected = true;}
    if(keyPressed == ARR_UP){ pointingTo--; if(pointingTo<1) pointingTo = 1;}
    if(keyPressed == ARR_DOWN){ pointingTo++; if(pointingTo>nofOptions) pointingTo = nofOptions;}
}

void Menu_xtra::printTitle()
{
    for(int t = 0; t<SCREEN_HIEGHT; t++){cout << '\n' << setfill(' ') << setw(SCREEN_WIDTH/2 - 29);}

                                                                                    placeCursor(SCREEN_WIDTH/2 - 41, SCREEN_HIEGHT/4);
    cout <<"_|_|_|    _|_|_|  _|      _|    _|_|   ";                               placeCursor(SCREEN_WIDTH/2 - 29, SCREEN_HIEGHT/4 + 1);
    cout <<"_|    _|    _|    _|_|    _|  _|    _|      _|        _|     " ;        placeCursor(SCREEN_WIDTH/2 - 29, SCREEN_HIEGHT/4 + 2);
    cout <<"_|    _|    _|    _|  _|  _|  _|    _|    _|_|_|    _|_|_|    ";        placeCursor(SCREEN_WIDTH/2 - 29, SCREEN_HIEGHT/4 + 3);
    cout <<"_|    _|    _|    _|    _|_|  _|    _|      _|        _|      ";        placeCursor(SCREEN_WIDTH/2 - 29, SCREEN_HIEGHT/4 + 4);
    cout <<"_|_|_|    _|_|_|  _|      _|    _|_|   ";
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
    system("cls");
    SCREEN_HIEGHT = H; SCREEN_WIDTH = W;
    selected = false;
    printTitle();
    pointingTo = 1;

    while(!selected)
    {
                                      placeCursor(SCREEN_WIDTH/2 - 8 , 2*SCREEN_HIEGHT/3 - 3);
        cout << "  Play";             placeCursor(SCREEN_WIDTH/2 - 8, 2*SCREEN_HIEGHT/3 - 2);
        cout << "  Settings";         placeCursor(SCREEN_WIDTH/2 - 8, 2*SCREEN_HIEGHT/3 - 1);
        cout << "  Help";             placeCursor(SCREEN_WIDTH/2 - 8, 2*SCREEN_HIEGHT/3 );
        cout << "  Quit";

        selectMech(4);
    }
    selected = false;
     if(pointingTo == 1)
     {

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
    system("cls");
    printTitle();
    pointingTo = 1;
    selected = false;
    while(!selected)
    {
                                                                    placeCursor(SCREEN_WIDTH/2 - 16, 2*SCREEN_HIEGHT/3 - 5);
        cout << "           SETTINGS           ";                   placeCursor(SCREEN_WIDTH/2 - 16, 2*SCREEN_HIEGHT/3 - 3);
        cout << "  Challenge   ";
        if(difficulty == 2) cout << "    Normal    ";
        if(difficulty == 3) cout << "     Hard     " ;
        if(difficulty == 4) cout << "   Nightmare  " ;              placeCursor(SCREEN_WIDTH/2 - 16, 2*SCREEN_HIEGHT/3 - 2)  ;
        cout << "  Sounds      ";
        if(sounds == 1) cout << "      ON      ";
        if(sounds == 0) cout << "     OFF      " ;                  placeCursor(SCREEN_WIDTH/2 - 16, 2*SCREEN_HIEGHT/3 - 1);
        cout << "  Back";
        selectMech(3, 8);
    }
    selected = false;

    if(pointingTo == 1)
    {
        pointingToSubOpt = difficulty-1;
        while(!selected)
        {
            placeCursor(SCREEN_WIDTH/2 - 2, 2*SCREEN_HIEGHT/3 - 3);
            if(pointingToSubOpt == 1) cout << "    Normal   >";
            if(pointingToSubOpt == 2) cout << "<    Hard    >";
            if(pointingToSubOpt == 3) cout << "<  Nightmare  ";
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
            if(pointingToSubOpt == 1) cout << "      ON     >";
            if(pointingToSubOpt == 2) cout << "<    OFF      ";
            selectSubMech(2);
        }
        if(pointingToSubOpt == 1) sounds = true;
        else if(pointingToSubOpt == 2) sounds = false;
        settings();
    }

    if(pointingTo == 3) mainMenu(SCREEN_WIDTH, SCREEN_HIEGHT);
}


void Menu_xtra::help()
{
    system("cls");
    printTitle();
    pointingTo = 1;
    selected = false;
                                                                            placeCursor(SCREEN_WIDTH/2 - 8,  2*SCREEN_HIEGHT/3 - 5);
    cout << "    HELP  ";                                                   placeCursor(SCREEN_WIDTH/2 - 8,  2*SCREEN_HIEGHT/3 - 4);
    cout << "          ";                                                   placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 - 3);
    cout << "  You have the responsibility to save the last dinosaur ";     placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 - 2);
    cout << "                on Earth from extinction.               ";     placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 - 0);
    cout << "  Too easy!? You can always change the difficulty in the";     placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 + 1);
    cout << "                     Settings menu.                     ";     placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 + 2);
    cout << "                      P  - Pause                        ";     placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 + 3);
    cout << "                       Q - Quit                         ";     placeCursor(SCREEN_WIDTH/2 - 30, 2*SCREEN_HIEGHT/3 + 4);
    cout << "                     SPACE - Jump                       ";

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
