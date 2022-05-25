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
#include <vector>
#include <utility>
#include "EnumList.h"
#define BOARD_WIDTH 42
#define BOARD_HEIGHT 42

class Snake;

class Board
{
private:
    std::array<std::array<board_elements, BOARD_WIDTH>, BOARD_HEIGHT> *board_data;
    struct snake_node **head;
    struct snake_node **tail;
    int length;
    enum board_dir current;
    bool has_apple;
    std::pair<int, int> apple_pos;
public:
    Board();
    ~Board();

    void
    init();

    std::array<std::array<board_elements, BOARD_WIDTH>, BOARD_HEIGHT> *
    data();

    bool
    update(enum board_dir);

    bool
    update();

    void
    set_direction(enum board_dir);

    enum board_dir
    get_direction();

    bool
    place_apple(int, int);

    int
    get_length();
    
    int **
    export_board();
    
    std::vector<std::pair<int, int>> *
    export_snake();
    
    int
    export_dir();

    void
    load(int **, std::vector<std::pair<int, int>> *, int);
    
    void
    apple_placed();

    void
    apple_removed();

    bool
    is_apple_placed();

    std::pair<int, int>
    get_apple_pos();

    void
    set_apple_pos(int, int);

    int
    get_width() { return BOARD_HEIGHT; }

    int
    get_height() { return BOARD_WIDTH; }

    std::pair<int, int> 
    get_snake_head();
};

#endif
