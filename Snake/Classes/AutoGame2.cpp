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

#include <cstdlib>
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
    snake.push_back(new point(snake.front->x, snake.front->y - 1));
    board.at(snake.front->y).at(snake.front->x) = HEAD;
    place_apple();
}
enum AutoGame2::AutoBoard::board_elements at(int y, int x)
{
    return board.at(y).at(x);
}
void AutoGame2::AutoBoard::set_dir(enum board_dir dir)
{
    current_dir = dir;
}
enum board_dir AutoGame2::AutoBoard::get_dir()
{
    return current_dir;
}
bool AutoGame2::AutoBoard::update()
{
    int xinc, yinc;
    switch (current_dir) {
    case UP:
        xinc = 0;
        yinc = 1;
    case DOWN:
        xinc = 0;
        yinc = -1;
    case LEFT:
        xinc = -1;
        yinc = 0;
    case RIGHT:
        xinc = 1;
        yinc = 0;
    }
    int next_head_x = snake.front->x + xinc;
    int next_head_y = snake.front->y + yinc;
    if (board.at(next_head_y).at(next_head_x) == SNAKE ||
            board.at(next_head_y).at(next_head_x) == WALL ||
            board.at(next_head_y).at(next_head_x) == TAIL) {
        return false;
    }
    board.at(snake.front->y).at(snake.front->x) = SNAKE;
    snake.push_front(new point(next_head_x, next_head_y));
    if (board.at(snake.front->y).at(snake.front->x) == APPLE) {
        snake_length++;
        board.at(snake.front->y).at(snake.front->x) = HEAD;
        apple_placed = false;
        return true;
    }
    board.at(snake.back->y).at(snake.back->x) = EMPTY;
    snake.pop_back();
    board.at(snake.back-y).at(snake.back->x) = TAIL;
}
bool AutoGame2::AutoBoard::place_apple()
{
    int y = std::rand() % height;
    int x = std::rand() % width;
    if (board.at(y).at(x) != EMPTY) {
        return false;
    } else {
        board.at(y).at(x) = APPLE;
        set_apple(y, x);
        return true;
    }
}
void AutoGame2::AutoBoard::set_apple(int y, int x)
{
    apple_placed = true;
    apple_x = x;
    apple_y = y;
}
int AutoGame2::AutoBoard::get_snake_length()
{
    return snake_length;
}
bool AutoGame2::AutoBoard::is_apple_placed()
{
    return apple_placed;
}

AutoGame2::AutoGame2(int y, int x)
{
    state = GAME_STATE_INIT;
    graph = std::vector<std::vector<int>>(y * x);
    for (int i = 0; i < y * x; i++) graph.at(i) = std::vector<int>(y * x);
    for (int i = 0; i < y * x; i++) {
        for (int j = 0; j < y * x; j++) {
            graph.at(i).at(j) = 0;
        }
    }
    board = new AutoBoard(y, x);
    for (int i = 0; i < y * x; i++) {
        int board_y = i / x;
        int board_x = i % x;
        if (board.at(board_y).at(board_x) == WALL) continue;
        int id_r = board_y       * x + board_x + 1;
        int id_l = board_y       * x + board_x - 1;
        int id_u = (board_y - 1) * x + board_x;
        int id_d = (board_y + 1) * x + board_x;

        bool xunder = board_x - 1 < 0;
        bool xover = board_x + 1 >= x;
        bool yunder = board_y - 1 < 0;
        bool yover = board_y + 1 >= y;   
        if (!xover) {
            if (board.at(board_y).at(board_x + 1) == EMPTY) {
                graph.at(id).at(id_r) = 1;
            } else {
                graph.at(id).at(id_r) = 0;
            }
        }
        if (!xunder) {
            if (board.at(board_y).at(board_x - 1) == EMPTY) {
                graph.at(id).at(id_l) = 1;
            } else {
                graph.at(id).at(id_l) = 0;
            }
        }
        if (!yover) {
            if (board.at(board_y + 1).at(board_x) == EMPTY) {
                graph.at(id_d).at(id) = 1;
            } else {
                graph.at(id_d).at(id) = 0;
            }
        }
        if (!yunder) {
            if (board.at(board_y - 1).at(board_x) == EMPTY) {
                graph.at(id_u).at(id) = 1;
            } else {
                graph.at(id_u).at(id) = 0;
            }
        }
    }
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
    switch (board->get_dir) {
    case UP:
    case DOWN:
        board->set_dir(RIGHT);
        break;
    case LEFT:
        board->set_dir(UP);
        break;
    case RIGHT:
        board->set_dir(DOWN);
        break;
    }
    if(!board->update()) {
        over();
        return GAME_STATE_OVER;
    } else {
        return GAME_STATE_PLAY;
    }
}
bool AutoGame2::place_apple(int x, int y)
{
    return board->place_apple();
}
//State report methods
enum game_state AutoGame2::get_state()
{
    return state;
}
enum board_elements AutoGame2::board_data(int x, int y)
{
    return board->at(y, x);
}
enum board_dir AutoGame2::get_direction()
{
    return board->get_dir();
}
int AutoGame2::player_score()
{
    return board->get_snake_length();
}
bool AutoGame2::is_apple_placed()
{
    return board->is_apple_place();
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
