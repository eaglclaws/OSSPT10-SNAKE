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

    auto header = Label::createWithTTF("Snake Game", "fonts/arial.ttf", 50);
    header->setTextColor(Color4B::BLACK);
    header->setPositionNormalized(Vec2(0.5, 0.9));
    this->addChild(header);


    auto single_button = MenuItemFont::create("Single Play", CC_CALLBACK_1(StartScene::singleGame, this));
    single_button->setColor(Color3B(0, 0, 0));

    auto dual_button = MenuItemFont::create("Dual Play", CC_CALLBACK_1(StartScene::dualGame, this));
    dual_button->setColor(Color3B(0, 0, 0));

    auto auto_button = MenuItemFont::create("Auto Play", CC_CALLBACK_1(StartScene::autoGame, this));
    auto_button->setColor(Color3B(0, 0, 0));

    auto load_button = MenuItemFont::create("Load", CC_CALLBACK_1(StartScene::loadGame, this));
    load_button->setColor(Color3B(0, 0, 0));

    auto ranking_button = MenuItemFont::create("Ranking", CC_CALLBACK_1(StartScene::rankingGame, this));
    ranking_button->setColor(Color3B(0, 0, 0));

    auto exit_button = MenuItemFont::create("Exit", CC_CALLBACK_1(StartScene::exitGame, this));
    exit_button->setColor(Color3B(0, 0, 0));


    auto pMenu = Menu::create(single_button, dual_button, auto_button, load_button, ranking_button, exit_button, NULL);

    pMenu->alignItemsVertically();

    this->addChild(pMenu);
    return true;
}


void StartScene::singleGame(cocos2d::Ref* pSender) {
    GameController::clicked(false);
    auto gc = GameController::getInstance();
    gc->set_game_type(SOLO);
    gc->set_players(1);

    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void StartScene::dualGame(cocos2d::Ref* pSender) {
    GameController::clicked(false);
    auto gc = GameController::getInstance();
    gc->set_game_type(DUAL);
    gc->set_players(2);

    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void StartScene::autoGame(cocos2d::Ref* pSender) {
    GameController::clicked(false);
    auto gc = GameController::getInstance();
    gc->set_game_type(AUTO1);
    gc->set_players(1);

    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void StartScene::loadGame(cocos2d::Ref* pSender) {
    if (GameController::getInstance()->loadDirection() != -1) {
        GameController::clicked(true);

        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}

void StartScene::rankingGame(cocos2d::Ref* pSender) {
    auto scene = ShowRankingScene::createScene();
    cocos2d::Director::getInstance()->replaceScene(scene);
}

void StartScene::exitGame(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}
