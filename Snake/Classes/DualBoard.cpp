#include <array>
#include <vector>
#include "DualBoard.h"

DualBoard::DualBoard()
{
    board_data = new std::array<std::array<board_elements, DUALBOARD_WIDTH>, DUALBOARD_HEIGHT>;
    init();
}

DualBoard::~DualBoard()
{
    struct snake_node* cur1 = (*tail_player_one);
    struct snake_node* cur2 = (*tail_player_two);

    while (cur1->next != nullptr) {
        struct snake_node* temp = cur1->next;
        delete cur1;
        cur1 = temp;
    }

    while (cur2->next != nullptr) {
        struct snake_node* temp = cur2->next;
        delete cur2;
        cur2 = temp;
    }

    delete cur1;
    delete cur2;
    delete tail_player_one;
    delete tail_player_two;
    delete head_player_one;
    delete head_player_two;
}

std::array<std::array<board_elements, DUALBOARD_WIDTH>, DUALBOARD_HEIGHT>*
DualBoard::data()
{
    return board_data;
}


//set_direction_player_one & player_two
void
DualBoard::set_direction(enum board_dir dir)
{
    current = dir;
}

// maybe remove? confirm 
enum board_dir
    DualBoard::get_direction()
{
    return current;
}

void
DualBoard::init()
{
    head_player_one = new struct snake_node*;
    tail_player_one = new struct snake_node*;
    (*head_player_one) = new struct snake_node;
    (*head_player_one)->next = nullptr;
    (*tail_player_one) = new struct snake_node;
    (*tail_player_one)->next = (*head_player_one);
    (*head_player_one)->y = (int)DUALBOARD_HEIGHT / 2;
    (*head_player_one)->x = (int)DUALBOARD_WIDTH / 2;
    (*tail_player_one)->y = (*head_player_one)->y - 1;
    (*tail_player_one)->x = (*head_player_one)->x;
    length = 0;
    current_player_one = UP;
    for (int y = 0; y < DUALBOARD_HEIGHT; y++) {
        for (int x = 0; x < DUALBOARD_WIDTH; x++) {
            board_data->at(y).at(x) = EMPTY;
        }
    }

    for (int i = 0; i < DUALBOARD_HEIGHT; i++) {
        board_data->at(i).at(0) = WALL;
        board_data->at(i).at(DUALBOARD_WIDTH - 1) = WALL;
    }

    for (int i = 0; i < DUALBOARD_WIDTH; i++) {
        board_data->at(0).at(i) = WALL;
        board_data->at(DUALBOARD_WIDTH - 1).at(i) = WALL;
    }
    board_data->at((*head_player_one)->y).at((*head_player_one)->x) = HEAD;
    board_data->at((*tail_player_one)->y).at((*tail_player_one)->x) = TAIL;
}


//to check is snake is alive?
bool
DualBoard::update()
{
    return update(current);
}

bool
DualBoard::update(enum board_dir dir)
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

    board_data->at((*head_player_one)->y).at((*head_player_one)->x) = SNAKE;
    struct snake_node* temp = new struct snake_node;
    int headx = (*head_player_one)->x + xinc;
    int heady = (*head_player_one)->y + yinc;
    enum board_elements front = board_data->at(heady).at(headx);
    if (
        board_data->at(heady).at(headx) == SNAKE ||
        board_data->at(heady).at(headx) == WALL ||
        board_data->at(heady).at(headx) == TAIL
        ) return false;
    temp->x = (*head_player_one)->x + xinc;
    temp->y = (*head_player_one)->y + yinc;
    temp->next = nullptr;
    (*head_player_one)->next = temp;
    (*head_player_one) = temp;
    board_data->at(heady).at(headx) = HEAD;

    if (front == APPLE) {
        length++;
        apple_removed();
        return true;
    }
    board_data->at((*tail_player_one)->y).at((*tail_player_one)->x) = EMPTY;
    temp = (*tail_player_one)->next;
    (*tail_player_one)->next = nullptr;
    delete (*tail_player_one);
    (*tail_player_one) = temp; if ((*tail_player_one) == (*head_player_one)) return true;
    board_data->at((*tail_player_one)->y).at((*tail_player_one)->x) = TAIL;
    return true;
}

int
DualBoard::get_length()
{
    return length;
}

void
DualBoard::load(int** board_save, std::vector<std::pair<int, int>>* snake_save, int dir_save)
{
    has_apple = false;
    int load_length = -2;
    for (int y = 0; y < DUALBOARD_HEIGHT; y++) {
        for (int x = 0; x < DUALBOARD_WIDTH; x++) {
            enum board_elements temp;
            int sw = board_save[y][x];
            if (sw == 0) {
                temp = EMPTY;
            }
            else if (sw == 1) {
                temp = WALL;
            }
            else if (sw == 2) {
                temp = HEAD;
            }
            else if (sw == 3) {
                temp = SNAKE;
            }
            else if (sw == 4) {
                temp = TAIL;
            }
            else if (sw == 5) {
                temp = APPLE;
                has_apple = true;
            }
            board_data->at(y).at(x) = temp;
        }
    }
    struct snake_node* load_snake = new struct snake_node;
    struct snake_node* cur = load_snake;
    for (std::vector<std::pair<int, int>>::iterator it = snake_save->begin(); it != snake_save->end(); it++) {
        load_length++;
        cur->x = it->first;
        cur->y = it->second;
        cur->next = nullptr;
        if (it + 1 == snake_save->end()) continue;
        cur->next = new struct snake_node;
        cur = cur->next;
    }
    length = load_length;
    (*tail_player_one) = load_snake;
    (*head_player_one) = cur;
    if (cur == nullptr) (*head_player_one) = (*tail_player_one);

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

void
DualBoard::apple_placed()
{
    has_apple = true;
}

void
DualBoard::apple_removed()
{
    has_apple = false;
}

bool
DualBoard::is_apple_placed()
{
    return has_apple;
}
