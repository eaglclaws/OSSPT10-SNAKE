#pragma once
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class StartScene : public LayerColor{
public:
	virtual bool init();
	CREATE_FUNC(StartScene);

	static cocos2d::Scene* createScene();
};