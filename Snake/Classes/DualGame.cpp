#include <array>
#include <vector>
#include <utility>
#include "Game.h"
#include "DualBoard.h"
#include "DualGame.h"
#include <chrono>
#include <random>

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
    return board->get_direction(PLAYER1);
}

int** DualGame::export_board() {
    int** tmp;
    return tmp;
}
int DualGame::player_score() {
    //In DualGame does not use. score is not calculated.
    return 0;
}
int DualGame::export_dir() {
    return 1;
}
std::vector<std::pair<int, int>>* DualGame::export_snake() {
    std::vector<std::pair<int, int>>* tmp;

    return tmp;
}

enum game_state DualGame::update()
{
    bool board_live = board->update();
    if (!board_live) {
        over();
        winner = board->get_winner();
        return state;
    }
    else {
        return state;
    }
}

bool DualGame::place_apple() {
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937* rng = new std::mt19937(seed1);

    int x = (*rng)() % 80 + 1, y = (*rng)() % 40 + 1;
    int x1, y1;

    if (board->get_apple_amount() == 1) {
        if (board->data()->at(y).at(x) != EMPTY) {
            return false;
        }
        else {
            board->data()->at(y).at(x) = APPLE;
            board->apple_placed();
            return true;
        }
    }
    else if (board->get_apple_amount() == 0) {
        x1 = (*rng)() % 80 + 1;
        y1 = (*rng)() % 40 + 1;
        if (board->data()->at(y).at(x) != EMPTY) {
            return false;
        }
        else {
            board->data()->at(y).at(x) = APPLE;
        }

        while (x == x1 && y == y1) {
            x1 = (*rng)() % 80 + 1;
            y1 = (*rng)() % 40 + 1;
        }
        if (board->data()->at(y1).at(x1) != EMPTY) {
            return false;
        }
        else {
            board->data()->at(y1).at(x1) = APPLE;
            board->apple_placed();
            return true;
        }
    }
}

//bool DualGame::place_apple()
//{
//    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
//    std::mt19937*rng = new std::mt19937(seed1);
//
//    int x1 = (*rng)() % 40 + 1, y1 = (*rng)() % 40 + 1, x2, y2;
//
//    if (board->get_apple_amount() == 1) {
//        while (1) {
//            if (board->data()->at(y1).at(x1) == APPLE) {
//                x1 = (*rng)() % 40 + 1;
//                y1 = (*rng)() % 40 + 1;
//                continue;
//            }
//            else {
//                board->data()->at(y1).at(x1) = APPLE;
//                board->apple_placed();
//                return true;
//            }
//        }
//    }
//    else if (board->get_apple_amount() == 0) {
//        board->data()->at(y1).at(x1) = APPLE;
//        x2 = (*rng)() % 40 + 1;
//        y2 = (*rng)() % 40 + 1;
//
//        while (1) {
//            if (x2 == x1 && y2 == y1) {
//                x2 = (*rng)() % 40 + 1;
//                y2 = (*rng)() % 40 + 1;
//                continue;
//            }
//            else {
//                board->data()->at(y2).at(x2) = APPLE;
//                board->apple_placed();
//                return true;
//            }   
//        }
//    }
//    return true;
//}

bool DualGame::is_apple_placed()
{
    return board->is_apple_placed();
}

int DualGame::get_board_height()
{
    return board->get_height();
}

int DualGame::get_board_width()
{
    return board->get_width();
}

void DualGame::key_event(enum key_press ekey) {
    switch (ekey)
    {
    case KEY_UP:
        break;
    case KEY_DOWN:
        break;
    case KEY_LEFT:
        break;
    case KEY_RIGHT:
        break;
    case KEY_W:
        break;
    case KEY_A:
        break;
    case KEY_S:
        break;
    case KEY_D:
        break;
    case KEY_ESC:
        pause();
        break;
    default:
        break;
    }
}

void DualGame::load(int**, std::vector<std::pair<int, int>>*, int) {

}

void DualGame::key_event(enum key_press ekey, enum PlayerSelect player)
{
    switch (ekey) {
    case KEY_UP:
        board->set_direction(UP, player);
        break;
    case KEY_DOWN:
        board->set_direction(DOWN, player);
        break;
    case KEY_LEFT:
        board->set_direction(LEFT, player);
        break;
    case KEY_RIGHT:
        board->set_direction(RIGHT, player);
        break;
    case KEY_W:
        board->set_direction(UP, player);
        break;
    case KEY_S:
        board->set_direction(DOWN, player);
        break;
    case KEY_A:
        board->set_direction(LEFT, player);
        break;
    case KEY_D:
        board->set_direction(RIGHT, player);
        break;

    case KEY_ESC:
        pause();
        break;
    }
}

std::pair<int, int> DualGame::get_head_pos(enum PlayerSelect player) {
    return board->get_snake_head(player);
}

enum board_dir DualGame::get_direction(enum PlayerSelect player) {
    return board->get_direction(player);
}

enum PlayerSelect DualGame::get_winner() {
    return winner;
}