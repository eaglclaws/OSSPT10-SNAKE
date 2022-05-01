#pragma once
#include "cocos2d.h"

USING_NS_CC;

class StartScene : public LayerColor{
private:
	void playGame(cocos2d::Ref* pSender);
	void loadGame(cocos2d::Ref* pSender);
	void rankingGame(cocos2d::Ref* pSender);
	void exitGame(cocos2d::Ref* pSender);
public:
	virtual bool init();
	CREATE_FUNC(StartScene);

	static cocos2d::Scene* createScene();
};