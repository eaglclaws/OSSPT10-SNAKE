#pragma once
#include "GameController.h"
#include "Game.h"
#include "cocos2d.h"


class Game;

class GameScene : public cocos2d::LayerColor{
private:
	GameController* gc;
	Game game;

public:
	virtual bool init();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	CREATE_FUNC(GameScene);

	static cocos2d::Scene* createScene();
};