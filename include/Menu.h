#ifndef Menu_H
#define Menu_H


class Menu
{
private:
	//int SCREEN_HIEGHT, SCREEN_WIDTH;
	bool selected = 0;
	int pointingTo = 1;
	int keyPressed;
	int nofOptions;
	int nofsubOptions;
	int pointingToSubOpt = 1;
public:
	void selectSubMech(int n);
	void selectMech(int n, int Align);
	/*void hideCursor();
	void placeCursor(short int x, short int y);
	void cls();
	void printTitle();

	void resetGame();*/

	void mainMenu(int, int);
	void settings();
	void help();
	void quit();
};

#endif // Menu_H
