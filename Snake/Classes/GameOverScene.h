#pragma once
#include "cocos2d.h"
#include "GameController.h"



class GameOverScene : public cocos2d::LayerColor{
private:
	GameController* gc;
public:
	virtual bool init();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(GameOverScene);

	static cocos2d::Scene* createScene();
};