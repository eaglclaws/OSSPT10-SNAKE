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

#include <exception>
#include "AutoGame2.h"
//State modification methods
AutoGame2::AutoBoard::AutoBoard(int y, int x)
{
    height = y;
    width = x;
    board = std::vector<std::vector<enum board_elements>>(height);
    for (int i = 0; i < height; i++) {
        board.at(i) = std::vector<enum board_elements>(width);
        for (int j = 0; j < width; j++) {
            board.at(i).at(j) = EMPTY;
        }
    }

    for (int i = 0; i < width; i++) {
        board.at(0).at(i) = WALL;
        board.at(height - 1).at(i) = WALL;
    }

    for (int i = 0; i < height; i++) {
        board.at(i).at(0) = WALL;
        board.at(i).at(width - 1) = WALL;
    }

    snake = std::deque<struct point *>();
    snake.push_back(new point(height / 2, width / 2));
    board.at(snake.front->y).at(snake.front->x) = HEAD;
    board.at(10).at(10) = APPLE;
}
enum AutoGame2::AutoBoard::board_elements at(int y, int x)
{
    return board.at(y).at(x);
}
void AutoGame2::AutoBoard::set_dir(enum board_dir)
{
    /*TODO*/
}
void AutoGame2::AutoBoard::update()
{
    /*TODO*/
}
void AutoGame2::AutoBoard::place_apple()
{
    /*TODO*/
}
int AutoGame2::AutoBoard::get_snake_length()
{
    /*TODO*/
}
bool AutoGame2::AutoBoard::is_apple_placed()
{
    /*TODO*/
}

AutoGame2::AutoGame2()
{
    state = GAME_STATE_INIT;
    board = new AutoBoard;
}
void AutoGame2::init()
{
    state = GAME_STATE_INIT;
}
void AutoGame2::play()
{
    state = GAME_STATE_PLAY;
}
void AutoGame2::pause()
{
    state = GAME_STATE_PAUSE;
}
void AutoGame2::over()
{
    state = GAME_STATE_OVER;
}
enum game_state AutoGame2::update()
{
    /*TODO*/
}
bool AutoGame2::place_apple(int, int)
{
    /*TODO*/
}
//State report methods
enum game_state AutoGame2::get_state()
{
    /*TODO*/
}
enum board_elements AutoGame2::board_data(int y, int x)
{
    return board->at(y, x);
}
enum board_dir AutoGame2::get_direction()
{
    /*TODO*/
}
int AutoGame2::player_score()
{
    /*TODO*/
}
bool AutoGame2::is_apple_placed()
{
    /*TODO*/
}
//Unnecessary methods
void AutoGame2::key_event(enum key_press)
{
    return;
}
std::vector<std::pair<int, int>> *AutoGame2::export_snake()
{
    std::terminate();
}
int AutoGame2::export_dir()
{
    std::terminate();
}
int **AutoGame2::export_board()
{
    std::terminate();
}
void AutoGame2::load(int **, std::vector<std::pair<int, int>> *, int)
{
    std::terminate();
}
std::pair<int, int> AutoGame2::get_head_pos(enum PlayerSelect)
{
    std::terminate();
}
board_dir AutoGame2::get_direction(enum PlayerSelect)
{
    std::terminate();
}
