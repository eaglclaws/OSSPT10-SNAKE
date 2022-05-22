/*
Copyright 2022 ����

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
#include "AutoGame.h"
#include "Board.h"

using namespace std;

AutoGame::AutoGame()
{
    state = AutoGame_STATE_INIT;
    board = new Board;
}

AutoGame::~AutoGame()
{
    delete board;
}

void AutoGame:: init()
{
    state = AutoGame_STATE_INIT;
    board->init();
}

void AutoGame::play()
{
    state = AutoGame_STATE_PLAY;
}

void AutoGame::pause()
{
    state = AutoGame_STATE_PAUSE;
}

void AutoGame::over()
{
    state = AutoGame_STATE_OVER;
}

enum game_state AutoGame::get_state()
{
    return state;
}

enum board_elements AutoGame::board_data(int x, int y)
{
    return board->data()->at(y).at(x);
}

enum board_dir AutoGame::get_direction()
{
    return board->get_direction();
}

enum AutoGame_state AutoGame::update()
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

bool AutoGame::place_apple(int x, int y)
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

bool AutoGame::is_apple_placed()
{
    return board->is_apple_placed();
}

int AutoGame::player_score()
{
    return board->get_length();
}

//�˰��� �ϼ� �Ŀ� �Լ��� ���´� ������ �� ����.
void AutoGame::auto_play()
{
    //put algorithm here
    switch (board->get_direction()) {
    case UP:
        if (*(board->head)->y < board->get_apple_pos().second) {
            if (*(board->head)->x < board->get_apple_pos().first)
                board->set_direction(RIGHT);
            else if (*(board->head)->x == board->get_apple_pos().first)
            else
                board->set_direction(LEFT);
        }
        else if (*(board->head)->y == board->get_apple_pos().second) {
            if (*(board->head)->x < board->get_apple_pos().first)
                board->set_direction(RIGHT);
            else
                board->set_direction(LEFT);
        }
        else {
            if (*(board->head)->x < board->get_apple_pos().first) {
                board->set_direction(RIGHT);
                board->set_direction(RIGHT);
            }
            else if (*(board->head)->x == board->get_apple_pos().first) {
                board->set_direction(RIGHT);
                board->set_direction(RIGHT);//��ĭ ���� �ٷ�
                board->set_direction(RIGHT);
            }
            else {
                board->set_direction(LEFT);
                board->set_direction(LEFT);
            }
        }
    }

}