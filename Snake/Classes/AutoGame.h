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

#ifndef __AUTOGAME_H_
#define __AUTOGAME_H_
#include "Game.h"
#include <vector>
#include <utility>
#include "Board.h"


class AutoGame: public Game {
private:
    Board* board;
    enum game_state state;
public:
    AutoGame();
    ~AutoGame();
    
    enum game_state get_state() override;

    void init() override;

    void play() override;

    void pause() override;

    void over() override;

    
    enum game_state update() override;

    enum board_elements board_data(int, int) override;

    enum board_dir get_direction() override;
    
    bool place_apple(int, int) override;

    int player_score() override;

    bool is_apple_placed() override;

    //알고리즘 완성 후에 함수의 형태는 변형될 수 있음.
    void auto_play();
};

#endif
