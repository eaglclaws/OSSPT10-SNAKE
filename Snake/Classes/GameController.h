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
	void resetGame(); // Game init() play() ȣ�� Scene����.
	void gamePlay();

private:
	//���� �ֱ� score ����
	int score;

	//��ŷ ����� ���� username�� score �ֵ� (���߿� �̰� ���Ϸ� �����ؾ���.)
	vector<pair<int, string>> ranking;

public:
	//GameOverScene���� GameController�κ��� ���� ���� ������ Score�� �޾ƿ��� ����.
	int getScore();

	//Game���� ���� ���� ������ Score�� GameController�� �޾ƿ��� ����.
	void setScore(int);

	//GameOverScene���� �Է¹��� user�� score�� pair�� ranking�� �����ϱ� ����. (score ���� 10���� ����.)
	void addUser(string);

	//��ŷ�� ���α׷��� �����ص� ���ư��� �ʵ��� �ؽ�Ʈ ���Ͽ� ���
	void recordRank();

	//���Ͽ� ������ ��ŷ�� �ҷ���. (RankingScene���� ����� �� �ְ�)
	vector<pair<int, string>> getRocordedRank();
};

#endif
