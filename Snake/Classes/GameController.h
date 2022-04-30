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
	vector<pair<string, int>> ranking;

public:
	//GameOverScene에서 GameController로부터 게임 종료 시점의 Score를 받아오기 위함.
	int getScore();

	//Game에서 게임 종료 시점의 Score를 GameController로 받아오기 위함.
	void setScore();

	//GameOverScene에서 입력받은 user를 score와 pair로 ranking에 저장하기 위함.
	void adduser(string);

	//ranking에 있는 user와 score pair를 username을 인자로 받아 지우기 위함.
	void deleteUser(string);

	//종료 조건:자기 몸 건드렸는지, 이동방향과 반대로 움직였는지, 벽에 닿았는지 (추후 수정)
	void endGameCondition();
};