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
#include "GameScene.h"
#include "Board.h"
#include "GamePauseLayer.h"

USING_NS_CC;

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
    if (!Scene::init()) return false;

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    game = new Game;
    sprites = new std::array<std::array<Sprite *, BOARD_WIDTH>, BOARD_HEIGHT>;
    time = 0.0;
    float xoffset = visibleSize.width / 2 - sprite_size * BOARD_WIDTH / 2;
    float yoffset = visibleSize.height / 2 - sprite_size * BOARD_HEIGHT / 2;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            Sprite *temp;
            const char *file;
            switch (game->board_data(x, y)) {
            case EMPTY:
                temp = nullptr;
                break;
            case WALL:
                file = "wall.png";
                break;
            case HEAD:
                file = "snake_head.png";
                break;
            case SNAKE:
                file = "snake_body.png";
                break;
            }
            temp = Sprite::create(file);
            sprites->at(y).at(x) = temp;
        }
    }
    draw_board();
    scheduleUpdate();
    return true;
}


void 
GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        game->key_event(KEY_UP);
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        game->key_event(KEY_DOWN);
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        game->key_event(KEY_RIGHT);
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        game->key_event(KEY_LEFT);
        break;

    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
        
        game->key_event(KEY_ESC);

        // 이 부분 변경됨.
        GameController::setGame(game);

        this->layer = GamePauseLayer::create();
        this->layer->setVisible(true);
        break;
    }
}


void
GameScene::update(float delta)
{
    time += delta;
    if (time > 0.2) {
        if (test = (test + 1) % 2) {
            game->key_event(KEY_LEFT);
        } else {
            game->key_event(KEY_UP);
        }
        if(!game->update()) Director::getInstance()->stopAnimation();
        update_sprites();
        draw_board();
        time = 0.0;
    }
}

void
GameScene::update_sprites()
{
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            Sprite *temp;
            const char *file;
            //if (sprites->at(y).at(x) != nullptr) {
            //    delete sprites->at(y).at(x);
            //}
            switch (game->board_data(x, y)) {
            case EMPTY:
                temp = nullptr;
                break;
            case WALL:
                file = "wall.png";
                temp = Sprite::create(file);
                break;
            case HEAD:
                file = "snake_head.png";
                temp = Sprite::create(file);
                break;
            case SNAKE:
                file = "snake_body.png";
                temp = Sprite::create(file);
                break;
            }
            sprites->at(y).at(x) = temp;
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
    float xoffset = visibleSize.width / 2 - sprite_size * BOARD_WIDTH / 2;
    float yoffset = visibleSize.height / 2 - sprite_size * BOARD_HEIGHT / 2;

    removeAllChildren();
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (sprites->at(y).at(x) != nullptr) {
                sprites->at(y).at(x)->setPosition(Vec2(origin.x + x * sprite_size + xoffset, origin.y + y * sprite_size + yoffset));
                addChild(sprites->at(y).at(x), 0);
            }
        }
    }
}

