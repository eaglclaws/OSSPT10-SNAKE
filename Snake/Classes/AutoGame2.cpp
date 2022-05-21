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

#include <exception>
#include "AutoGame2.h"
//State modification methods
void AutoGame2::init()
{
    state = GAME_STATE_INIT;
}
void AutoGame2::play()
{
    state = GAME_STATE_PLAY;
}
void AutoGame2::pause()
{
    state = GAME_STATE_PAUSE;
}
void AutoGame2::over()
{
    state = GAME_STATE_OVER;
}
enum game_state AutoGame2::update() {/*TODO*/}
bool AutoGame2::place_apple(int, int) {/*TODO*/}
//State report methods
enum game_state AutoGame2::get_state() {/*TODO*/}
enum board_elements AutoGame2::board_data(int, int) {/*TODO*/}
enum board_dir AutoGame2::get_direction() {/*TODO*/}
int AutoGame2::player_score() {/*TODO*/}
bool AutoGame2::is_apple_placed() {/*TODO*/}
//Unnecessary methods
void AutoGame2::key_event(enum key_press)
{
    std::terminate();
}
std::vector<std::pair<int, int>> *AutoGame2::export_snake()
{
    std::terminate();
}
int AutoGame2::export_dir()
{
    std::terminate();
}
int **AutoGame2::export_board()
{
    std::terminate();
}
void AutoGame2::load(int **, std::vector<std::pair<int, int>> *, int)
{
    std::terminate();
}
std::pair<int, int> AutoGame2::get_head_pos(enum PlayerSelect)
{
    std::terminate();
}
board_dir AutoGame2::get_direction(enum PlayerSelect)
{
    std::terminate();
}
