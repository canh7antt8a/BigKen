//
//  PopUpVongQuayMayMan.cpp
//  MyCards
//
//  Created by hungle on 8/10/16.
//
//

///@ PopUpVongQuayMayMan.cpp
#include "PopUpVongQuayMayMan.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"
#include <vector>
#include "UI/MButton.hpp"
#include "UI/MText.hpp"
using namespace std;
using namespace cocos2d;

bool PopUpVongQuayMayMan::init() {
    if (!Popup::init())
        return false;
    
    backgroundPopup = MSprite::create("vongquay/sprite_vongtrong.png");
    backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
                                      visibleSize.height / 2 - backgroundPopup->getHeight() / 2));
    
    backgroundContentSize = background->getContentSize();
    auto pos = backgroundPopup->getPosition();
    
    m_popupLayer = Layer::create();
    m_popupLayer->setAnchorPoint(Vec2::ZERO);
    m_popupLayer->setPosition(Vec2(origin.x,origin.y - visibleSize.height));
    addChild(m_popupLayer);
    
    m_popupLayer->addChild(backgroundPopup);
    
    auto tabButton = MButton::create("btn_taoban.png");
    tabButton->setPosition(Vec2(pos.x + backgroundPopup->getWidth()/2 - tabButton->getWidth()/2,
                                pos.y + backgroundPopup->getHeight()/2 - tabButton->getHeight()/2));
    m_popupLayer->addChild(tabButton);
    
    //button close
    auto btn_back = MButton::create();
    btn_back->loadTextureNormal(IMAGE_CLOSE);
    btn_back->setZoomScale(0.02f);
    btn_back->setAnchorPoint(cocos2d::Vec2(0, 0));
    btn_back->setTag(TAG_POPUP_BTN_BACK);
    btn_back->setPosition(Vec2(backgroundPopup->getPosition().x
                               + backgroundPopup->getWidth() - btn_back->getWidth() - 15
                               ,backgroundPopup->getPosition().y
                               + backgroundPopup->getHeight() - btn_back->getHeight() - 15));
    m_popupLayer->addChild(btn_back);
    
    btn_back->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->disappear();
                break;
            default:
                break;
        }
    });
    return true;
}

void PopUpVongQuayMayMan::menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type){
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            this->disappear();
            break;
        default:
            break;
    }
}

void PopUpVongQuayMayMan::onExit() {
    Popup::onExit();
}
