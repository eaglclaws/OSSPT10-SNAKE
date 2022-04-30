#include "GamePauseScene.h"


GamePauseScene* GamePauseScene::create() {
    GamePauseScene* layer = new GamePauseScene();
    if (!layer->initWithColor(cocos2d::Color4B::WHITE)) {

    }

    auto resume_button = cocos2d::MenuItemFont::create("Resume", [layer](Ref* psender) {
        layer->setVisible(false);
    });
    resume_button->setColor(cocos2d::Color3B(0, 0, 0));

    auto restart_button = cocos2d::MenuItemFont::create("Restart", [layer](Ref* psender) {
        //gc에서 올 삭제하고 다시 시작
    });
    restart_button->setColor(cocos2d::Color3B(0, 0, 0));

    auto save_button = cocos2d::MenuItemFont::create("Save", [layer](Ref* psender) {
        //gc에 요청 현재 데이터 저장
    });
    save_button->setColor(cocos2d::Color3B(0, 0, 0));

    auto exit_button = cocos2d::MenuItemFont::create("Exit", [layer](Ref* psender) {
        //exit
        
    });
    exit_button->setColor(cocos2d::Color3B(0, 0, 0));


    auto pMenu = cocos2d::Menu::create(resume_button, restart_button, save_button, exit_button, NULL);

    pMenu->alignItemsVertically();

    layer->addChild(pMenu);

    return layer;
}