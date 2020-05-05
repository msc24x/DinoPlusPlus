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


class FRONTEND
{
    public:
        int nofdigits(int number);
        void makeSpaceinConsole();
        void printDinoAnywhere(int x, int y);
        void change_text_color(WORD color);
    private:
};

#endif // FRONTEND_H
