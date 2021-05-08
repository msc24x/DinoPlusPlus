#ifndef Video_H
#define Video_H



#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>


class Video
{
public:
	//void printDinoAnywhere(int x, int y, int eyes);
	//void printSurface();
	//void printEgg(int x, bool);
	void callout();

	void video();

	void printUS();
	void printLS();

	void printBlock();

private:

	int dinoVP = 37;
	int eggVP = 60;
	int x, y;

};

#endif // Video_H
