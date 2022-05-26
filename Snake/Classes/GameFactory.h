#ifndef __GAME_FACTORY_H__
#define __GAME_FACTORY_H__

class Game;

class GameFactory {
public:
    Game *createGame(enum game_T);
};

#endif
