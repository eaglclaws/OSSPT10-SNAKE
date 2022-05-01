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

#include "Snake.h"

Snake::Snake(int x, int y)
{
    snake_head = new struct node *;
    snake_tail = new struct node *;
    (*snake_head) = new struct node;
    (*snake_head)->next = nullptr;
    (*snake_head)->x = x;
    (*snake_head)->y = y;
    (*snake_tail) = (*snake_head);
}

Snake::~Snake()
{
    struct node *cur = (*snake_head);
    while (cur->next != nullptr) {
        struct node *temp = cur->next;
        delete cur;
        cur = temp;
    }
    delete *snake_tail;
    delete snake_tail;
    delete snake_head;
}

struct node **
Snake::head()
{
    return snake_head;
}

struct node **
Snake::tail()
{
    return snake_tail;
}

void
Snake::grow()
{
    struct node *new_node = new struct node;
    new_node->next = (*snake_head);
    new_node->x = (*snake_head)->x + 1;
    new_node->y = (*snake_head)->y;
    (*snake_head) = new_node;
}