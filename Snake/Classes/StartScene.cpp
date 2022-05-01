#include "StartScene.h"
#include "GameScene.h"
#include "ShowRankingScene.h"
#include "GameController.h"


Scene* StartScene::createScene() {
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init(){
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))){
        return false;
    }

    auto play_button = MenuItemFont::create("Play", CC_CALLBACK_1(StartScene::playGame, this));
    play_button->setColor(Color3B(0, 0, 0));

    auto load_button = MenuItemFont::create("Load", CC_CALLBACK_1(StartScene::loadGame, this));
    load_button->setColor(Color3B(0, 0, 0));

    auto ranking_button = MenuItemFont::create("Ranking", CC_CALLBACK_1(StartScene::rankingGame, this));
    ranking_button->setColor(Color3B(0, 0, 0));

    auto exit_button = MenuItemFont::create("Exit", CC_CALLBACK_1(StartScene::exitGame, this));
    exit_button->setColor(Color3B(0, 0, 0));


    auto pMenu = Menu::create(play_button, load_button, ranking_button, exit_button, NULL);

    pMenu->alignItemsVertically();

    this->addChild(pMenu);
    return true;
}

void StartScene::playGame(cocos2d::Ref* pSender) {
    GameController::clicked(false);

    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}


void StartScene::loadGame(cocos2d::Ref* pSender) {
    GameController::clicked(true);

    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void StartScene::rankingGame(cocos2d::Ref* pSender) {
    auto scene = ShowRankingScene::createScene();
    cocos2d::Director::getInstance()->replaceScene(scene);
}

void StartScene::exitGame(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}