
#include "Utils.h"
#include "RuntimeInfo.h"
#include <sstream>

#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>

#define SCREEN_WIDTH 40*siz
#define SCREEN_HIEGHT  10*siz

#define US (char)223
#define LS (char)220
#define B (char)219

using namespace std;

Utils::Utils()
{

}

void Utils::printTitle()
{

	for (int t = 0; t<SCREEN_HIEGHT; t++) { cout << setfill(' ') << setw(SCREEN_WIDTH) << '\n'; }
	Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4);
	printf("_|_|_|    _|_|_|  _|      _|    _|_|  ");		 Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 1);
	printf("_|    _|    _|    _|_|    _|  _|    _|");        Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 2);
	printf("_|    _|    _|    _|  _|  _|  _|    _|");        Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 3);
	printf("_|    _|    _|    _|    _|_|  _|    _|");        Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 4);
	printf("_|_|_|    _|_|_|  _|      _|    _|_|  ");        Utils::placeCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HIEGHT / 4 + 6);
	printf("    --< THE AGE OF EXTINCTION >--    ");         Utils::placeCursor(SCREEN_WIDTH - 25, SCREEN_HIEGHT + 2);

	printf("build 2.0-rc2-20200514");

	Utils::printSurface();
	Utils::printDinoAnywhere(14, SCREEN_HIEGHT - 5 - 10, 1);
	Utils::printEgg(60, 0);


}

void Utils::printDinoAnywhere(int x, int y, int eyes)
{
	//     y=28
	Utils::placeCursor(x, y++);
	cout << LS << string(6, B) << LS;                                     Utils::placeCursor(x, y++);
	cout << string(4, B);
	if (eyes == 0) cout << B;
	else if (eyes == 1) cout << ' ';
	else if (eyes == 2) cout << "\b  ";
	cout << string(4, B);                             Utils::placeCursor(x, y++);
	cout << string(9, B);                  Utils::placeCursor(x, y++);
	cout << string(7, B) << LS;                                  Utils::placeCursor(x - 1, y++);
	cout << LS << string(5, B) << LS;                            Utils::placeCursor(x - 10, y++);
	cout << B << "      " << LS << string(8, B) << LS;               Utils::placeCursor(x - 10, y++);
	cout << B << B << "   " << LS << string(10, B) << US << B;       Utils::placeCursor(x - 9, y++);
	cout << string(14, B) << US;         Utils::placeCursor(x - 9, y++);
	cout << US << string(12, B) << US;                Utils::placeCursor(x - 7, y++);
	cout << US << string(8, B) << US;                        Utils::placeCursor(x - 5, y++);
	cout << B << LS << "  " << B << LS;

}


void Utils::printSurface()
{
	Utils::placeCursor(0, SCREEN_HIEGHT - 6);
	cout << string(SCREEN_WIDTH, '_'); //for(int x = 0; x < SCREEN_WIDTH; x++){cout << '_';}
}

void Utils::printEgg(int x, bool stone = false)
{
	Utils::placeCursor(x + 2, SCREEN_HIEGHT - 10);
	cout << LS << LS << LS;                            Utils::placeCursor(x, SCREEN_HIEGHT + 1 - 10);
	if (!stone) { cout << LS << string(5, B) << LS;      Utils::placeCursor(x, SCREEN_HIEGHT + 2 - 10); }
	if (stone) { cout << LS << string(4, B) << "  ";      Utils::placeCursor(x, SCREEN_HIEGHT + 2 - 10); }
	if (stone) { cout << B << B << US << LS << "   ";      Utils::placeCursor(x, SCREEN_HIEGHT + 3 - 10); }
	if (!stone) { cout << B << B << US << LS << B << B << B;      Utils::placeCursor(x, SCREEN_HIEGHT - 10 + 3); }
	cout << B << B << ' ' << string(4, B);            Utils::placeCursor(x, SCREEN_HIEGHT + 4 - 10);
	cout << string(7, B);
	if (stone)cout << "   " << string(4, B);
	Utils::placeCursor(x + 1, SCREEN_HIEGHT + 5 - 10);
	cout << US << string(3, B) << US;
}

void Utils::cls()
{
	placeCursor(0, 0);
}

void Utils::credits()
{
	Utils::makeSpaceinConsole();

	Utils::placeCursor(SCREEN_WIDTH / 2 - 19, SCREEN_HIEGHT / 2 - 1);
	cout << "D E V E L O P E D   B Y   M S C 2 4 X";    Utils::placeCursor(SCREEN_WIDTH / 2 - 9, SCREEN_HIEGHT / 2 + 1);
	cout << "with love using c++"; //cout << "WITH LOVE USING C++";
}

void Utils::makeSpaceinConsole()
{
	Utils::placeCursor(0, 0);
	for (int s = 0; s< SCREEN_HIEGHT; s++)
	{
		cout << string(SCREEN_WIDTH, ' ');
		putchar(10);
	}
}

void Utils::hideCursor()
{
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	static CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = false;
	SetConsoleCursorInfo(console, &info);
}

int Utils::nofDigits(int number)
{
	int nofd = 0;
	while (number /= 10)
	{
		nofd++;
	}
	return nofd;
}

void Utils::placeCursor(short int x, short int y)
{
	static HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
	static COORD place;
	place.X = x;
	place.Y = y;
	SetConsoleCursorPosition(cons, place);
}


void Utils::resetGame()
{
	hit = 0;
	surface = SCREEN_HIEGHT - 5;
	quitIt = false;
	dino = surface;
	jumps = 0;
	powerOff = false;
	stillJumping = false;
	// srand(time(NULL));
	treeP = 120 + (rand() % 300);
	tree2P = 120 + (rand() % 300);
	birdP = 300 + rand() % 300;
	score = 0;
	running = true;
	treeVanish = true;
	tree2Vanish = true;
	frame = 0;
	if (difficulty == 2) bestJump = 5;
	if (difficulty == 3) bestJump = 35;
	if (difficulty == 4) bestJump = 60;
}

