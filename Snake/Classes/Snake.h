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

#ifndef __SNAKE_H__
#define __SNAKE_H__

enum snake_state {
    SNAKE_STATE_ALIVE,
    SNAKE_STATE_DEAD
};

enum direction {
    SNAKE_UP,
    SNAKE_RIGHT,
    SNAKE_DOWN,
    SNAKE_LEFT
};

class Snake {
public:
    enum snake_state
    state();

    int
    length();

    void
    face(enum direction);

    void
    kill_snake();
}
