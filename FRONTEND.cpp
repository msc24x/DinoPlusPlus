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

#define US (char)223
#define LS (char)220
#define B (char)219

using namespace std;

PrintPaster objPP;
Menu_xtra objMX;
fstream ScreenV;

void FRONTEND::callout()
{
    objMX.placeCursor(30, 23);  putchar(' '); for(int t = 0 ; t < 29; t++) putchar(LS);
    objMX.placeCursor(30, 24);  putchar(B); objMX.placeCursor(60, 24); putchar(B);
    objMX.placeCursor(29, 25);  putchar(B) ;putchar(' '); objMX.placeCursor(60, 25); putchar(B);
    objMX.placeCursor(28, 26);  putchar(B); printf("  "); objMX.placeCursor(60, 26);putchar(B);
    objMX.placeCursor(27, 27);  for(int t = 0 ; t < 33; t++) putchar(US);
}



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
    objMX.placeCursor(0,0);
    for(int s = 0; s< SCREEN_HIEGHT; s++)
    {
        cout << string(SCREEN_WIDTH, ' ');putchar(10); //<< "                                                                                                                       \n";
        //cout << setfill(' ') << setw(SCREEN_WIDTH) << '\n';
    }
}

void FRONTEND::printDinoAnywhere(int x, int y, int eyes)
{
    //     y=28
                                                                        objMX.placeCursor(x,y++);
    cout << LS << string(6,B) << LS;                                     objMX.placeCursor(x, y++);
    cout << string(4,B);
    if(eyes ==0 ) cout << B;
    else if(eyes == 1) cout << ' ';
    else if(eyes == 2) cout << "\b  ";
    cout << string(4,B);                             objMX.placeCursor(x, y++);
    cout << string(9,B);                  objMX.placeCursor(x, y++);
    cout << string(7,B)<< LS;                                  objMX.placeCursor(x-1, y++);
    cout << LS << string(5,B)<< LS;                            objMX.placeCursor(x-10, y++);
    cout << B << "      " << LS<< string(8,B)<< LS;               objMX.placeCursor(x-10, y++);
    cout << B<< B  << "   " << LS<< string(10,B)<< US<< B;       objMX.placeCursor(x-9, y++);
    cout << string(14,B)<< US;         objMX.placeCursor(x-9, y++);
    cout << US<< string(12,B)<< US;                objMX.placeCursor(x-7, y++);
    cout << US<< string(8,B)<< US;                        objMX.placeCursor(x-5, y++);
    cout << B<< LS << "  " << B<< LS;

}


void FRONTEND::change_text_color(WORD color)
{
    HANDLE outH = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO  csBinfo;
    GetConsoleScreenBufferInfo(outH, &csBinfo);
    SetConsoleTextAttribute(outH, color);
}

void FRONTEND::printSurface()
{
    objMX.placeCursor(0,37);
    cout << string(SCREEN_WIDTH, '_'); //for(int x = 0; x < SCREEN_WIDTH; x++){cout << '_';}
}

void FRONTEND::printEgg(int x, bool stone = false)
{
                                                        objMX.placeCursor(x+2, 33);
    cout << LS << LS << LS;                            objMX.placeCursor(x, 34);
    if(!stone)  {cout << LS <<string(5,B)<< LS;      objMX.placeCursor(x, 35);}
    if( stone)  {cout << LS <<string(4,B) << "  ";      objMX.placeCursor(x, 35);}
    if(stone){   cout << B << B << US << LS << "   ";      objMX.placeCursor(x, 36);}
    if(!stone){  cout << B << B << US << LS << B << B << B;      objMX.placeCursor(x, 36);}
    cout << B << B << ' ' << string(4,B);            objMX.placeCursor(x, 37);
    cout << string(7,B);
    if(stone)cout << "___" << string(4,B);
    objMX.placeCursor(x+1, 38);
    cout << US << string(3,B)<< US;
}

void FRONTEND::video()
{
    dinoVP = 37;
    eggVP = 60;
    surface += 2;
    if(sounds)PlaySound("MM.wav", NULL, SND_ASYNC);

    makeSpaceinConsole();
    printSurface();
    printDinoAnywhere(14, 28,0);
    printEgg(eggVP);

    callout(); objMX.placeCursor(32, 25); printf("Zzzzz...ZZzz...            ");

    this_thread::sleep_for(chrono::seconds(3));
    x = 100; y = -4;
    while(1)
    {
    makeSpaceinConsole();
    printSurface();
    printDinoAnywhere(14, 28,0);

    printEgg(eggVP);

    //callout(); objMX.placeCursor(32, 25); cout << "tun , tung tung tung tun...";

    if(y >= 34) break;


                                                            objMX.placeCursor(x,y);
    cout<<"       ....";                    objMX.placeCursor(x,y+1);
    cout<<"   ......"               ;       objMX.placeCursor(x,y+2);
    cout<< LS<<string(4,B)<< LS<< '.';           objMX.placeCursor(x,y+3);
    cout<< string(6,B)<< '.';         objMX.placeCursor(x,y+4);
    cout<< US<< string(4,B)<< US;             objMX.placeCursor(x,y+5);
    y+=2; x-=2;
    this_thread::sleep_for(chrono::milliseconds(90));

    }

    printEgg(eggVP, 1);
    if(sounds)PlaySound("SB.wav", NULL, SND_SYNC);
    printDinoAnywhere(14,28, 2);
    if(sounds)PlaySound("MM.wav", NULL, SND_ASYNC);

    callout(); objMX.placeCursor(32, 25); printf("Oh! what was that?         ");

    this_thread::sleep_for(chrono::seconds(1));

    x = 50; y = 0;
    while(1)
    {
        makeSpaceinConsole();
        printSurface();
        printDinoAnywhere(14, 28,1);
        printEgg(eggVP, 1);

        //callout(); objMX.placeCursor(32, 25); cout << "Oh! what was that?         ";

        if(x < 0) break;
                                                                    objMX.placeCursor(x,y);
        cout<<"                          ......";      objMX.placeCursor(x,y+1);
        cout<<"                   .........";           objMX.placeCursor(x,y+2);
        cout<<"    ..................";             objMX.placeCursor(x,y+3);
        cout<< '.'<< LS<< LS<< string(11,B)<< LS<< LS<< '.'<< '.'<< '.'<< '.';objMX.placeCursor(x,y+4);
        cout<< ' '<<string(15,B)<< ' '<< '.'<< '.';objMX.placeCursor(x,y+5);
        cout<< string(17,B)<< '.';objMX.placeCursor(x,y+6);
        cout<< string(17,B)<< '.';objMX.placeCursor(x,y+7);
        cout<< string(17,B)<< '.';objMX.placeCursor(x,y+8);
        cout<< string(17,B)<< '.';objMX.placeCursor(x,y+9);
        cout<< ' '<< string(16,B);objMX.placeCursor(x,y+10);
        cout<< '.'<< US<< US<< string(11,B)<< US<< US;

	     y+=1; x-=5;
        this_thread::sleep_for(chrono::milliseconds(90));


    }

    if(sounds)PlaySound("LB.wav", NULL, SND_SYNC);

    callout(); objMX.placeCursor(32, 25); printf("I'm sorry my egg . . . Bye!");

    printDinoAnywhere(14,28,2);

    this_thread::sleep_for(chrono::seconds(1));


    dinoVP = 37;
    eggVP = 60;
    while(1)
    {
    if(eggVP >= 14 && eggVP <= 30) dinoVP-=2;
    else if(eggVP < 14) dinoVP+=2;
    if(eggVP < 14 && dinoVP == 37) {system("cls"); break;}
    ScreenV.open("cScreenV.txt", ios::in | ios::out | ios::trunc);
    if(!ScreenV.is_open())ScreenV.open("cScreenV.txt", ios::in | ios::out | ios::trunc);
    for(int r=0; r <SCREEN_HIEGHT; r++)
	{
	    ScreenV << '\n';
		for(int c=0; c<SCREEN_WIDTH; c++)
		{
			//the surface
			if( r==surface-1)
			{
				ScreenV << '_';
            }else  {ScreenV << ' ';}

            //EGG

            if(
                (r == surface && (c >= eggVP && c <= eggVP+4))
            ||  (r == surface-1 && ((c >= eggVP-1 && c <= eggVP+5) || (c >= eggVP+9 && c <= eggVP+12)))
            ||  (r == surface-2 && (c >= eggVP-1 && c <= eggVP+5 && c != eggVP+1))
            ||  (r == surface-3 && (c >= eggVP-1 && c <= eggVP+2))
            ||  (r == surface-4 && (c >= eggVP-1 && c <= eggVP+3))
            ||  (r == surface-5 && (c >= eggVP+1 && c <= eggVP+3))
               )
            {
                 printBlock();
                if(r == surface-5 && (c >= eggVP+1 && c <= eggVP+3))  printLS();
                if(r == surface-4 && (c == eggVP-1 ))  printLS();
                if(r == surface-3 && (c == eggVP+1))  printUS();
                if(r == surface-3 && (c == eggVP+2))  printLS();
                if(r == surface && (c == eggVP || c == eggVP+4))  printUS();
            }



			//fixed dinoVP
			if(
                   ((r == dinoVP) && ( c == 15 || c == 14 || c == 10 || c == 9))
                          ||  ((r == dinoVP-1) && (c >=8 && c <= 16))
                          ||  ((r == dinoVP-2) && (c >=6 && c <= 18))
                          ||  ((r == dinoVP-3) && ((c >=5 && c <= 19)))
                          ||  ((r == dinoVP-4) && ((c >=9 && c <= 21) || c == 4 || c == 5))
                          ||  ((r == dinoVP-5) && ((c >=11 && c <= 20) || c == 4 ))
                          ||  ((r == dinoVP-6) && ((c >=13 && c <= 19)))
                          ||  ((r == dinoVP-7) && ((c >=14 && c <= 21)))
                          ||  ((r == dinoVP-8) && ((c >=14 && c <= 22)))
                          ||  ((r == dinoVP-9) && ((c >=14 && c <= 22)))
                          ||  ((r == dinoVP-10) && ((c >=14 && c <= 21)))

              )
			{
                printBlock();
                if(r==dinoVP && (c == 15 || c == 10))  printLS();
                if(r==dinoVP-1 && (c == 8 || c == 16))  printUS();
                if(r==dinoVP-2 && (c == 6 || c == 18))  printUS();
                if(r==dinoVP-3 && (c == 19))  printUS();
                if(r==dinoVP-4 && (c == 20))  printUS();
                if(r==dinoVP-4 && (c == 9))  printLS();
                if(r==dinoVP-5 && (c == 11 || c == 20))  printLS();
                if(r==dinoVP-6 && (c == 19 || c == 13))  printLS();
                if(r==dinoVP-7 && (c == 21))  printLS();
                if(r==dinoVP-9 && (c == 17) && !hit){ScreenV.seekp(-1, ios_base::cur); if((frame/5)%30)ScreenV << ' '; else ScreenV << 'B'; }
                else if(r==dinoVP-9 && (c == 17) && hit){ScreenV << 'B';}
                if((r == dinoVP-10) && ((c ==14 || c == 21)))  printLS();
                if(!stillJumping)
                {
                    if((frame/5)%2){     if((r==dinoVP) && (c==9 || c==10))  printUS();   }
                    else {     if((r==dinoVP) && (c == 15 || c == 14))  printUS();    }
                }
			}
		}
	}
	objMX.cls();
	ScreenV.seekp(0);
    while(!ScreenV.eof())
    {
        static string scr;
        getline(ScreenV, scr);
        for(int x = 0; x < SCREEN_WIDTH; x++)
        {
            if(scr[x] == 'B' || scr[x] == 'T') {scr[x] = B;}
            if(scr[x] == 'L') {scr[x] = LS;}
            if(scr[x] == 'U') {scr[x] = US;}
        }
        cout << scr << '\n';
    }
    frame++;
    eggVP-=1;
    ScreenV.close();
    }
}

void FRONTEND::credits()
{
    makeSpaceinConsole();

                                                        objMX.placeCursor(SCREEN_WIDTH/2 - 19, SCREEN_HIEGHT/2 - 1);
    cout << "D E V E L O P E D   B Y   M S C 2 4 X";    objMX.placeCursor(SCREEN_WIDTH/2 - 9, SCREEN_HIEGHT/2 + 1);
    cout << "with love using c++"; //cout << "WITH LOVE USING C++";
}

void FRONTEND::printUS()
{
    /*Screen.seekp(-1, ios_base::cur);//putchar('\b');
    Screen.get(d);
    if(d == 'T') { hit = 1; }*/
    ScreenV.seekp(-1, ios_base::cur);
    ScreenV << 'U';
}

void FRONTEND::printLS()
{
    /*Screen.seekp(-1, ios_base::cur);
    Screen.get(d);
    if(d == 'T') { hit = 1; }*/
    ScreenV.seekp(-1, ios_base::cur);
    ScreenV << 'L';
}
void FRONTEND::printBlock()
{
    ScreenV.seekp(-1, ios_base::cur);
    ScreenV.get(d);
    if(d == 'T') { hit = 1; }
    ScreenV.seekp(-1, ios_base::cur);
    ScreenV << 'B';
}
