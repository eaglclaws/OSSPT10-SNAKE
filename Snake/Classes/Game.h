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

#ifndef __GAME_H_
#define __GAME_H_
#include "Board.h"

enum game_state {
    GAME_STATE_INIT,
    GAME_STATE_PLAY,
    GAME_STATE_PAUSE,
    GAME_STATE_OVER
}

/*
    Game 클래스
    Board 클래스와 Snake 클래스를 관리해주는 최상위 클래스

    * 게임 진행 중 Board와 Snake를 직접 수정할 필요가 없기 때문에 모든
      관리를 Game 클래스에 위임함. 실제로 Board와 Snake에 대한 수정은
      game_update 메소드 내에서 가능함. (Board의 갱신, Snake의 생존 여부
      판단 등)
*/
class Game {
public:
/*  현재 game_state 반환 */
    enum game_state
    state();

/*  보드를 초기화 또는 리셋 state를 GAME_STATE_INIT로 전환*/
    void
    game_init();

/*  state를 GAME_STATE_PLAY로 전환 */
    void
    game_play();

/*  state를 GAME_STATE_PAUSE로 전환 */
    void
    game_pause();

/*  state를 GAME_STATE_OVER로 전환 */
    void
    game_over();

/*  Board와 Snake의 상태 갱신, 그 side effect에 따라
    state 전환 메소드 호출 */
    void
    game_update();

/*  출력을 위해 Board를 노출 (임시) TODO: 이후 배열만 노출 할 것! */
    Board
    game_board();

/*
    (y, x)에 사과 놓기 시도. 외부에서 랜덤이 결정 되기 때문에 (y, x)에
    사과를 놓을 수 없다면 false를 반환. 다음과 같이 사용하기를 추천
    Game game = new Game;
    while (!game.place_apple(y, x)) { code here } 
*/
    bool
    place_apple(int, int);

    int
    player_score();
}
