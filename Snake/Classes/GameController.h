#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__
#include <string>
#include <cocos2d.h>
#include <vector>
#include "Game.h"

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
	static bool isLoadClicked;
	static bool isCreated;
	static void clicked(bool isLoad);

	int** loadBoard();
	vector<pair<int, int>>* loadSnake();
	int loadDirection();
	void setGame(Game* gameInstance);
	void saveGame(); 
	void resetGame(); // Game init() play() 호출 Scene변경.
};
#endif