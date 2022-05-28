#include "DualResultScene.h"
#include "GameController.h"
#include "StartScene.h"
#include <string>
#include "EnumList.h"

Scene* DualResultScene::createScene() {
    auto scene = Scene::create();
    auto layer = DualResultScene::create();
    scene->addChild(layer);
    return scene;
}

bool DualResultScene::init() {
    if (!LayerColor::initWithColor(cocos2d::Color4B(255, 255, 255, 255))) {
        return false;
    }

    auto gc = GameController::getInstance();
    enum PlayerSelect winner = gc->get_winner();
    string win;
    switch (winner)
    {
    case PLAYER1:
        win = "Winner : PLAYER1";
        break;
    case PLAYER2:
        win = "Winner : PLAYER2";
        break;
    case NONE:
        win = "DRAW";
        break;
    default:
        break;
    }   

    // score gc에서 가져와야함.
    auto who_win = Label::createWithTTF(win, "fonts/arial.ttf", 30);
    who_win->setTextColor(Color4B::BLACK);
    who_win->setPositionNormalized(Vec2(0.5, 0.8));

    auto restart_button = MenuItemFont::create("Restart", CC_CALLBACK_1(DualResultScene::restartGame, this));
    restart_button->setColor(Color3B(0, 0, 0));

    auto exit_button = MenuItemFont::create("Exit", CC_CALLBACK_1(DualResultScene::exitGame, this));
    exit_button->setColor(Color3B(0, 0, 0));

    auto button = Menu::create(restart_button, exit_button, NULL);
    button->setPositionNormalized(Vec2(0.5, 0.6));
    button->alignItemsVertically();

    this->addChild(who_win);
    this->addChild(button);
    return true;

}

void DualResultScene::restartGame(cocos2d::Ref* pSender) {
    auto scene = StartScene::createScene();
    Director::getInstance()->replaceScene(scene);
}


void DualResultScene::exitGame(cocos2d::Ref* pSender) {
    Director::getInstance()->end();
}