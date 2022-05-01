#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__
#include <string>
#include <cocos2d.h>
#include <vector>
#include "Game.h"
#include <vector>
#include <utility>

using namespace std;

class GameController {
private:
	Game* game;
	void saveBoard(int** board);
	void saveSnake(vector<pair<int, int>>* snake);
	void saveDirection(int dir);
	static GameController* instance;
public:
	static GameController* getInstance();
	bool isLoadClicked;
	static bool isCreated;
	static void clicked(bool isLoad);

	int** loadBoard();
	vector<pair<int, int>>* loadSnake();
	int loadDirection();
	void setGame(Game* gameInstance);
	void saveGame(); 
	void resetGame(); // Game init() play() 호출 Scene변경.
	void gamePlay();

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

	//파일에 저장한 랭킹을 불러옴. (RankingScene에서 사용할 수 있게)
	vector<pair<int, string>> getRocordedRank();
};

#endif
