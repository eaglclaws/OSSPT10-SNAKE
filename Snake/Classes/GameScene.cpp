#include "GameScene.h"
#include "Game.h"
#include <string>
#include "GameController.h"

bool GameScene::init() {
    if (!LayerColor::initWithColor(cocos2d::Color4B(255, 255, 255, 255))) {
        return false;
    }

    this->gc = GameController::getInstance();
//    game.game_init();

  //  game.game_play();

}


void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    string push_button;

    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        push_button = "North";
        break;
       
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        push_button = "Sorth";
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        push_button = "East";
        break;
    
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        push_button = "West";
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
        push_button = "Esc";
        break;

    }

    //game에 push_button 인자로 주기.

}

