#ifndef PROCESSING_H
#define PROCESSING_H

#include "Menu_xtra.h"
#include "PrintPaster.h"
#include "DATAS.h"
#include "SaveGame.h"

class Processing
{
    public:
        void linkToMain(Menu_xtra OM,        PrintPaster OP,       SaveGame OS);
        void smoothingJump();
        void gameOver();
        void treesAI();
        void resetGame();
        void updateDatas();
    private:
        Menu_xtra obj;
        PrintPaster objPP;
        SaveGame objSave;
};


#endif // PROCESSING_H
