#include <array>
#include <vector>
#include <utility>
#include "Game.h"
#include "DualBoard.h"
#include "DualGame.h"

DualGame::DualGame()
{
    state = GAME_STATE_INIT;
    board = new DualBoard;
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

bool DualGame::place_apple()
{
   /* if (board->data()->at(y).at(x) != EMPTY) {
        return false;
    }
    else {
        board->data()->at(y).at(x) = APPLE;
        board->apple_placed();
        return true;
    }*/
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

int DualGame::player_score()
{
    return board->get_length();
}

void DualGame::load(int** board_save, std::vector<std::pair<int, int>>* snake_save, int dir_save)
{
    board->load(board_save, snake_save, dir_save);
}

int DualGame::get_board_height()
{
    return board->getBoardHeight();
}

int DualGame::get_board_width()
{
    return board->getBoardWidth();
}


void DualGame::key_event(enum key_press ekey, enum PlayerSelect player)
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
    case KEY_W:
        board->set_direction(UP);
        break;
    case KEY_A:
        board->set_direction(DOWN);
        break;
    case KEY_S:
        board->set_direction(LEFT);
        break;
    case KEY_D:
        board->set_direction(RIGHT);
        break;

    case KEY_ESC:
        pause();
        break;
    }
}

std::pair<int, int> DualGame::get_head_pos(enum PlayerSelect player) {
    return board->get_snake_head(player);
}