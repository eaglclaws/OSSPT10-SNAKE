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
    board = new Board;
}

Game::~Game()
{
    delete board;
}

enum board_elements
Game::board_data(int x, int y)
{
    return board->data()->at(y).at(x);
}

bool
Game::update()
{
    return board->update();
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
        break;
    }
}