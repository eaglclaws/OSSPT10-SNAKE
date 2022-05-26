#include "GameFactory.h"
#include "Game.h"
#include "SoloGame.h"
#include "GameController.h"


Game *GameFactory::createGame(enum game_T game_type)
{
    
    switch (game_type) {
    case SOLO:
        GameController::getInstance()->set_players(1);
        return new SoloGame;
    /*case DUAL:
        return new DualGame;*/
    default:
        return NULL;
    }
}
