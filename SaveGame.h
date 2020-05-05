#ifndef SAVEGAME_H
#define SAVEGAME_H
#include "Menu_xtra.h"
#include "DATAS.h"
#include <fstream>
class SaveGame
{
    public:
        SaveGame();
        bool openSaveFile();
        void Loading(bool file_opened);
        void Saving(bool file_opened);
    private:
        Menu_xtra menu_obj;

};

#endif // SAVEGAME_H
