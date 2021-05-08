#pragma once
class Utils
{
public:
	Utils();

	static void printTitle();

	static void printDinoAnywhere(int x, int y, int eyes);

	static void printSurface();

	static void printEgg(int x, bool stone);

	static void cls();
	static void credits();
	static void makeSpaceinConsole();
	static void hideCursor();
	static int nofDigits(int number);
	static void placeCursor(short int x, short int y);
	static void resetGame();


};

