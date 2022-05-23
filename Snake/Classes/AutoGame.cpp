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

void AutoGame:: init()
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

void
Game::autoplay_by_direction(enum board_dir dir) {
    switch (dir) {
    case UP:
        if ((*(board->get_head()))->y < board->get_apple_pos().second) {
            //autoplay_by_direction(dir);
            break;
        }
        else if ((*(board->get_head()))->y == board->get_apple_pos().second) {
            if ((*(board->get_head()))->x < board->get_apple_pos().first) {
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if ((*(board->get_head()))->x == board->get_apple_pos().first) {
                if ((*(board->get_head()))->y >= 40) {
                    if ((*(board->get_head()))->x <= 20) {
                        board->set_direction((board_dir)((dir + 1) % 4));
                        break;
                    }
                    else {
                        board->set_direction((board_dir)((dir + 3) % 4));
                        break;
                    }
                }
                break;
            }
            else {
                board->set_direction((board_dir)((dir + 3) % 4));
                //board->set_direction(DOWN);
                break;
            }
        }
        else {
            if ((*(board->get_head()))->x < board->get_apple_pos().first) {
                board->set_direction((board_dir)((dir + 1) % 4));
                //autoplay_by_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if ((*(board->get_head()))->x == board->get_apple_pos().first) {
                if ((*(board->get_head()))->x >= 40) {
                    board->set_direction((board_dir)((dir + 3) % 4));
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                //autoplay_by_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else {
                board->set_direction((board_dir)((dir + 3) % 4));
                //board->set_direction(UP);
                //autoplay_by_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        break;

    case RIGHT:
        if ((*(board->get_head()))->x < board->get_apple_pos().first) {
            //autoplay_by_direction(dir);
            break;
        }
        else if ((*(board->get_head()))->x == board->get_apple_pos().first) {
            if ((*(board->get_head()))->y > board->get_apple_pos().second) {
                board->set_direction((board_dir)((dir + 1) % 4));
                //board->set_direction(UP);
                break;
            }
            else if ((*(board->get_head()))->y == board->get_apple_pos().second) {
                if ((*(board->get_head()))->y > 20) {
                    board->set_direction((board_dir)((dir + 1) % 4));
                    break;
                }
                else {
                    board->set_direction((board_dir)((dir + 3) % 4));
                    break;
                }
                break;
            }
            else {
                board->set_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        else {
            if ((*(board->get_head()))->y > board->get_apple_pos().second) {
                board->set_direction((board_dir)((dir + 1) % 4));
                //board->set_direction(DOWN);
                //autoplay_by_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if ((*(board->get_head()))->y == board->get_apple_pos().second) {
                if ((*(board->get_head()))->x >= 40) {
                    if ((*(board->get_head()))->y <= 1) {
                        board->set_direction((board_dir)((dir + 3) % 4));
                        break;
                    }
                    board->set_direction((board_dir)((dir + 1) % 4));
                    //board->set_direction(DOWN);
                    //autoplay_by_direction((board_dir)((dir + 1) % 4));
                    break;
                }
            }
            else {
                board->set_direction((board_dir)((dir + 3) % 4));
                //autoplay_by_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        break;

    case DOWN:
        if ((*(board->get_head()))->y > board->get_apple_pos().second) {
            //autoplay_by_direction(dir);
            //board->set_direction(UP);
            break;
        }
        else if ((*(board->get_head()))->y == board->get_apple_pos().second) {
            if ((*(board->get_head()))->x > board->get_apple_pos().first) {
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if ((*(board->get_head()))->x == board->get_apple_pos().first) {
                if ((*(board->get_head()))->y <= 1) {
                    if ((*(board->get_head()))->x > 20) {
                        board->set_direction((board_dir)((dir + 1) % 4));
                        break;
                    }
                    else {
                        board->set_direction((board_dir)((dir + 3) % 4));
                        break;
                    }
                }
                break;
            }
            else {
                board->set_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        else {
            if ((*(board->get_head()))->x > board->get_apple_pos().first) {
                board->set_direction((board_dir)((dir + 1) % 4));
                //autoplay_by_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if ((*(board->get_head()))->x == board->get_apple_pos().first) {
                if ((*(board->get_head()))->x <= 1) {
                    board->set_direction((board_dir)((dir + 3) % 4));
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                //autoplay_by_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else {
                board->set_direction((board_dir)((dir + 3) % 4));
                //autoplay_by_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        break;

    case LEFT:
        if ((*(board->get_head()))->x > board->get_apple_pos().first) {
            //autoplay_by_direction(dir);
            //board->set_direction(UP);
            break;
        }
        else if ((*(board->get_head()))->x == board->get_apple_pos().first) {
            if ((*(board->get_head()))->y < board->get_apple_pos().second) {
                board->set_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if ((*(board->get_head()))->y == board->get_apple_pos().second) {
                if ((*(board->get_head()))->x <= 1) {
                    if ((*(board->get_head()))->y <= 20) {
                        board->set_direction((board_dir)((dir + 1) % 4));
                        break;
                    }
                    else {
                        board->set_direction((board_dir)((dir + 3) % 4));
                        break;
                    }
                }
                break;
            }
            else {
                board->set_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        else {
            if ((*(board->get_head()))->y < board->get_apple_pos().second) {
                board->set_direction((board_dir)((dir + 1) % 4));
                //autoplay_by_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else if ((*(board->get_head()))->y == board->get_apple_pos().second) {
                if ((*(board->get_head()))->y >= 40) {
                    board->set_direction((board_dir)((dir + 3) % 4));
                    break;
                }
                board->set_direction((board_dir)((dir + 1) % 4));
                //autoplay_by_direction((board_dir)((dir + 1) % 4));
                break;
            }
            else {
                board->set_direction((board_dir)((dir + 3) % 4));
                //autoplay_by_direction((board_dir)((dir + 3) % 4));
                break;
            }
        }
        break;
    }

    //if ((*(board->get_head()))->y < board->get_apple_pos().second) {
    //    autoplay_by_direction(dir);
    //}
    //else if ((*(board->get_head()))->y == board->get_apple_pos().second) {
    //    if ((*(board->get_head()))->x < board->get_apple_pos().first)
    //        board->set_direction((board_dir)((dir + 1) % 4));
    //    else
    //        board->set_direction((board_dir) ((dir + 3) % 4));
    //}
    //else {
    //    if ((*(board->get_head()))->x < board->get_apple_pos().first) {
    //        board->set_direction((board_dir)((dir + 1) % 4));
    //        autoplay_by_direction((board_dir)((dir + 1) % 4));
    //    }
    //    else if ((*(board->get_head()))->x == board->get_apple_pos().first) {
    //        board->set_direction((board_dir)((dir + 1) % 4));
    //        autoplay_by_direction((board_dir)((dir + 1) % 4));
    //    }
    //    else {
    //        board->set_direction((board_dir)((dir + 3) % 4));
    //        autoplay_by_direction((board_dir)((dir + 3) % 4));
    //    }
    //}

    //switch (dir) {
    //case UP:
    //    if ((*(board->get_head()))->y < board->get_apple_pos().second) {
    //        if ((*(board->get_head()))->x < board->get_apple_pos().first)
    //            board->set_direction(RIGHT);
    //        else if ((*(board->get_head()))->x == board->get_apple_pos().first)
    //        else
    //            board->set_direction(LEFT);
    //    }
    //    else if ((*(board->get_head()))->y == board->get_apple_pos().second) {
    //        if ((*(board->get_head()))->x < board->get_apple_pos().first)
    //            board->set_direction(RIGHT);
    //        else
    //            board->set_direction(LEFT);
    //    }
    //    else {
    //        if ((*(board->get_head()))->x < board->get_apple_pos().first) {
    //            board->set_direction(RIGHT);
    //            board->set_direction(RIGHT);
    //        }
    //        else if ((*(board->get_head()))->x == board->get_apple_pos().first) {
    //            board->set_direction(RIGHT);
    //            board->set_direction(RIGHT);//한칸 가고 바로
    //            board->set_direction(RIGHT);
    //        }
    //        else {
    //            board->set_direction(LEFT);
    //            board->set_direction(LEFT);
    //        }
    //    }
    //}
}

void
Game::auto_play()
{
    autoplay_by_direction(board->get_direction());
}