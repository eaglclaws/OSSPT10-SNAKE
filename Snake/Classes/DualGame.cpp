#include <array>
#include <vector>
#include <utility>
#include "Game.h"
#include "Board.h"
#include "DualGame.h"

DualGame::DualGame()
{
    state = GAME_STATE_INIT;
    board = new Board;
}

DualGame::~DualGame()
{
    delete board;
}

void DualGame::init()
{
    state = GAME_STATE_INIT;
    board->init();
}

void DualGame::play()
{
    state = GAME_STATE_PLAY;
}

void DualGame::pause()
{
    state = GAME_STATE_PAUSE;
}

void DualGame::over()
{
    state = GAME_STATE_OVER;
}

enum game_state DualGame::get_state()
{
    return state;
}

enum board_elements DualGame::board_data(int x, int y)
{
    return board->data()->at(y).at(x);
}

enum board_dir DualGame::get_direction()
{
    return board->get_direction();
}

enum game_state DualGame::update()
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

bool DualGame::place_apple(int x, int y)
{
    if (board->data()->at(y).at(x) != EMPTY) {
        return false;
    }
    else {
        board->data()->at(y).at(x) = APPLE;
        board->apple_placed();
        return true;
    }
}

bool DualGame::is_apple_placed()
{
    return board->is_apple_placed();
}

void DualGame::key_event(enum key_press ekey)
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

int** DualGame::export_board()
{
    return board->export_board();
}

std::vector<std::pair<int, int>>* DualGame::export_snake()
{
    return board->export_snake();
}

int DualGame::export_dir()
{
    return board->export_dir();
}

int DualGame::player_score()
{
    return board->get_length();
}

void DualGame::load(int** board_save, std::vector<std::pair<int, int>>* snake_save, int dir_save)
{
    board->load(board_save, snake_save, dir_save);
}
