#ifndef FRONTEND_H
#define FRONTEND_H

#include "Menu_xtra.h"
#include "PrintPaster.h"
#include "DATAS.h"
#include "SaveGame.h"
#include "Processing.h"

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>


class FRONTEND
{
    public:
        int nofdigits(int number);
        void makeSpaceinConsole();
        void printDinoAnywhere(int x, int y, int eyes);
        void change_text_color(WORD color);
        void printSurface();
        void printEgg(int x, bool );
        void callout();

        void video();


        void printUS();
        void printLS();

        void credits();

        void printBlock();
    private:

        int dinoVP = 37;
        int eggVP = 60;
        int x,y;

};

#endif // FRONTEND_H
