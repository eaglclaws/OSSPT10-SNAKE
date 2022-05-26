#ifndef __DUAL_GAME_H_
#define __DUAL_GAME_H_
#include <vector>
#include <utility>
#include "Game.h"
#include "DualBoard.h"
#include "EnumList.h"


class DualGame : public Game {
private:
    DualBoard* board;
    enum game_state state;
    enum PlayerSelect winner;
public:
    DualGame();
    ~DualGame() override;
    //Get Methods
    bool is_apple_placed() override;
    enum game_state get_state() override;
    enum game_state update() override;
    enum board_elements board_data(int, int) override;
    enum board_dir get_direction() override;
    int** export_board() override;
    int player_score() override; //In DualGame does not use. score is not calculated.
    int export_dir() override; 
    std::vector<std::pair<int, int>>* export_snake() override;
    //Set Methods
    void init() override;
    void play() override;
    void pause() override;
    void over() override;
    void load(int**, std::vector<std::pair<int, int>>*, int) override;
    void key_event(enum key_press) override;

    //new one
    bool place_apple() override;
    enum board_dir get_direction(enum PlayerSelect) override;
    int get_board_height() override;
    int get_board_width() override;
    void key_event(enum key_press, enum PlayerSelect) override;
    std::pair<int, int> get_head_pos(enum PlayerSelect) override;
};

#endif
