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
#include <array>
#include <vector>
#include <utility>
#include "Game.h"
#include "AutoGame1.h"
#include "Board.h"
#include <chrono>
#include <random>

using namespace std;

AutoGame::AutoGame()
{
    state = GAME_STATE_INIT;
    board = new Board;
}

AutoGame::~AutoGame()
{
    delete board;
}

void AutoGame::init()
{
    state = GAME_STATE_INIT;
    board->init();
}

void AutoGame::play()
{
    state = GAME_STATE_PLAY;
}

void AutoGame::pause()
{
    state = GAME_STATE_PAUSE;
}

void AutoGame::over()
{
    state = GAME_STATE_OVER;
}

enum game_state AutoGame::get_state()
{
    return state;
}

enum board_elements AutoGame::board_data(int x, int y)
{
    return board->data()->at(y).at(x);
}

enum board_dir AutoGame::get_direction()
{
    return board->get_direction();
}

enum game_state AutoGame::update()
{
    bool board_live = board->update();
    if (!board_live) {
        over();
        return state;
    }
    else {
        auto_play();
        return state;
    }
}

bool AutoGame::place_apple()
{
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937* rng = new std::mt19937(seed1);

    int x = (*rng)() % 40 + 1, y = (*rng)() % 40 + 1;

    if (board->data()->at(y).at(x) != EMPTY) {
        return false;
    }
    else {
        board->data()->at(y).at(x) = APPLE;
        board->set_apple_pos(x, y);
        board->apple_placed();
        return true;
    }
}

bool AutoGame::is_apple_placed()
{
    return board->is_apple_placed();
}

int AutoGame::player_score()
{
    return board->get_length();
}

//부딪히기 직전 몸의 이전노드의 방향의 반대로 이동
void
AutoGame::autoplay_by_direction(enum board_dir dir) {

    int xinc = 0, yinc = 0;
    switch (dir) {
    case UP:
        yinc = 1;
        break;
    case DOWN:
        yinc = -1;
        break;
    case LEFT:
        xinc = -1;
        break;
    case RIGHT:
        xinc = 1;
        break;
    }

    if (xinc != 0 && board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + xinc) == WALL) {
        if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
            board->set_direction(DOWN);
            return;
        }
        else if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
            board->set_direction(UP);
            return;
        }
    }
    if (yinc != 0 && board->data()->at(board->get_snake_head().second + yinc).at(board->get_snake_head().first) == WALL) {
        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
            board->set_direction(LEFT);
            return;
        }
        else if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
            board->set_direction(RIGHT);
            return;
        }
    }
    int checksnake = 0;

    if (board->data()->at(board->get_snake_head().second + yinc).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + yinc).at(board->get_snake_head().first) == TAIL) {
        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
            board->set_direction(LEFT);
            return;
        }
        else if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
            board->set_direction(RIGHT);
            return;
        }
        if (yinc > 0) {
            checksnake -= 1;
            while (board->data()->at(board->get_snake_head().second + checksnake).at(board->get_snake_head().first) == SNAKE) {
                checksnake -= 1;
            }
            if (board->data()->at(board->get_snake_head().second + checksnake + 1).at(board->get_snake_head().first + 1) == SNAKE) {
                board->set_direction(LEFT);
                return;
            }
            else {
                board->set_direction(RIGHT);
                return;
            }
        }
        if (yinc < 0) {
            checksnake += 1;
            while (board->data()->at(board->get_snake_head().second + checksnake).at(board->get_snake_head().first) == SNAKE) {
                checksnake += 1;
            }
            if (board->data()->at(board->get_snake_head().second + checksnake - 1).at(board->get_snake_head().first + 1) == SNAKE) {
                board->set_direction(LEFT);
                return;
            }
            else {
                board->set_direction(RIGHT);
                return;
            }
        }
    }
    if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + xinc) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + xinc) == TAIL) {
        if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
            board->set_direction(DOWN);
            return;
        }
        else if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
            board->set_direction(UP);
            return;
        }
        if (xinc > 0) {
            checksnake -= 1;
            while (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + checksnake) == SNAKE) {
                checksnake -= 1;
            }
            if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first + checksnake + 1) == SNAKE) {
                board->set_direction(DOWN);
                return;
            }
            else {
                board->set_direction(UP);
                return;
            }
        }
        if (xinc < 0) {
            checksnake += 1;
            while (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + checksnake) == SNAKE) {
                checksnake += 1;
            }
            if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first + checksnake - 1) == SNAKE) {
                board->set_direction(DOWN);
                return;
            }
            else {
                board->set_direction(UP);
                return;
            }
        }
    }

    switch (dir) {
    case UP:
        if (board->get_snake_head().second < board->get_apple_pos().second) {
            break;
        }
        else if (board->get_snake_head().second == board->get_apple_pos().second) {
            if (board->get_snake_head().first < board->get_apple_pos().first) {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                    break;
                }
                board->set_direction(RIGHT);
                break;
            }
            else if (board->get_snake_head().first == board->get_apple_pos().first) {
                if (board->get_snake_head().second >= 40) {
                    if (board->get_snake_head().first <= 20) {
                        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                            break;
                        }
                        board->set_direction(RIGHT);
                        break;
                    }
                    else {
                        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                            break;
                        }
                        board->set_direction(LEFT);
                        break;
                    }
                }
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                    break;
                }
                board->set_direction(LEFT);
                break;
            }
        }
        else {
            if (board->get_snake_head().first < board->get_apple_pos().first) {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                    break;
                }
                board->set_direction(RIGHT);
                break;
            }
            else if (board->get_snake_head().first == board->get_apple_pos().first) {
                if (board->get_snake_head().first >= 40) {
                    if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                        break;
                    }
                    board->set_direction(LEFT);
                    break;
                }
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                    break;
                }
                board->set_direction(RIGHT);
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                    break;
                }
                board->set_direction(LEFT);
                break;
            }
        }
        break;

    case RIGHT:
        if (board->get_snake_head().first < board->get_apple_pos().first) {
            break;
        }
        else if (board->get_snake_head().first == board->get_apple_pos().first) {
            if (board->get_snake_head().second > board->get_apple_pos().second) {
                if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction(DOWN);
                break;
            }
            else if (board->get_snake_head().second == board->get_apple_pos().second) {
                if (board->get_snake_head().first >= 40) {
                    if (board->get_snake_head().second > 20) {
                        if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction(DOWN);
                        break;
                    }
                    else {
                        if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction(UP);
                        break;
                    }
                }
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction(UP);
                break;
            }
        }
        else {
            if (board->get_snake_head().second > board->get_apple_pos().second) {
                if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction(DOWN);
                break;
            }
            else if (board->get_snake_head().second == board->get_apple_pos().second) {
                if (board->get_snake_head().first >= 40) {
                    if (board->get_snake_head().second <= 1) {
                        if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction(UP);
                        break;
                    }
                    if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                        break;
                    }
                    board->set_direction(DOWN);
                    break;
                }
            }
            else {
                if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction(UP);
                break;
            }
        }
        break;

    case DOWN:
        if (board->get_snake_head().second > board->get_apple_pos().second) {
            break;
        }
        else if (board->get_snake_head().second == board->get_apple_pos().second) {
            if (board->get_snake_head().first > board->get_apple_pos().first) {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                    break;
                }
                board->set_direction(LEFT);
                break;
            }
            else if (board->get_snake_head().first == board->get_apple_pos().first) {
                if (board->get_snake_head().second <= 1) {
                    if (board->get_snake_head().first > 20) {
                        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                            break;
                        }
                        board->set_direction(LEFT);
                        break;
                    }
                    else {
                        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                            break;
                        }
                        board->set_direction(RIGHT);
                        break;
                    }
                }
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                    break;
                }
                board->set_direction(RIGHT);
                break;
            }
        }
        else {
            if (board->get_snake_head().first > board->get_apple_pos().first) {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                    break;
                }
                board->set_direction(LEFT);
                break;
            }
            else if (board->get_snake_head().first == board->get_apple_pos().first) {
                if (board->get_snake_head().first <= 1) {
                    if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                        break;
                    }
                    board->set_direction(RIGHT);
                    break;
                }
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                    break;
                }
                board->set_direction(LEFT);
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                    break;
                }
                board->set_direction(RIGHT);
                break;
            }
        }
        break;

    case LEFT:
        if (board->get_snake_head().first > board->get_apple_pos().first) {
            break;
        }
        else if (board->get_snake_head().first == board->get_apple_pos().first) {
            if (board->get_snake_head().second < board->get_apple_pos().second) {
                if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction(UP);
                break;
            }
            else if (board->get_snake_head().second == board->get_apple_pos().second) {
                if (board->get_snake_head().first <= 1) {
                    if (board->get_snake_head().second <= 20) {
                        if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction(UP);
                        break;
                    }
                    else {
                        if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction(DOWN);
                        break;
                    }
                }
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction(DOWN);
                break;
            }
        }
        else {
            if (board->get_snake_head().second < board->get_apple_pos().second) {
                if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction(UP);
                break;
            }
            else if (board->get_snake_head().second == board->get_apple_pos().second) {
                if (board->get_snake_head().second >= 40) {
                    if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                        break;
                    }
                    board->set_direction(DOWN);
                    break;
                }
                if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction(UP);
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction(DOWN);
                break;
            }
        }
        break;
    }
}

std::pair<int, int> AutoGame::get_head_pos(enum PlayerSelect player) {
    return board->get_snake_head();
}

void AutoGame::key_event(enum key_press)
{
    return;
}

int AutoGame::get_board_height()
{
    return board->get_height();
}

int AutoGame::get_board_width() 
{
    return board->get_width();
}
void AutoGame::key_event(enum key_press, enum PlayerSelect)
{
    return;
}

void AutoGame::load(int**, std::vector<std::pair<int, int>>*, int)
{
    return;
}

std::vector<std::pair<int, int>>* AutoGame::export_snake() 
{
    return nullptr;
}

int AutoGame::export_dir() 
{
    return 0;
}

int** AutoGame::export_board()
{
    return nullptr;
}
void AutoGame::auto_play()
{
    autoplay_by_direction(board->get_direction());
}

board_dir AutoGame::get_direction(enum PlayerSelect player) {
    if (player == PLAYER1)
        return board->get_direction();
    return NONE_DIR;
}

enum PlayerSelect AutoGame::get_winner() {
    return NONE;
}
