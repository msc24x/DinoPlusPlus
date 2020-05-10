#ifndef DATAS_H_INCLUDED
#define DATAS_H_INCLUDED

//------------------developed-by-msc24x-------------------------//

// RPERESENTS OBJECTS AND THEIR POSITIONS
extern int surface ;
extern int treeP, tree2P, birdP;
extern int dino ;
extern int birdHeight;

//SUPPORT BOOLEANS FOR REAL TIME INFORMATION
extern bool incmngBirds;
extern int bestJump;
extern bool hit ;
extern long int frame;
extern bool stillJumping;
extern bool powerOff ;
extern bool jumped ;
extern bool running;
extern bool treeVanish ;
extern bool tree2Vanish ;
extern int whenjumped ;
extern int TimeUnit;
extern bool paused ;
extern bool quitIt ;
extern bool cheatOn;
extern bool NewGame;

//TO BE SAVED NECCESSARY
extern int HiScore;
extern int HiJumps;
extern int score ;
extern int jumps;
extern int difficulty;
extern bool sounds;

//EXTRA
extern char d;
extern char j;

#endif // DATAS_H_INCLUDED
