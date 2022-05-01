#include "ShowRankingScene.h"
#include "StartScene.h"
#include "GameController.h"

bool ShowRankingScene::init() {
    if (!LayerColor::initWithColor(cocos2d::Color4B(255, 255, 255, 255))) {
        return false;
    }
    
    GameController* gc = GameController::getInstance();
    vector<pair<int, string>> ranker = gc->getRecordedRank();

    int size = ranker.size() > 5 ? ranker.size() : 5;

    Label *player[5];

    string data;
    for (int i = 0; i < size; i++) {
        data = to_string(ranker[i].first) + ". " + ranker[i].second;

        player[i] = Label::createWithTTF(data, "fonts/arial.ttf", 10);
        player[i]->setTextColor(Color4B::BLACK);
        player[i]->setPositionNormalized(Vec2(0.5, 0.9 - 0.1 * i));
        this->addChild(player[i]);
    }

    auto goBackButton = MenuItemFont::create("Go Back", CC_CALLBACK_1(ShowRankingScene::goBack, this));
    goBackButton->setColor(Color3B(0, 0, 0));


    auto pMenu = Menu::create(goBackButton, NULL);

    pMenu->alignItemsVertically();

    this->addChild(pMenu);


}

void ShowRankingScene::goBack(cocos2d::Ref* pSender) {
    auto scene = StartScene::createScene();
    Director::getInstance()->replaceScene(scene);
}