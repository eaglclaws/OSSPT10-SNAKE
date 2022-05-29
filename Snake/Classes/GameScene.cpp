/*
Copyright 2022 고석현

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <stdio.h>
#include <array>
#include <vector>
#include <utility>
#include <chrono>
#include <random>
#include "GameScene.h"
#include "SoloGame.h"
#include "Board.h"
#include "GamePauseScene.h"
#include "GameController.h"
#include "GameOverScene.h"
#include "SoloGame.h"
#include "GameFactory.h"
#include "DualResultScene.h"
#include "ShowResultScene.h"
#include "AutoGame2.h"

USING_NS_CC;

#define REFRESH_INTERVAL 0.1 //업데이트 대기 시간 (초)
const int sprite_size = 16;

Scene *
GameScene::createScene()
{
    return GameScene::create();
}

static void
problemLoading(const char *filename)
{
    printf("Error while loading: %s\n", filename);
}

bool
GameScene::init()
{
    //Scene 초기화
    if (!Scene::init()) return false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto GC = GameController::getInstance();
    GameFactory* GF = new GameFactory;

    game = GF->createGame(GC->get_game_type());
    game->place_apple();
    bwidth = game->get_board_width();
    bheight = game->get_board_height();
    sprites = new std::vector<std::vector<Sprite*>>(bheight);
    for (int i = 0; i < bheight; i++) sprites->at(i) = std::vector<Sprite*>(bwidth);

    time = 0.0;

    listener = EventListenerKeyboard::create();
    layer = GamePauseScene::create();
 
    layer->setVisible(false);
    addChild(layer, -1);

    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    for (int y = 0; y < bheight; y++) {
        for (int x = 0; x < bwidth; x++) {
            sprites->at(y).at(x) = Sprite::create("empty.png");
            sprites->at(y).at(x)->setVisible(true);
            addChild(sprites->at(y).at(x), 0);
        }
    }

    game->init();
    if (GC->isLoadClicked) {
        game->load(GC->loadBoard(), GC->loadSnake(), GC->loadDirection());
    } else {
        game->place_apple();
    }

    update_sprites();
    draw_board();
    scheduleUpdate();
    return true;
}


void 
GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        if (!(game->get_direction(PLAYER1) == DOWN) && !pressed) {
            game->key_event(KEY_UP, PLAYER1);
            pressed = true;
        }
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        if (!(game->get_direction(PLAYER1) == UP) && !pressed) {
            game->key_event(KEY_DOWN, PLAYER1);
            pressed = true;
        }
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        if (!(game->get_direction(PLAYER1) == LEFT) && !pressed) {
            game->key_event(KEY_RIGHT, PLAYER1);
            pressed = true;
        }
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        if (!(game->get_direction(PLAYER1) == RIGHT) && !pressed) {
            game->key_event(KEY_LEFT, PLAYER1);
            pressed = true;
        }
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W: case cocos2d::EventKeyboard::KeyCode::KEY_W:
        if (!(game->get_direction(PLAYER2) == DOWN) && !pressed) {
            game->key_event(KEY_W, PLAYER2);
            pressed = true;
        }
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S: case cocos2d::EventKeyboard::KeyCode::KEY_S:
        if (!(game->get_direction(PLAYER2) == UP) && !pressed ) {
            game->key_event(KEY_S, PLAYER2);
            pressed = true;
        }
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D: case cocos2d::EventKeyboard::KeyCode::KEY_D:
        if (!(game->get_direction(PLAYER2) == LEFT) && !pressed) {
            game->key_event(KEY_D, PLAYER2);
            pressed = true;
        }
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A: case cocos2d::EventKeyboard::KeyCode::KEY_A:
        if (!(game->get_direction(PLAYER2) == RIGHT) && !pressed) {
            game->key_event(KEY_A, PLAYER2);
            pressed = true;
        }
        break;


    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
        if (game->get_state() == GAME_STATE_PAUSE) {
            layer->setVisible(false);
            game->play();
        } else {
            game->key_event(KEY_ESC);
            GameController::getInstance()->setGame(game);
            this->layer->setVisible(true);
        }
        break;
    }
}


void
GameScene::update(float delta)
{
    if (game->get_state() == GAME_STATE_OVER) return;
    time += delta;
    
    if (time > REFRESH_INTERVAL && !(game->get_state() == GAME_STATE_PAUSE)) {
        if (pressed) {
            listener->setEnabled(false);
        }
        if(game->update() == GAME_STATE_OVER) {
            //게임 종료시 데이터 초기화 구현 완료시 각주 풀 것
            auto GC = GameController::getInstance();

            GC->setScore(game->player_score());
            GC->resetData();
            GC->set_winner(game->get_winner());
            enum game_T game_type = GC->get_game_type();
            
            if (game_type == SOLO) {
                auto gameover = GameOverScene::createScene();
                Director::getInstance()->replaceScene(gameover);
            }
            else if (game_type == DUAL) {
                auto gameover = DualResultScene::createScene();
                Director::getInstance()->replaceScene(gameover);
            } else {
                auto gameover = ShowResultScene::createScene();
                Director::getInstance()->replaceScene(gameover);
            }
        }
        update_sprites();
        draw_board();
        addChild(layer, 1);
        time = 0.0;
        pressed = false;
    }
    if (!game->is_apple_placed()) {
        game->place_apple();
    }
    if (!pressed) {
        listener->setEnabled(true);
    } else {
        listener->setEnabled(false);
    }
}

void
GameScene::update_sprites()
{
    for (int y = 0; y < bheight; y++) {
        for (int x = 0; x < bwidth; x++) {
            const char *file;
         
            switch (game->board_data(x, y)) {
            case EMPTY:
                file = "empty.png";
                break;
            case WALL:
                file = "wall.png";
                break;
            case HEAD:
                file = "snake_head.png";
                break;
            case SNAKE:
            case APPLE:
                file = "snake_body.png";
                break;
            case TAIL:
                file = "snake_tail.png";
                break;
            }
            sprites->at(y).at(x)->setTexture(file);
        }
    } 

    enum board_dir facing;
    float angle = 0.0f;
    std::pair<int, int> pos;

    for (int i = 0; i < GameController::getInstance()->get_players(); i++) {
        angle = 0.0f;
        enum PlayerSelect player = static_cast<PlayerSelect>(i);
        facing = game->get_direction(player);
        if (facing == UP) {
            angle = -90.0f;
        }
        else if (facing == DOWN) {
            angle = 90.0f;
        }
        else if (facing == LEFT) {
            angle = 180.0f;
        }
        pos = game->get_head_pos(player);

        sprites->at(pos.second).at(pos.first)->setRotation(angle);
    }
}

void
GameScene::menuCloseCallback(Ref *pSender)
{
    Director::getInstance()->end();
}

void
GameScene::draw_board()
{
    float xoffset = visibleSize.width / 2 - sprite_size * bwidth / 2;
    float yoffset = visibleSize.height / 2 - sprite_size * bheight / 2;

    for (int y = 0; y < bheight; y++) {
        for (int x = 0; x < bwidth; x++) {
            if (sprites->at(y).at(x) != nullptr) {
                sprites->at(y).at(x)->setPosition(Vec2(origin.x + x * sprite_size + xoffset, origin.y + y * sprite_size + yoffset));
            }
        }
    }
}
