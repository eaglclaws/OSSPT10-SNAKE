#include "GameFactory.h"
#include "Game.h"
#include "SoloGame.h"
#include "DualGame.h"
#include "AutoGame.h"

Game *GameFactory::createGame(enum game_T game_type)
{
    
    switch (game_type) {
    case SOLO:
        return new SoloGame;
    case DUAL:
        return new DualGame;
    case AUTO1:
        return new AutoGame;

    default:
        return NULL;
    }
}
