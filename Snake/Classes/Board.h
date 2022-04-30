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

#ifndef __BOARD_H__
#define __BOARD_H__
#include <array>

#define BOARD_WIDTH 42
#define BOARD_HEIGHT 42

class Snake;

enum board_elements
{
    EMPTY,
    WALL,
    HEAD,
    SNAKE,
    APPLE
};

enum board_dir
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Board
{
private:
    std::array<std::array<board_elements, BOARD_WIDTH>, BOARD_HEIGHT> *board_data;
    int headx;
    int heady;

    int tailx;
    int taily;
    enum board_dir current;
public:
    Board();

    std::array<std::array<board_elements, BOARD_WIDTH>, BOARD_HEIGHT> *
    data();

    bool
    update(enum board_dir);

    bool
    update();

    void
    set_direction(enum board_dir);
    
    bool
    place_apple(int, int);
};

#endif