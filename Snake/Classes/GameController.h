#pragma once
#include <string>
#include <vector>
#include <utility>

using namespace std;

class GameController {

private:
	//가장 최근 score 저장
	int score;

	//랭킹 기록을 위한 username과 score 쌍들 (나중에 이걸 파일로 저장해야함.)
	vector<pair<int, string>> ranking;

public:
	//GameOverScene에서 GameController로부터 게임 종료 시점의 Score를 받아오기 위함.
	int getScore();

	//Game에서 게임 종료 시점의 Score를 GameController로 받아오기 위함.
	void setScore(int);

	//GameOverScene에서 입력받은 user를 score와 pair로 ranking에 저장하기 위함. (score 상위 10개만 남김.)
	void addUser(string);

	//랭킹이 프로그램을 종료해도 날아가지 않도록 텍스트 파일에 기록
	void recordRank();

	//종료 조건:자기 몸 건드렸는지, 벽에 닿았는지 (추후 수정) //종료조건은 이미 구현 됐고, 여기서는 application의 state변화를 이끌어 내는 것!
	void endGameCondition();
};