#ifndef __DUALBOARD_H__
#define __DUALBOARD_H__
#include <vector>
#define DUALBOARD_WIDTH 82
#define DUALBOARD_HEIGHT 42

class Snake;

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
    DOWN,
    LEFT,
    RIGHT
};

struct snake_node
{
    struct snake_node* next;
    int x;
    int y;
};

class DualBoard
{
private:
    std::array<std::array<board_elements, DUALBOARD_WIDTH>, DUALBOARD_HEIGHT>* board_data;
    struct snake_node** head_player_one;
    struct snake_node** tail_player_one;
    struct snake_node** head_player_two;
    struct snake_node** tail_player_two;
    int length;
    enum board_dir current_player_one;
    enum board_dir current_player_two;

    bool has_apple;
public:
    DualBoard();
    ~DualBoard();

    void
        init();

    std::array<std::array<board_elements, DUALBOARD_WIDTH>, DUALBOARD_HEIGHT>*
        data();

    bool
        update(enum board_dir);

    bool
        update();

    void
        set_direction(enum board_dir);

    enum board_dir
        get_direction();

    bool
        place_apple(int, int);

    int
        get_length();

    void
        load(int**, std::vector<std::pair<int, int>>*, int);

    void
        apple_placed();

    void
        apple_removed();

    bool
        is_apple_placed();
    
    int
        getBoardWidth() { return DUALBOARD_WIDTH; }
    int
        getBoardHeight() { return DUALBOARD_WIDTH; }
    
};

#endif
