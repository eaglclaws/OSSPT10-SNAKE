#include "GamePauseLayer.h"

USING_NS_CC;


GamePauseLayer* GamePauseLayer::create() {
    GamePauseLayer* layer = new GamePauseLayer();
    if (!layer->initWithColor(Color4B::WHITE)) {

    }

    auto resume_button = MenuItemFont::create("Resume", [layer](Ref* psender) {
        layer->setVisible(false);
    });
    resume_button->setColor(Color3B(0, 0, 0));

    auto restart_button = MenuItemFont::create("Restart", [layer](Ref* psender) {
        //gc���� �� �����ϰ� �ٽ� ����

    });
    restart_button->setColor(Color3B(0, 0, 0));

    auto save_button = MenuItemFont::create("Save", [layer](Ref* psender) {
        //gc�� ��û ���� ������ ����
    });
    save_button->setColor(Color3B(0, 0, 0));

    auto exit_button = MenuItemFont::create("Exit", [layer](Ref* psender) {
        //exit
        
    });
    exit_button->setColor(Color3B(0, 0, 0));


    auto pMenu = Menu::create(resume_button, restart_button, save_button, exit_button, NULL);

    pMenu->alignItemsVertically();

    layer->addChild(pMenu);

    return layer;
}