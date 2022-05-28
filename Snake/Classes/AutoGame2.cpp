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

#include <cstdlib>
#include <exception>
#include "AutoGame2.h"
#include "EnumList.h"
//State modification methods
AutoGame2::AutoBoard::AutoBoard(int y, int x)
{
    height = y;
    width = x;
    apple_placed = false;
    board = std::vector<std::vector<enum board_elements>>(height);
    for (int i = 0; i < height; i++) {
        board.at(i) = std::vector<enum board_elements>(width);
        for (int j = 0; j < width; j++) {
            board.at(i).at(j) = EMPTY;
        }
    }

    for (int i = 0; i < width; i++) {
        board.at(0).at(i) = WALL;
        board.at(height - 1).at(i) = WALL;
    }

    for (int i = 0; i < height; i++) {
        board.at(i).at(0) = WALL;
        board.at(i).at(width - 1) = WALL;
    }

    snake = std::deque<struct point *>();
    snake.push_back(new point(height / 2, width / 2));
    snake.push_back(new point(snake.front()->y - 1, snake.front()->x));
    board.at(snake.front()->y).at(snake.front()->x) = HEAD;
    board.at(snake.back()->y).at(snake.back()->x) = TAIL;
    head_x = snake.front()->x;
    head_y = snake.front()->y;
    set_dir(UP);
}
enum board_elements AutoGame2::AutoBoard::at(int y, int x)
{
    return board.at(y).at(x);
}
void AutoGame2::AutoBoard::set_dir(enum board_dir dir)
{
    current_dir = dir;
}
enum board_dir AutoGame2::AutoBoard::get_dir()
{
    return current_dir;
}
int AutoGame2::AutoBoard::get_head_x()
{
    return head_x;
}
int AutoGame2::AutoBoard::get_head_y()
{
    return head_y;
}
int AutoGame2::AutoBoard::get_apple_x()
{
    return apple_x;
}
int AutoGame2::AutoBoard::get_apple_y()
{
    return apple_y;
}
bool AutoGame2::AutoBoard::update()
{
    int xinc, yinc;
    switch (current_dir) {
    case UP:
        xinc = 0;
        yinc = 1;
        break;
    case DOWN:
        xinc = 0;
        yinc = -1;
        break;
    case LEFT:
        xinc = -1;
        yinc = 0;
        break;
    case RIGHT:
        xinc = 1;
        yinc = 0;
        break;
    case NONE_DIR:
        break;
    }
    int next_head_x = snake.front()->x + xinc;
    int next_head_y = snake.front()->y + yinc;
    if (board.at(next_head_y).at(next_head_x) == SNAKE ||
            board.at(next_head_y).at(next_head_x) == WALL ||
            board.at(next_head_y).at(next_head_x) == TAIL) {
        return false;
    }
    board.at(snake.front()->y).at(snake.front()->x) = SNAKE;
    snake.push_front(new point(next_head_y, next_head_x));
    head_x = snake.front()->x;
    head_y = snake.front()->y;
    if (board.at(snake.front()->y).at(snake.front()->x) == APPLE) {
        board.at(snake.front()->y).at(snake.front()->x) = HEAD;
        snake_length++;
        apple_placed = false;
        return true;
    }
    board.at(snake.front()->y).at(snake.front()->x) = HEAD;
    board.at(snake.back()->y).at(snake.back()->x) = EMPTY;
    snake.pop_back();
    board.at(snake.back()->y).at(snake.back()->x) = TAIL;
    return true;
}
bool AutoGame2::AutoBoard::place_apple()
{
    if (apple_placed) return false;
    int y = 10; //std::rand() % height;
    int x = 10; //std::rand() % width;
    if (board.at(y).at(x) != EMPTY) {
        return false;
    } else {
        board.at(y).at(x) = APPLE;
        set_apple(y, x);
        return true;
    }
}
void AutoGame2::AutoBoard::set_apple(int y, int x)
{
    apple_placed = true;
    apple_x = x;
    apple_y = y;
}
int AutoGame2::AutoBoard::get_snake_length()
{
    return snake_length;
}
bool AutoGame2::AutoBoard::is_apple_placed()
{
    return apple_placed;
}
int AutoGame2::AutoBoard::get_width()
{
    return width;
}
int AutoGame2::AutoBoard::get_height()
{
    return height;
}

AutoGame2::AutoGame2(int y, int x)
{
    state = GAME_STATE_INIT;
    graph = std::vector<std::vector<int>>(y * x);
    for (int i = 0; i < y * x; i++) graph.at(i) = std::vector<int>(y * x);
    for (int i = 0; i < y * x; i++) {
        for (int j = 0; j < y * x; j++) {
            graph.at(i).at(j) = 0;
        }
    }
    board = new AutoBoard(y, x);
    scan_graph();
    dist = std::vector<int>(y * x);
    prev = std::vector<int>(y * x);
    Q = std::vector<int>(y * x);
    for (int i = 0; i < y * x; i++) {
        dist.at(i) = y * x;
        prev.at(i) = -1;
        Q.at(i) = 1;
    }
}
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
enum game_state AutoGame2::update()
{
    int y = board->get_head_y();
    int x = board->get_head_x();
    scan_graph();
    enum board_dir next = next_dir(board->get_apple_y(), board->get_apple_x(),
            board->get_head_y(), board->get_head_x());
    if (next == NONE_DIR) {
        switch (board->get_dir()) {
        case UP:
            if (y - 1 >= 0 && board->at(y - 1, x) == EMPTY) {
                next = UP;
            } else if (x - 1 >= 0 && board->at(y, x - 1) == EMPTY) {
                next = LEFT;
            } else if (x + 1 < board->get_width() && board->at(y, x + 1) == EMPTY) {
                next = RIGHT;
            } else {
                next = UP;
            }
            break;
        case DOWN:
            if (y + 1 < board->get_height() && board->at(y + 1, x) == EMPTY) {
                next = DOWN;
            } else if (x - 1 >= 0 && board->at(y, x - 1) == EMPTY) {
                next = LEFT;
            } else if (x + 1 < board->get_width() && board->at(y, x + 1) == EMPTY) {
                next = RIGHT;
            } else {
                next = DOWN;
            }
            break;
        case LEFT:
            if (y - 1 >= 0 && board->at(y - 1, x) == EMPTY) {
                next = UP;
            } else if (y + 1 < board->get_height() && board->at(y + 1, x) == EMPTY) {
                next = DOWN;
            } else if (x - 1 < board->get_width() && board->at(y, x - 1) == EMPTY) {
                next = LEFT;
            } else {
                next = LEFT;
            }
            break;
        case RIGHT:
            if (y - 1 >= 0 && board->at(y - 1, x) == EMPTY) {
                next = UP;
            } else if (y + 1 < board->get_height() && board->at(y + 1, x) == EMPTY) {
                next = DOWN;
            } else if (x + 1 >= 0 && board->at(y, x + 1) == EMPTY) {
                next = RIGHT;
            } else {
                next = RIGHT;
            }
            break;
        }
    }
    board->set_dir(next);
    bool failed = !board->update();
    if(failed) {
        over();
        return GAME_STATE_OVER;
    } else {
        return GAME_STATE_PLAY;
    }
}
bool AutoGame2::place_apple()
{
    return board->place_apple();
}
//State report methods
enum game_state AutoGame2::get_state()
{
    return state;
}
enum board_elements AutoGame2::board_data(int x, int y)
{
    return board->at(y, x);
}
enum board_dir AutoGame2::get_direction()
{
    return board->get_dir();
}
int AutoGame2::player_score()
{
    return board->get_snake_length();
}
bool AutoGame2::is_apple_placed()
{
    return board->is_apple_placed();
}
//Unnecessary methods
void AutoGame2::key_event(enum key_press)
{
    return;
}
std::vector<std::pair<int, int>> *AutoGame2::export_snake()
{
    return nullptr;
}
int AutoGame2::export_dir()
{
    return -1;
}
int **AutoGame2::export_board()
{
    return nullptr;
}
void AutoGame2::load(int **, std::vector<std::pair<int, int>> *, int)
{
    return;
}
std::pair<int, int> AutoGame2::get_head_pos(enum PlayerSelect)
{
    return std::pair<int, int>(board->get_head_x(), board->get_head_y());
}
board_dir AutoGame2::get_direction(enum PlayerSelect)
{
    return board->get_dir();
}
int AutoGame2::get_board_height()
{
    return board->get_height();
}
int AutoGame2::get_board_width()
{
    return board->get_width();
}
void AutoGame2::key_event(enum key_press, enum PlayerSelect)
{
    return;
}
enum PlayerSelect AutoGame2::get_winner()
{
    return PLAYER1;
}

enum board_dir AutoGame2::next_dir(int dy, int dx, int sy, int sx)
{
    board_dir dir;
    int y = board->get_height();
    int x = board->get_width();
    int src = sy * board->get_width() + sx;
    int des = dy * board->get_width() + dx;
    for (int i = 0; i < y * x; i++) {
        dist.at(i) = y * x + 1;
        prev.at(i) = -1;
        Q.at(i) = 1;
    }
    dist.at(src) = 0;
    
    int u;
    int v;
    int dist_min;
    int alt;
    for (int k = 0; k < y * x + 2; k++) {
        dist_min = y * x + 1;
        for (int i = 0; i < y * x; i++) {
            if (dist.at(i) < dist_min) {
                dist_min = dist.at(i);
                u = i;
            }
        }
        Q.at(u) = 0;
        if (u == des) break;
        for (int i = 0; i < y * x; i++) {
            if (graph.at(u).at(i) == 1 && Q.at(i) == 1) {
                v = i;
                //printf("%d -> %d\n", u, v);
                alt = dist.at(u) + 1;
                if (alt < dist.at(v)) {
                    dist.at(v) = alt;
                    prev.at(v) = u;
                }
            }
        }
        dist_min = y * x + 1;
        //printf("\n\n");
    }
    if (prev.at(des) == -1) {
        return NONE_DIR;
    } else {
        int next_node;
        int cur_node = des;
        while (prev.at(cur_node) != src) {
            next_node = prev.at(cur_node);
            cur_node = next_node;
        }
        if (src + 1 == cur_node) {
            dir = RIGHT;
        } else if (src - 1 == cur_node) {
            dir = LEFT;
        } else if (src - x == cur_node) {
            dir = UP;
        } else if (src + x == cur_node) {
            dir = DOWN;
        }
    }
    return dir;
}
void AutoGame2::scan_graph()
{
    int y = board->get_height();
    int x = board->get_width();
    for (int i = 0; i < y * x; i++) {
        int board_y = i / x;
        int board_x = i % x;
        int id = i;
        if (board->at(board_y, board_x) == WALL) continue;
        int id_r = i + 1;
        int id_l = i - 1;
        int id_u = i - x;
        int id_d = i + x;
        bool xunder = board_x - 1 < 0;
        bool xover = board_x + 1 >= x;
        bool yunder = board_y - 1 < 0;
        bool yover = board_y + 1 >= y;
        graph.at(id).at(id) = 0;
        if (!xover) {
            if (board->at(board_y, board_x + 1) == EMPTY || board->at(board_y, board_x + 1) == APPLE || board->at(board_y, board_x + 1) == HEAD) {
                graph.at(id).at(id_r) = 1;
                graph.at(id_r).at(id) = 1;
            } else {
                graph.at(id).at(id_r) = 0;
                graph.at(id_r).at(id) = 0;
            }
        }
        if (!xunder) {
            if (board->at(board_y, board_x - 1) == EMPTY || board->at(board_y, board_x - 1) == APPLE || board->at(board_y, board_x - 1) == HEAD) {
                graph.at(id).at(id_l) = 1;
                graph.at(id_l).at(id) = 1;
            } else {
                graph.at(id).at(id_l) = 0;
                graph.at(id_l).at(id) = 0;
            }
        }
        if (!yover) {
            if (board->at(board_y + 1, board_x) == EMPTY || board->at(board_y + 1, board_x) == APPLE || board->at(board_y + 1, board_x) == HEAD) {
                graph.at(id_d).at(id) = 1;
                graph.at(id).at(id_d) = 1;
            } else {
                graph.at(id_d).at(id) = 0;
                graph.at(id).at(id_d) = 0;
            }
        }
        if (!yunder) {
            if (board->at(board_y - 1, board_x) == EMPTY || board->at(board_y - 1, board_x) == APPLE || board->at(board_y - 1, board_x) == HEAD) {
                graph.at(id_u).at(id) = 1;
                graph.at(id).at(id_u) = 1;
            } else {
                graph.at(id_u).at(id) = 0;
                graph.at(id).at(id_u) = 0;
            }
        }
    }
}
