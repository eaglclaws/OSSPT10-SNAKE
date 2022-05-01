#ifndef __GAMEOVERSCENE_H__
#define __GAMEOVERSCENE_H__
#include "cocos2d.h"
#include "GameController.h"
#include "ui\UITextField.h"


class GameOverScene : public cocos2d::LayerColor{
private:
	GameController* gc;
	cocos2d::CCTextFieldTTF* input_text;

public:
	virtual bool init();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(GameOverScene);

	
	static cocos2d::Scene* createScene();
};
#endif