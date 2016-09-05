//
//  PopupReconnect.cpp
//  MyCards
//
//  Created by hungle on 6/20/16.
//
//

#include "PopupReconnect.hpp"
#include "UI/MLabel.hpp"
#include "UI/M9Path.hpp"
#include "Utils/LoadingManager.hpp"
#include "Utils/NetworkManager.h"

PopupReconnect*  PopupReconnect::_instance = 0;

PopupReconnect::PopupReconnect(){
    Size _visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 _origin = Director::getInstance()->getVisibleOrigin();
    auto darkSprite = LayerColor::create(Color4B(0, 0, 0, 160));
    darkSprite->setContentSize(_visibleSize);
    darkSprite->setPosition(_origin);
    this->addChild(darkSprite);
    
    auto sprite = M9Path::create("backgroundpopup.9.png",Size(_visibleSize.width*0.6f,_visibleSize.height*0.4f));
    sprite->setAnchorPoint(Point::ANCHOR_MIDDLE);
    sprite->setPosition(Vec2(_visibleSize.width/2,_visibleSize.height/2));
    this->addChild(sprite);
    
    auto ok = cocos2d::ui::Button::create("btn_doiluat.png");
    ok->setTitleText("OK");

    ok->setTitleFontSize(ok->getContentSize().height/2);
    ok->setPosition(Vec2(sprite->getContentSize().width/2,ok->getContentSize().height));
    ok->addTouchEventListener(CC_CALLBACK_2(PopupReconnect::menuCallBack,this));
    sprite->addChild(ok);
    
    auto text = MLabel::create("Bạn có muốn reconnect ko,nhanh m ?! \n ừ ,nút OK đấy!", ok->getContentSize().height/2);
    text->setAlignment(cocos2d::TextHAlignment::CENTER);
    text->setPosition(Vec2(sprite->getWidth()/2 - text->getWidth()/2,
                           sprite->getHeight()/2));
    sprite->addChild(text);
}

void PopupReconnect::menuCallBack(Ref *pSender, ui::Widget::TouchEventType eventType){
    if (eventType == ui::Widget::TouchEventType::ENDED){
        //handle nut ok
        CCLOG("reconnect");
        hidePopup();
        bool canReconnect = NetworkManager::getInstance()->reconnect();
        if (!canReconnect) {
            showPopup();
        }
    }
}

void PopupReconnect::hidePopup() {
    _eventDispatcher->resumeEventListenersForTarget(Director::getInstance()->getRunningScene(), true);
    this->removeFromParentAndCleanup(true);
}

PopupReconnect::~PopupReconnect(){
}

PopupReconnect* PopupReconnect::getInstance(){
    if(!_instance){
        _instance = new PopupReconnect();
    }
    return _instance;
}

void PopupReconnect::showPopup() {
    if (this->getParent() == nullptr) {
        auto scene = cocos2d::Director::getInstance()->getRunningScene();
        if (scene != nullptr) {
            _eventDispatcher->pauseEventListenersForTarget(scene, true);
            scene->addChild(this);
        }
    }
}

void PopupReconnect::setRoomIndex(int roomIndex){
    this->roomIndex = roomIndex;
}
 
int PopupReconnect::getRoomIndex(){
    return this->roomIndex;
}

bool PopupReconnect::init(){
    if(Node::init()){
        return true;
    }
    return false;
}
