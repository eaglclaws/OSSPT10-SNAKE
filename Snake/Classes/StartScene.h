#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class StartScene : public LayerColor{
private:
	void singleGame(cocos2d::Ref* pSender);
	void dualGame(cocos2d::Ref* pSender);
	void autoGame(cocos2d::Ref* pSender);
	void loadGame(cocos2d::Ref* pSender);
	void rankingGame(cocos2d::Ref* pSender);
	void exitGame(cocos2d::Ref* pSender);
public:
	virtual bool init();
	CREATE_FUNC(StartScene);

	static cocos2d::Scene* createScene();
};

#endif
