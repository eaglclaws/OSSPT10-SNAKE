#pragma once
#include <string>
#include <cocos2d.h>

using namespace std;

class GameController {
public:
	GameController();
	void loadGame();
	void saveGame(string data);
	static GameController* instance;
	static GameController* getInstance();
};