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
#include "Board.h"

Board::Board()
{
    board_data = new std::array<std::array<board_elements, BOARD_WIDTH>, BOARD_HEIGHT>;
    heady = (int)BOARD_HEIGHT/2;
    headx = (int)BOARD_WIDTH/2;
    taily = heady;
    tailx = headx;
    current = UP;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board_data->at(y).at(x) = EMPTY;
        }
    }

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        board_data->at(i).at(0) = WALL;
        board_data->at(i).at(BOARD_WIDTH - 1) = WALL;
    }

    for (int i = 0; i < BOARD_WIDTH; i++) {
        board_data->at(0).at(i) = WALL;
        board_data->at(BOARD_HEIGHT - 1).at(i) = WALL;
    }
    board_data->at(heady).at(headx) = HEAD;
}

std::array<std::array<board_elements, BOARD_WIDTH>, BOARD_HEIGHT> *
Board::data()
{
    return board_data;
}

void
Board::set_direction(enum board_dir dir)
{
    current = dir;
}


bool
Board::update()
{
    return update(current);
}

bool
Board::update(enum board_dir dir)
{
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
    board_data->at(heady).at(headx) = SNAKE;
    headx += xinc;
    heady += yinc;
    if (board_data->at(heady).at(headx) != EMPTY) return false;
    board_data->at(heady).at(headx) = HEAD;
    return true;
}