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
#include "Board.h"

Board::Board()
{
    board_data = new std::array<std::array<board_elements, BOARD_WIDTH>, BOARD_HEIGHT>;
    init();
}

Board::~Board()
{
    struct snake_node *cur = (*tail);
    while (cur->next != nullptr) {
        struct snake_node *temp = cur->next;
        delete cur;
        cur = temp;
    }
    delete cur;
    delete tail;
    delete head;
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

enum board_dir
Board::get_direction()
{
    return current;
}

void
Board::init()
{
    head = new struct snake_node *;
    tail = new struct snake_node *;
    (*head) = new struct snake_node;
    (*head)->next = nullptr;
    (*tail) = new struct snake_node;
    (*tail)->next = (*head);
    (*head)->y = (int)BOARD_HEIGHT/2;
    (*head)->x = (int)BOARD_WIDTH/2;
    (*tail)->y = (*head)->y - 1;
    (*tail)->x = (*head)->x;
    length = 2;
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
    board_data->at((*head)->y).at((*head)->x) = HEAD;
    board_data->at((*tail)->y).at((*tail)->x) = TAIL;
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
    board_data->at((*head)->y).at((*head)->x) = SNAKE;
    struct snake_node *temp = new struct snake_node;
    int headx = (*head)->x + xinc;
    int heady = (*head)->y + yinc;
    enum board_elements front = board_data->at(heady).at(headx);
    if (
        board_data->at(heady).at(headx) == SNAKE ||
        board_data->at(heady).at(headx) == WALL ||
        board_data->at(heady).at(headx) == TAIL    
    ) return false;
    temp->x = (*head)->x + xinc;
    temp->y = (*head)->y + yinc;
    temp->next = nullptr;
    (*head)->next = temp;
    (*head) = temp;
    board_data->at(heady).at(headx) = HEAD;

    if (front == APPLE) {
        length++;
        return true;
    }
    board_data->at((*tail)->y).at((*tail)->x) = EMPTY;
    temp = (*tail)->next;
    (*tail)->next = nullptr;
    delete (*tail);
    (*tail) = temp; if ((*tail) == (*head)) return true;
    board_data->at((*tail)->y).at((*tail)->x) = TAIL;
    return true;
}

int
Board::get_length()
{
    return length;
}

int **
Board::export_board()
{
    int **temp = new int *[BOARD_WIDTH];
    for (int i = 0; i < BOARD_WIDTH; i++) temp[i] = new int[BOARD_HEIGHT];
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            temp[y][x] = (int)board_data->at(y).at(x);
        }
    }
    return temp;
}

std::vector<std::pair<int, int>> *
Board::export_snake()
{
    std::vector<std::pair<int, int>> *temp = new std::vector<std::pair<int, int>>;
    struct snake_node *cur = (*tail);
    while(cur != nullptr) {
        std::pair<int, int> ele(cur->x, cur->y);
        temp->push_back(ele);
        cur = cur->next;
    }
    return temp;
}

int
Board::export_dir()
{
    return (int)current;
}

void
Board::load(int **board_save, std::vector<std::pair<int, int>> *snake_save, int dir_save)
{
    printf("AT LEAST IN THE FUNCTION\n");
    int load_length = 0;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            enum board_elements temp;
            int sw = board_save[y][x];
            if (sw == 0) {
                temp = EMPTY;
            } else if (sw == 1) {
                temp = WALL;
            } else if (sw == 2) {
                temp = HEAD;
            } else if (sw == 3) {
                temp = SNAKE;
            } else if (sw == 4) {
                temp = TAIL;
            } else if (sw == 5) {
                temp = APPLE;
            }
            board_data->at(y).at(x) = temp;
        }
    }
    printf("SEGFAULT GUARD\n");
    struct snake_node *load_snake = new struct snake_node;
    struct snake_node *cur = load_snake;
    for (std::vector<std::pair<int, int>>::iterator it = snake_save->begin(); it != snake_save->end(); it++) {
        load_length++;
        cur->x = it->first;
        cur->y = it->second;
        cur->next = nullptr;
        if (it + 1 == snake_save->end()) continue; 
        cur->next = new struct snake_node;
        cur = cur->next;
    }
    (*tail) = load_snake;
    (*head) = cur;
    if (cur == nullptr) (*head) = (*tail);

    switch (dir_save) {
    case 0:
        current = UP;
        break;
    case 1:
        current = DOWN;
        break;
    case 2:
        current = LEFT;
        break;
    case 3:
        current = RIGHT;
        break;
    }
}
