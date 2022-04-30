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
    if (!Scene::init()) return false;

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    game = new Game;
    game->place_apple(10, 10);
    sprites = new std::array<std::array<Sprite *, BOARD_WIDTH>, BOARD_HEIGHT>;
    time = 0.0;
    float xoffset = visibleSize.width / 2 - sprite_size * BOARD_WIDTH / 2;
    float yoffset = visibleSize.height / 2 - sprite_size * BOARD_HEIGHT / 2;
    update_sprites();
    draw_board();
    scheduleUpdate();
    return true;
}

void
GameScene::update(float delta)
{
    time += delta;
    if (time > REFRESH_INTERVAL) {
        if(game->update() == GAME_STATE_OVER) Director::getInstance()->stopAnimation();
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
                temp = nullptr;
                break;
            case WALL:
                file = "wall.png";
                temp = Sprite::create(file);
                break;
            case HEAD:
                file = "snake_head.png";
                temp = Sprite::create(file);
                if (temp == nullptr) printf("Warning!");
                temp->setRotation(angle);
                break;
            case SNAKE:
            case APPLE:
                file = "snake_body.png";
                temp = Sprite::create(file);
                break;
            case TAIL:
                file = "snake_tail.png";
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