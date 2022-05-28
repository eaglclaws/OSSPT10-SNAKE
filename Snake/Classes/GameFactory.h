#ifndef __GAME_FACTORY_H__
#define __GAME_FACTORY_H__
#include "EnumList.h"

class Game;

class GameFactory {
public:
    Game *createGame(enum game_T);
};

#endif
