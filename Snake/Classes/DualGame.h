#ifndef __DUAL_GAME_H_
#define __DUAL_GAME_H_
#include <vector>
#include <utility>
#include "Game.h"
#include "Board.h"

class DualGame : public Game {
private:
    Board* board;
    enum game_state state;
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
    int player_score() override;
    int export_dir() override;
    std::vector<std::pair<int, int>>* export_snake() override;
    //Set Methods
    void init() override;
    void play() override;
    void pause() override;
    void over() override;
    void load(int**, std::vector<std::pair<int, int>>*, int) override;
    void key_event(enum key_press) override;
    bool place_apple(int, int) override;
};

#endif
