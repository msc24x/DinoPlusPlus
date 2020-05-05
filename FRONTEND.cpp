#include "FRONTEND.h"
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

#define SCREEN_WIDTH 160
#define SCREEN_HIEGHT 40

using namespace std;

PrintPaster objPP;

int FRONTEND::nofdigits(int number)
{
    int nofd = 0;
    while(number/=10)
    {
        nofd++;
    }
    return nofd;
}

void FRONTEND::makeSpaceinConsole()
{
    system("cls");
    for(int s = 0; s< SCREEN_HIEGHT; s++)
    {
        cout << setw(SCREEN_WIDTH) << '\n';
    }
}

void FRONTEND::printDinoAnywhere(int x, int y)
{

}


void FRONTEND::change_text_color(WORD color)
{
    HANDLE outH = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO  csBinfo;
    GetConsoleScreenBufferInfo(outH, &csBinfo);
    SetConsoleTextAttribute(outH, color);
}
