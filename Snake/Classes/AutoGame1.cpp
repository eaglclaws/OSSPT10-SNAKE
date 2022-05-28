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
#include "AutoGame.h"
#include "Board.h"

using namespace std;

AutoGame::AutoGame()
{
    state = AutoGame_STATE_INIT;
    board = new Board;
}

AutoGame::~AutoGame()
{
    delete board;
}

void AutoGame::init()
{
    state = AutoGame_STATE_INIT;
    board->init();
}

void AutoGame::play()
{
    state = AutoGame_STATE_PLAY;
}

void AutoGame::pause()
{
    state = AutoGame_STATE_PAUSE;
}

void AutoGame::over()
{
    state = AutoGame_STATE_OVER;
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

enum AutoGame_state AutoGame::update()
{
    bool board_live = board->update();
    if (!board_live) {
        over();
        return state;
    }
    else {
        return state;
    }
}

bool AutoGame::place_apple(int x, int y)
{
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
Game::autoplay_by_direction(enum board_dir dir) {

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
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if (board->get_snake_head().first == board->get_apple_pos().first) {
                if (board->get_snake_head().second >= 40) {
                    if (board->get_snake_head().first <= 20) {
                        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                            break;
                        }
                        board->set_direction((board_dir)((dir + 1) % 4));
                        break;
                    }
                    else {
                        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                            break;
                        }
                        board->set_direction((board_dir)((dir + 3) % 4));
                        break;
                    }
                }
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        else {
            if (board->get_snake_head().first < board->get_apple_pos().first) {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if (board->get_snake_head().first == board->get_apple_pos().first) {
                if (board->get_snake_head().first >= 40) {
                    if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                        break;
                    }
                    board->set_direction((board_dir)((dir + 3) % 4));
                    break;
                }
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 3) % 4));
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
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if (board->get_snake_head().second == board->get_apple_pos().second) {
                if (board->get_snake_head().first >= 40) {
                    if (board->get_snake_head().second > 20) {
                        if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction((board_dir)((dir + 1) % 4));
                        break;
                    }
                    else {
                        if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction((board_dir)((dir + 3) % 4));
                        break;
                    }
                }
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        else {
            if (board->get_snake_head().second > board->get_apple_pos().second) {
                if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if (board->get_snake_head().second == board->get_apple_pos().second) {
                if (board->get_snake_head().first >= 40) {
                    if (board->get_snake_head().second <= 1) {
                        if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction((board_dir)((dir + 3) % 4));
                        break;
                    }
                    if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                        break;
                    }
                    board->set_direction((board_dir)((dir + 1) % 4));
                    break;
                }
            }
            else {
                if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 3) % 4));
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
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if (board->get_snake_head().first == board->get_apple_pos().first) {
                if (board->get_snake_head().second <= 1) {
                    if (board->get_snake_head().first > 20) {
                        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                            break;
                        }
                        board->set_direction((board_dir)((dir + 1) % 4));
                        break;
                    }
                    else {
                        if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                            break;
                        }
                        board->set_direction((board_dir)((dir + 3) % 4));
                        break;
                    }
                }
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        else {
            if (board->get_snake_head().first > board->get_apple_pos().first) {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if (board->get_snake_head().first == board->get_apple_pos().first) {
                if (board->get_snake_head().first <= 1) {
                    if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                        break;
                    }
                    board->set_direction((board_dir)((dir + 3) % 4));
                    break;
                }
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first - 1) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == SNAKE || board->data()->at(board->get_snake_head().second).at(board->get_snake_head().first + 1) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 3) % 4));
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
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if (board->get_snake_head().second == board->get_apple_pos().second) {
                if (board->get_snake_head().first <= 1) {
                    if (board->get_snake_head().second <= 20) {
                        if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction((board_dir)((dir + 1) % 4));
                        break;
                    }
                    else {
                        if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                            break;
                        }
                        board->set_direction((board_dir)((dir + 3) % 4));
                        break;
                    }
                }
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        else {
            if (board->get_snake_head().second < board->get_apple_pos().second) {
                if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if (board->get_snake_head().second == board->get_apple_pos().second) {
                if (board->get_snake_head().second >= 40) {
                    if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                        break;
                    }
                    board->set_direction((board_dir)((dir + 3) % 4));
                    break;
                }
                if (board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second + 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else {
                if (board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == SNAKE || board->data()->at(board->get_snake_head().second - 1).at(board->get_snake_head().first) == TAIL) {
                    break;
                }
                board->set_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        break;
    }
}

void
Game::auto_play()
{
    autoplay_by_direction(board->get_direction());
}