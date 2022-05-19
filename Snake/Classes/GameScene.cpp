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
#include "GameFactory.h"

USING_NS_CC;

#define REFRESH_INTERVAL 0.2 //업데이트 대기 시간 (초)
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
    //필수 변수 지정 TODO: 생성자에 넣어두는 편이 나을까?
    GameFactory *GF = new GameFactory;
    auto GC = GameController::getInstance();
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    auto listener = EventListenerKeyboard::create();
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    rng = new std::mt19937(seed1);
    layer = GamePauseScene::create();
    time = 0.0;
    game = GF->createGame(SOLO);
    bwidth = BOARD_WIDTH;
    bheight = BOARD_HEIGHT;
    sprites = new std::vector<std::vector<Sprite *>>;
    sprites->reserve(bheight); for (int i = 0; i < bheight; i++) sprites->at(i).reserve(bwidth);
    //Scene utility procedures
    layer->setVisible(false);
    addChild(layer, -1);
    for (int y = 0; y < bheight; y++) {
        for (int x = 0; x < bwidth; x++) {
            sprites->at(y).at(x) = Sprite::create("empty.png");
            sprites->at(y).at(x)->setVisible(true);
            addChild(sprites->at(y).at(x), 0);
        }
    }
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //Game initialization
    game->init();
    if (GC->isLoadClicked) {
        game->load(GC->loadBoard(), GC->loadSnake(), GC->loadDirection());
    } else {
        game->place_apple((*rng)() % 40 + 1, (*rng)() % 40 + 1);
    }
    //First Scene update
    update_sprites();
    draw_board();
    scheduleUpdate();
    return true;
}


void 
GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        if (!(game->get_direction() == DOWN)) game->key_event(KEY_UP);
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        if (!(game->get_direction() == UP)) game->key_event(KEY_DOWN);
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        if (!(game->get_direction() == LEFT)) game->key_event(KEY_RIGHT);
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        if (!(game->get_direction() == RIGHT)) game->key_event(KEY_LEFT);
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
        if(game->update() == GAME_STATE_OVER) {
            //게임 종료시 데이터 초기화 구현 완료시 각주 풀 것
            GameController::getInstance()->setScore(game->player_score());
            GameController::getInstance()->resetData();
            auto gameover = GameOverScene::createScene();
            Director::getInstance()->replaceScene(gameover);
        }
        update_sprites();
        draw_board();
        addChild(layer, 1);
        time = 0.0;
    }
    if (!game->is_apple_placed()) {
        game->place_apple((*rng)() % 40 + 1, (*rng)() % 40 + 1);
    }
}

void
GameScene::update_sprites()
{
    for (int y = 0; y < bheight; y++) {
        for (int x = 0; x < bwidth; x++) {
            const char *file;
            enum board_dir facing;
            float angle;
            facing = game->get_direction();
            angle = 0.0f;
            if (facing == UP) {
                angle = -90.0f;
            } else if (facing == DOWN) {
                angle = 90.0f;
            } else if (facing == LEFT) {
                angle = 180.0f;
            }
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
            sprites->at(y).at(x)->setRotation(angle);
            sprites->at(y).at(x)->setTexture(file);
        }
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
