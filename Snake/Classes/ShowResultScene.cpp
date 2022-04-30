#include "ShowResultScene.h"
#include "GameController.h"
#include "StartScene.h"
#include <string>


Scene* ShowResultScene::createScene() {
    auto scene = Scene::create();
    auto layer = ShowResultScene::create();
    scene->addChild(layer);
    return scene;
}

bool ShowResultScene::init() {
    if (!LayerColor::initWithColor(cocos2d::Color4B(255, 255, 255, 255))) {
        return false;
    }

    auto gc = GameController::getInstance();

    // score gc에서 가져와야함.
    auto score = Label::createWithTTF("Score", "fonts/arial.ttf", 30);
    score->setTextColor(Color4B::BLACK);
    score->setPositionNormalized(Vec2(0.5, 0.8));

    auto restart_button = MenuItemFont::create("Restart", CC_CALLBACK_1(ShowResultScene::restartGame, this));
    restart_button->setColor(Color3B(0, 0, 0));

    auto exit_button = MenuItemFont::create("Exit", CC_CALLBACK_1(ShowResultScene::exitGame, this));
    exit_button->setColor(Color3B(0, 0, 0));

    auto button = Menu::create(restart_button, exit_button, NULL);
    button->setPositionNormalized(Vec2(0.5, 0.6));
    button->alignItemsVertically();

    this->addChild(score);
    this->addChild(button);
    return true;

}

void ShowResultScene::restartGame(cocos2d::Ref* pSender) {
    auto scene = StartScene::createScene();
    Director::getInstance()->replaceScene(scene);
}


void ShowResultScene::exitGame(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}

