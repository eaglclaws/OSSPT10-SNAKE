#pragma once
#include <string>
#include <cocos2d.h>

using namespace std;

class GameController {
public:

	void loadGame();
	void saveGame(string data);
};