#ifndef Processor_H
#define Processor_H

#include "Menu.h"
#include "Save.h"

class Processor
{
public:
	void linkToMain(Menu OM, Save OS);
	void smoothingJump();
	void gameOver();
	void treesAI();
	void updateRuntimeInfo();
private:
	Menu menu;// obj;
			  //Printer printer;// objPP;
	Save save;// objSave;
};


#endif // Processor_H
