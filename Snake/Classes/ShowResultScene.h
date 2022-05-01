#ifndef __SHOWRESULTSCREEN_H__
#define __SHOWRESULTSCREEN_H__

#include "cocos2d.h"

USING_NS_CC;

class ShowResultScene : public LayerColor {
public:
	virtual bool init();
	CREATE_FUNC(ShowResultScene);

	static cocos2d::Scene* createScene();

	void restartGame(cocos2d::Ref* pSender);
	void exitGame(cocos2d::Ref* pSender);
};

#endif
