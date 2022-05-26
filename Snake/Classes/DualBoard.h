#ifndef __DUALBOARD_H__
#define __DUALBOARD_H__
#include <vector>
#include "EnumList.h"
#define DUALBOARD_WIDTH 82
#define DUALBOARD_HEIGHT 42

class Snake;

class DualBoard
{
private:
    std::array<std::array<board_elements, DUALBOARD_WIDTH>, DUALBOARD_HEIGHT>* board_data;
    struct snake_node** head;
    struct snake_node** tail;
    struct snake_node** sec_head;
    struct snake_node** sec_tail;
    int length;
    int sec_length;
    enum board_dir current;
    enum board_dir sec_current;
    bool has_apple;
    std::pair<int, int> apple_pos;
    int apple_amount;
    enum PlayerSelect winner;
    bool winner_flag;

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

    int**
        export_board();

    std::vector<std::pair<int, int>>*
        export_snake();

    int
        export_dir();

    void
        load(int**, std::vector<std::pair<int, int>>*, int);

    void
        apple_placed();

    void
        apple_removed();

    bool
        is_apple_placed();

    std::pair<int, int>
        get_apple_pos();

    void
        set_apple_pos(int, int);

    int
        get_width() { return DUALBOARD_WIDTH; }

    int
        get_height() { return DUALBOARD_HEIGHT; }

    std::pair<int, int>
        get_snake_head();

    std::pair<int, int>
        get_snake_head(enum PlayerSelect);

    void
        set_direction(enum board_dir, enum PlayerSelect);

    enum board_dir
        get_direction(enum PlayerSelect);

    bool
        update(enum board_dir, enum PlayerSelect);
    int
        get_apple_amount();

    enum PlayerSelect
        get_winner() { return winner; }
};

#endif
