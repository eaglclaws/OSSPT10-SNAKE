#include "GameOverScene.h"
#include "cocos2d.h"
#include "ShowResultScene.h"
#include <string>
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


    auto gameover = Label::createWithTTF("Game Over", "fonts/arial.ttf", 40);
    gameover->setTextColor(Color4B::BLACK);
    gameover->setPositionNormalized(Vec2(0.5, 0.8));
    
    //해야할 부분
    auto score = Label::createWithTTF("Score", "fonts/arial.ttf", 40);
    score->setTextColor(Color4B::BLACK);
    score->setPositionNormalized(Vec2(0.5, 0.6));
    
    input_text = TextFieldTTF::textFieldWithPlaceHolder("input your ID", "fonts/arial.ttf", 30);

    input_text->setTextColor(Color4B::BLACK);
    input_text->setPositionNormalized(Vec2(0.5, 0.4));
    input_text->attachWithIME();
    this->addChild(input_text);

    auto enter_listener = EventListenerKeyboard::create();
    enter_listener->onKeyPressed = CC_CALLBACK_2(GameOverScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(enter_listener, this);

    return true;
}

void GameOverScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_ENTER:
        //gc에 username주는 거 추가. 
        std::string id_input = input_text->getString();
        GameController::getInstance()->addUser(id_input);


        auto scene = ShowResultScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}
