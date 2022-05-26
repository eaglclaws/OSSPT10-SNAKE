#include <array>
#include <vector>
#include "DualBoard.h"

using namespace std;

DualBoard::DualBoard()
{
    apple_amount = 0;
    board_data = new std::array<std::array<board_elements, DUALBOARD_WIDTH>, DUALBOARD_HEIGHT>;
    init();
}

DualBoard::~DualBoard()
{
    struct snake_node* cur = (*tail);
    while (cur->next != nullptr) {
        struct snake_node* temp = cur->next;
        delete cur;
        cur = temp;
    }
    cur = (*sec_tail);
    while (cur->next != nullptr) {
        struct snake_node* temp = cur->next;
        delete cur;
        cur = temp;
    }

    delete cur;
    delete tail;
    delete head;
    delete sec_tail;
    delete sec_head;
}

std::array<std::array<board_elements, DUALBOARD_WIDTH>, DUALBOARD_HEIGHT>*
DualBoard::data()
{
    return board_data;
}

void
DualBoard::set_direction(enum board_dir dir)
{
    current = dir;
}

enum board_dir
    DualBoard::get_direction()
{
    return current;
}

void
DualBoard::init()
{
    head = new struct snake_node*;
    tail = new struct snake_node*;
    (*head) = new struct snake_node;
    (*head)->next = nullptr;
    (*tail) = new struct snake_node;
    (*tail)->next = (*head);
    (*head)->y = DUALBOARD_HEIGHT - 3;
    (*head)->x = 1;
    (*tail)->y = (*head)->y + 1;
    (*tail)->x = (*head)->x;
    length = 0;
    current = DOWN;

    sec_head = new struct snake_node*;
    sec_tail = new struct snake_node*;
    (*sec_head) = new struct snake_node;
    (*sec_head)->next = nullptr;
    (*sec_tail) = new struct snake_node;
    (*sec_tail)->next = (*sec_head);
    (*sec_head)->y = 4;
    (*sec_head)->x = DUALBOARD_WIDTH - 2;
    (*sec_tail)->y = (*sec_head)->y - 1;
    (*sec_tail)->x = (*sec_head)->x;
    sec_length = 0;
    sec_current = UP;

    winner == NONE;

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
        board_data->at(DUALBOARD_HEIGHT - 1).at(i) = WALL;
    }
    board_data->at((*head)->y).at((*head)->x) = HEAD;
    board_data->at((*tail)->y).at((*tail)->x) = TAIL;

    board_data->at((*sec_head)->y).at((*sec_head)->x) = HEAD;
    board_data->at((*sec_tail)->y).at((*sec_tail)->x) = TAIL;

    apple_amount = 0;
}

bool
DualBoard::update()
{
    bool p1 = update(current, PLAYER1);
    bool p2 = update(sec_current, PLAYER2);
    return (p1 && p2);
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
    board_data->at((*head)->y).at((*head)->x) = SNAKE;
    struct snake_node* temp = new struct snake_node;
    int headx = (*head)->x + xinc;
    int heady = (*head)->y + yinc;
    enum board_elements front = board_data->at(heady).at(headx);
    if (
        board_data->at(heady).at(headx) == SNAKE ||
        board_data->at(heady).at(headx) == WALL ||
        board_data->at(heady).at(headx) == TAIL
        ) return false;
    temp->x = headx;
    temp->y = heady;
    temp->next = nullptr;
    (*head)->next = temp;
    (*head) = temp;
    board_data->at(heady).at(headx) = HEAD;

    if (front == APPLE) {
        length++;
        apple_amount--;
        apple_removed();
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
DualBoard::get_length()
{
    return length;
}

int**
DualBoard::export_board()
{
    int** temp = new int* [DUALBOARD_WIDTH];
    for (int i = 0; i < DUALBOARD_WIDTH; i++) temp[i] = new int[DUALBOARD_HEIGHT];
    for (int y = 0; y < DUALBOARD_HEIGHT; y++) {
        for (int x = 0; x < DUALBOARD_WIDTH; x++) {
            temp[y][x] = (int)board_data->at(y).at(x);
        }
    }
    return temp;
}

std::vector<std::pair<int, int>>*
DualBoard::export_snake()
{
    std::vector<std::pair<int, int>>* temp = new std::vector<std::pair<int, int>>;
    struct snake_node* cur = (*tail);
    while (cur != nullptr) {
        std::pair<int, int> ele(cur->x, cur->y);
        temp->push_back(ele);
        cur = cur->next;
    }
    return temp;
}

int
DualBoard::export_dir()
{
    return (int)current;
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

void
DualBoard::apple_placed()
{
    apple_amount = 2;
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

std::pair<int, int>
DualBoard::get_apple_pos()
{
    return apple_pos;
}

void
DualBoard::set_apple_pos(int x, int y)
{
    apple_pos = make_pair(x, y);
}

std::pair<int, int>
DualBoard::get_snake_head() {
    return std::pair<int, int>((*head)->x, (*head)->y);
}

std::pair<int, int>
DualBoard::get_snake_head(enum PlayerSelect player) {
    switch (player)
    {
    case PLAYER1:
        return std::pair<int, int>((*head)->x, (*head)->y);
        break;
    case PLAYER2:
        return std::pair<int, int>((*sec_head)->x, (*sec_head)->y);
        break;
    case NONE:
        break;
    default:
        break;
    }
}

void
DualBoard::set_direction(enum board_dir dir, enum PlayerSelect player) {
    switch (player)
    {
    case PLAYER1:
        current = dir;
        break;
    case PLAYER2:
        sec_current = dir;
        break;
    case NONE:
        break;
    default:
        break;
    }
}

enum board_dir
DualBoard::get_direction(enum PlayerSelect player) {
    switch (player)
    {
    case PLAYER1:
        return current;
        break;
    case PLAYER2:
        return sec_current;
        break;
    case NONE:
        break;
    default:
        break;
    }
}

bool
DualBoard::update(enum board_dir dir, enum PlayerSelect player) {
    int xinc = 0, yinc = 0;
    struct snake_node* temp = new struct snake_node;
    int headx = 0, heady = 0;
    enum board_elements front;

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
    switch (player)
    {
    case PLAYER1:
        board_data->at((*head)->y).at((*head)->x) = SNAKE;
        headx = (*head)->x + xinc;
        heady = (*head)->y + yinc;

        break;
    case PLAYER2:
        board_data->at((*sec_head)->y).at((*sec_head)->x) = SNAKE;
        headx = (*sec_head)->x + xinc;
        heady = (*sec_head)->y + yinc;

        break;
    case NONE:
        break;
    default:
        break;
    }
   
    front = board_data->at(heady).at(headx);
    if (
        board_data->at(heady).at(headx) == SNAKE ||
        board_data->at(heady).at(headx) == WALL ||
        board_data->at(heady).at(headx) == TAIL
        ) {
        if (winner != NONE)
            winner = NONE;
        else if (player == PLAYER1)
            winner = PLAYER2;
        else if (player == PLAYER2)
            winner = PLAYER1;
        return false;
    }
    board_data->at(heady).at(headx) = HEAD;
    temp->x = headx;
    temp->y = heady;
    temp->next = nullptr;

    switch (player)
    {
    case PLAYER1:
        (*head)->next = temp;
        (*head) = temp;

        if (front == APPLE) {
            length++;
            apple_amount--;
            apple_removed();
            return true;
        }


        board_data->at((*tail)->y).at((*tail)->x) = EMPTY;
        temp = (*tail)->next;
        (*tail)->next = nullptr;
        delete (*tail);
        (*tail) = temp; if ((*tail) == (*head)) return true;
        board_data->at((*tail)->y).at((*tail)->x) = TAIL;
        break;
    case PLAYER2:
        (*sec_head)->next = temp;
        (*sec_head) = temp;

        if (front == APPLE) {
            sec_length++;
            apple_amount--;
            apple_removed();
            return true;
        }


        board_data->at((*sec_tail)->y).at((*sec_tail)->x) = EMPTY;
        temp = (*sec_tail)->next;
        (*sec_tail)->next = nullptr;
        delete (*sec_tail);
        (*sec_tail) = temp; if ((*sec_tail) == (*sec_head)) return true;
        board_data->at((*sec_tail)->y).at((*sec_tail)->x) = TAIL;

        break;
    case NONE:
        break;
    default:
        break;
    }
    
    return true;
}

int 
DualBoard::get_apple_amount() {
    return apple_amount;
}
