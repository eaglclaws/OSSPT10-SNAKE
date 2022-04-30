#include "GameOverScene.h"
#include "cocos2d.h"
#include "ShowResultScene.h"
USING_NS_CC;


Scene* GameOverScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}


bool GameOverScene::init() {
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }

    gc = GameController::getInstance();

    auto gameover = Label::createWithTTF("Game Over", "fonts/arial.ttf", 40);
    gameover->setTextColor(Color4B::BLACK);
    gameover->setPositionNormalized(Vec2(0.5, 0.8));

    //해야할 부분
    auto score = Label::createWithTTF("Score", "fonts/arial.ttf", 40);
    gameover->setTextColor(Color4B::BLACK);
    gameover->setPositionNormalized(Vec2(0.5, 0.8));
    

    return true;
}

void GameOverScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_ENTER:
        //gc에 username주는 거 추가. 


        auto scene = ShowResultScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}