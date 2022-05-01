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

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <array>
#include "cocos2d.h"
#include "Board.h"
#include "Game.h"
#include "GamePauseLayer.h"

class GameScene : public cocos2d::Scene
{
private:
    std::array<std::array<cocos2d::Sprite *, BOARD_WIDTH>, BOARD_HEIGHT> *sprites;
    Board *board;
    Game *game;
    GamePauseLayer* layer;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    float time;
    int test;
public:
    static cocos2d::Scene *
    createScene();

    virtual bool
    init();
	
	virtual void 
	onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	
    void
    menuCloseCallback(cocos2d::Ref *pSender);

    void
    update(float);

    void
    update_sprites();

    CREATE_FUNC(GameScene);
    
private:
    void
    draw_board();
};

#endif