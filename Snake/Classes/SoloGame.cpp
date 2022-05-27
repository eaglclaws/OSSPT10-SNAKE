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
#include <utility>
#include "Game.h"
#include "Board.h"
#include "SoloGame.h"
#include <chrono>
#include <random>

SoloGame::SoloGame()
{
    state = GAME_STATE_INIT;
    board = new Board;
}

SoloGame::~SoloGame()
{
    delete board;
}

void SoloGame::init()
{
    state = GAME_STATE_INIT;
    board->init();
}

void SoloGame::play()
{
    state = GAME_STATE_PLAY;
}

void SoloGame::pause()
{
    state = GAME_STATE_PAUSE;
}

void SoloGame::over()
{
    state = GAME_STATE_OVER;
}

enum game_state SoloGame::get_state()
{
    return state;
}

enum board_elements SoloGame::board_data(int x, int y)
{
    return board->data()->at(y).at(x);
}

enum board_dir SoloGame::get_direction()
{
    return board->get_direction();
}

enum game_state SoloGame::update()
{
    bool board_live = board->update();
    if (!board_live) {
        over();
        return state;
    } else {
        return state;
    }
}


//bool SoloGame::place_apple(int x, int y)
//{
//    if (board->data()->at(y).at(x) != EMPTY) {
//        return false;
//    } else {
//        board->data()->at(y).at(x) = APPLE;
//        board->set_apple_pos(x, y); //apple 위치 저장
//        board->apple_placed();
//        return true;
//    }
//}

bool SoloGame::is_apple_placed()
{
    return board->is_apple_placed();
}

void SoloGame::key_event(enum key_press ekey)
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

int **SoloGame::export_board()
{
    return board->export_board();
}

std::vector<std::pair<int, int>> *SoloGame::export_snake()
{
    return board->export_snake();
}

int SoloGame::export_dir()
{
    return board->export_dir();
}

int SoloGame::player_score()
{
    return board->get_length();
}

void SoloGame::load(int **board_save, std::vector<std::pair<int, int>> *snake_save, int dir_save)
{
    board->load(board_save, snake_save, dir_save);
}

//new
bool SoloGame::place_apple() {
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937* rng = new std::mt19937(seed1);

    int x = (*rng)() % 40 + 1, y = (*rng)() % 40 + 1;

    if (board->data()->at(y).at(x) != EMPTY) {
        return false;
    }
    else {
        board->data()->at(y).at(x) = APPLE;
        board->set_apple_pos(x, y);
        board->apple_placed();
        return true;
    }
}

std::pair<int, int> SoloGame::get_head_pos(enum PlayerSelect player) {
    return board->get_snake_head();
}
int SoloGame::get_board_height() {
    return board->get_height();
}
int SoloGame::get_board_width() {
    return board->get_width();
}
void SoloGame::key_event(enum key_press ekey, enum PlayerSelect player) {
    if (player != PLAYER1)
        return;

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
board_dir SoloGame::get_direction(enum PlayerSelect player) {
    if (player == PLAYER1)
        return board->get_direction();
    return NONE_DIR;
}

enum PlayerSelect SoloGame::get_winner() {
    return NONE;
}

