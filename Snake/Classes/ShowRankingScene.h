#ifndef __SHOWRANKINGSCENE_H__
#define __SHOWRANKINGSCENE_H__

#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class ShowRankingScene : public LayerColor {
public:
	virtual bool init();
	CREATE_FUNC(ShowRankingScene);

	static cocos2d::Scene* createScene();

	void goBack(cocos2d::Ref* pSender);
};

#endif
