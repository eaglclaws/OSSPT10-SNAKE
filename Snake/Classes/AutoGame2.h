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

#ifndef __AUTO_GAME_2_H__
#define __AUTO_GAME_2_H__

#include "Game.h"
#include <deque>
#include <tuple>

class AutoGame2 : public Game {
private:
    class AutoBoard {
    private:
        struct point {
            point(int a, int b)
            {
                x = b;
                y = a;
            }
            int x;
            int y;
        };
        std::vector<std::vector<enum board_elements>> board;
        int width;
        int height;
        std::deque<struct point *> snake;
        enum board_dir current_dir;
        struct snake_node **head;
        struct snake_node **tail;
        int snake_length;
        bool apple_placed;
        int apple_x;
        int apple_y;
        int head_x;
        int head_y;
    public:
        AutoBoard(int, int);
        enum board_elements at(int, int);
        void set_dir(enum board_dir);
        enum board_dir get_dir();
        bool update();
        bool place_apple();
        void set_apple(int, int);
        int get_snake_length();
        bool is_apple_placed();
        int get_width();
        int get_height();
        int get_head_x();
        int get_head_y();
        int get_apple_x();
        int get_apple_y();
        void init();
    };
    enum game_state state;
    AutoGame2::AutoBoard *board;
    std::vector<std::vector<int>> graph;
    std::vector<int> dist;
    std::vector<int> prev;
    std::vector<int> Q;
    std::deque<int> path; 
public:
    AutoGame2(int, int);
    //State modification methods
    void init() override;
    void play() override;
    void pause() override;
    void over() override;
    enum game_state update() override;
    bool place_apple() override; //TODO: Eventually deprecate this method
    //State report methods
    enum game_state get_state() override;
    enum board_elements board_data(int, int) override;
    enum board_dir get_direction() override;
    int player_score() override;
    bool is_apple_placed() override;
    //Unnecessary methods
    void key_event(enum key_press) override;
    std::vector<std::pair<int, int>> *export_snake() override;
    int export_dir() override;
    int **export_board() override;
    void load(int **, std::vector<std::pair<int, int>> *, int) override;
    std::pair<int, int> get_head_pos(enum PlayerSelect) override;
    board_dir get_direction(enum PlayerSelect) override;
    int get_board_height() override;
    int get_board_width() override;
    void key_event(enum key_press, enum PlayerSelect) override;
    enum PlayerSelect get_winner() override;
private:
    enum board_dir next_dir(int, int, int, int);
    void scan_graph();
};

#endif
