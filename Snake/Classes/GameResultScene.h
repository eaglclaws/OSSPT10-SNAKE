#ifndef __GAMERESULTSCENE_H__
#define __GAMERESULTSCENE_H__

#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class GameResultScene : public LayerColor{
	virtual bool init();
	CREATE_FUNC(GameResultScene);

	static cocos2d::Scene* createScene();

};

#endif
