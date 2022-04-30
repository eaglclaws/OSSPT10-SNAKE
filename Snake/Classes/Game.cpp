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

#include "Game.h"
#include "Board.h"

Game::Game()
{
    state = GAME_STATE_INIT;
    board = new Board;
}

Game::~Game()
{
    delete board;
}

void
Game::init()
{
    state = GAME_STATE_INIT;
    board->init();
}

void
Game::play()
{
    state = GAME_STATE_PLAY;
}

void
Game::pause()
{
    state = GAME_STATE_PAUSE;
}

void
Game::over()
{
    state = GAME_STATE_OVER;
}

enum game_state
Game::get_state()
{
    return state;
}

enum board_elements
Game::board_data(int x, int y)
{
    return board->data()->at(y).at(x);
}

enum board_dir
Game::get_direction()
{
    return board->get_direction();
}

enum game_state
Game::update()
{
    bool board_live = board->update();
    if (!board_live) {
        over();
        return state;
    } else {
        return state;
    }
}

bool
Game::place_apple(int x, int y)
{
    if (board->data()->at(y).at(x) != EMPTY) {
        return false;
    } else {
        board->data()->at(y).at(x) = APPLE;
        return true;
    }
}

void
Game::key_event(enum key_press ekey)
{
    switch (ekey) {
    case KEY_UP:
        board->set_direction(UP);
        break;
    case KEY_DOWN:
        board->set_direction(DOWN);
        break;
    case KEY_LEFT:
        board->set_direction(LEFT);
        break;
    case KEY_RIGHT:
        board->set_direction(RIGHT);
        break;
    case KEY_ESC:
        pause();
        break;
    }
}