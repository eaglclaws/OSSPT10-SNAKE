/*
Copyright 2022 ������

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
    void autoplay_by_direction(enum board_dir);
    void auto_play();
public:
    AutoGame();
    ~AutoGame() override;
    
    //Get Methods
    bool is_apple_placed() override;
    enum game_state get_state() override;
    enum game_state update() override;
    enum board_elements board_data(int, int) override;
    enum board_dir get_direction() override;
    int** export_board() override;
    int player_score() override;
    int export_dir() override;
    std::vector<std::pair<int, int>>* export_snake() override;
    //Set Methods
    void init() override;
    void play() override;
    void pause() override;
    void over() override;
    void load(int**, std::vector<std::pair<int, int>>*, int) override;
    void key_event(enum key_press) override;

    bool place_apple() override;
    enum board_dir get_direction(enum PlayerSelect) override;
    int get_board_height() override;
    int get_board_width() override;
    void key_event(enum key_press, enum PlayerSelect) override;
    std::pair<int, int> get_head_pos(enum PlayerSelect) override;
    enum PlayerSelect get_winner() override;
};

#endif