#include "GameFactory.h"
#include "Game.h"
#include "SoloGame.h"

Game *GameFactory::createGame(enum game_T game_type)
{
    switch (game_type) {
    case SOLO:
        return new SoloGame;
    default:
        return NULL;
    }
}
