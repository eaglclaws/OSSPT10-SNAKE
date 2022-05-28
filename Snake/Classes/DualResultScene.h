#ifndef __DUALRESULTSCENE_H__
#define __DUALRESULTSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class DualResultScene : public LayerColor {
public:
	virtual bool init();
	CREATE_FUNC(DualResultScene);

	static cocos2d::Scene* createScene();

	void restartGame(cocos2d::Ref* pSender);
	void exitGame(cocos2d::Ref* pSender);
};

#endif