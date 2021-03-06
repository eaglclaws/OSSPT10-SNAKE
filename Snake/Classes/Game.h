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

#ifndef __GAME_H_
#define __GAME_H_
#include <vector>
#include <utility>
#include "Board.h"
#include "EnumList.h"


class Game {
public:
    virtual ~Game() = 0;
    virtual enum game_state get_state() = 0;
    virtual void init() = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void over() = 0;
    virtual enum game_state update() = 0;
    virtual enum board_elements board_data(int, int) = 0;
    virtual enum board_dir get_direction() = 0;
    virtual void key_event(enum key_press) = 0;

    virtual int player_score() = 0;
    virtual int **export_board() = 0;
    virtual std::vector<std::pair<int, int>> *export_snake() = 0;
    virtual int export_dir() = 0;
    virtual void load(int **, std::vector<std::pair<int, int>> *, int) = 0;
    virtual bool is_apple_placed() = 0;

    virtual bool place_apple() = 0 ;
    virtual std::pair<int, int> get_head_pos(enum PlayerSelect) = 0;
    virtual int get_board_height() = 0;
    virtual int get_board_width() = 0;
    virtual void key_event(enum key_press, enum PlayerSelect) = 0;
    virtual board_dir get_direction(enum PlayerSelect) = 0;
    virtual enum PlayerSelect get_winner() = 0;
};
inline Game::~Game() {}
#endif
