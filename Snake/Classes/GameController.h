#pragma once
#include <string>

using namespace std;

class GameController {

	//score 기록
	int score;

	//랜덤위치에 food 배치
	void food();

	//food를 먹었는지 체크 (여기서 안 해도 됨.)
	void checkFood();

	//플레이어 이름
	string playerName;

	//랭킹 기록(int* 임시, 외부 파일로 해야 안날아감)
	int* ranking;

	//게임 종료
	void endGame();

	//종료 조건:자기 몸 건드렸는지, 벽에 닿았는지, 이동방향과 반대로 움직였는지, 

};