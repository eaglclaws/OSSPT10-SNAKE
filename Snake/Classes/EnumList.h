#ifndef __ENUMLIST_H__
#define __ENUMLIST_H__

enum board_elements
{
    EMPTY,
    WALL,
    HEAD,
    SNAKE,
    TAIL,
    APPLE
};

enum board_dir
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum PlayerSelect {
    PLAYER1,
    PLAYER2,
    NONE
};

enum game_state {
    GAME_STATE_INIT,
    GAME_STATE_PLAY,
    GAME_STATE_PAUSE,
    GAME_STATE_OVER
};

enum key_press {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_ESC
};

struct snake_node
{
    struct snake_node* next;
    int x;
    int y;
};

enum game_T {
    SOLO,
    DUAL,
    AUTO1,
    AUTO2
};


#endif