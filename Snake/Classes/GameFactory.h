#ifndef __GAME_FACTORY_H__
#define __GAME_FACTORY_H__

class Game;

enum game_T {
    SOLO,
    DUAL,
    AUTO1,
    AUTO2
};

class GameFactory {
public:
    Game *createGame(enum game_T);
};

#endif
