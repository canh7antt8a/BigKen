//
//  MiniGamePopUp.cpp
//  KingGameTest
//
//  Created by hungle on 8/15/16.
//
//

#include "MiniGamePopUp.hpp"
#include "Utils/Common.h"
#include "Utils/TLMNConfig.hpp"
#include "UI/MSprite.hpp"
#include "UI/MButton.hpp"

using namespace cocos2d;

MiniGamePopUp*  MiniGamePopUp::_instance = 0;

MiniGamePopUp::MiniGamePopUp(){
    
    Size _visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 _origin = Director::getInstance()->getVisibleOrigin();
    
    auto cardSprite = Sprite::create("miniGame_popup.png");
    cardSprite->setPosition(Vec2(cardSprite->getContentSize().width/2,
                                 cardSprite->getContentSize().height/2));
    this->addChild(cardSprite);
    this->setContentSize(cardSprite->getContentSize());
    this->addEvent();
    this->setPosition(_origin+ _visibleSize - cardSprite->getContentSize()*1.5f);
    
    auto sprite_round = Sprite::create("round_blur.png");
    sprite_round->setTag(1);
    sprite_round->setPosition(Vec2(cardSprite->getContentSize().width/2,
                                   cardSprite->getContentSize().height/2));
    this->addChild(sprite_round);
    
    this->scheduleUpdate();
}

void MiniGamePopUp::show(){
    if (this->getChildByTag(1) != nullptr){
        auto ac1 = Spawn::create(ScaleTo::create(1.0f, 1.8f),FadeOut::create(1.0f), NULL);
        auto ac2 =  Spawn::create(ScaleTo::create(0,1.0f),FadeTo::create(0,255),NULL);
        this->getChildByTag(1)->runAction(RepeatForever::create(Sequence::create(ac1,ac2,NULL)));
    }
    this->setPosition(this->getOriginPos());
}

MiniGamePopUp::~MiniGamePopUp(){
    
}

MiniGamePopUp* MiniGamePopUp::getInstance(){
    if(!_instance){
        _instance = new MiniGamePopUp();
    }
    return  _instance;
}

void MiniGamePopUp::update(float dt){
    
}

float MiniGamePopUp::getWidth(){
    return this->getContentSize().width;
}

float MiniGamePopUp::getHeight(){
    return this->getContentSize().height;
}

cocos2d::Size MiniGamePopUp::getSize(){
    return this->getContentSize();
}

bool MiniGamePopUp::init() {
    
    if (!Node::init()) {
        return false;
    }
    return true;
}

void MiniGamePopUp::onEnter() {
    Node::onEnter();
}

void MiniGamePopUp::addEvent(){
    
    bool moved = false;
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p)) {
            this->touchOffset  = this->getPosition() - Director::getInstance()->convertToGL(touch->getLocationInView());
            moved = false;
            return true;
        }
        return false;
    };
    
    listener->onTouchMoved = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        this->setPosition(touch->getLocation() + this->touchOffset);
        moved = true;
    };
    
    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        this->setOriginPos(p);
        if(moved){
            if (this->getChildByTag(TAG_NODE_EMOTICON) == nullptr){
                showObjectThrow();
            }
        }else{
            if (this->getChildByTag(TAG_NODE_EMOTICON) == nullptr){
                showObjectThrow();
            }else {
                hiddenInfoExtend();
            }
        }
        this->runAction(EaseBackOut::create(MoveTo::create(0.2f,p + this->touchOffset)));
    };
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void MiniGamePopUp::hiddenInfoExtend() {
    if (this->getChildByTag(TAG_NODE_EMOTICON) != nullptr) {
        this->removeChildByTag(TAG_NODE_EMOTICON);
    }
}

void MiniGamePopUp::showObjectThrow(){
    //test
    auto common = Common::getInstance();
    
    Node* node_emoticon = Node::create();
    node_emoticon->setTag(TAG_NODE_EMOTICON);
    float PADDING = 15;
    if (1){
        auto sprite_bg_phao = MSprite::create("nem_gach_da/background_nem.png");
        sprite_bg_phao->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_bg_phao->setPosition(Vec2(-PADDING - sprite_bg_phao->getWidth() / 2, this->getHeight() / 2));
        node_emoticon->addChild(sprite_bg_phao);
        
        auto sprite_phao = MButton::create("nem_gach_da/sprite_daibac.png", TAG_CLICK_PHAO);
        sprite_phao->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_phao->setPosition(sprite_bg_phao->getPosition());
        node_emoticon->addChild(sprite_phao);
        
        auto sprite_bg_dep = MSprite::create("nem_gach_da/background_nem.png");
        sprite_bg_dep->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_bg_dep->setPosition(Vec2(this->getWidth() + PADDING + sprite_bg_dep->getWidth() / 2,
                                        this->getHeight() / 2));
        node_emoticon->addChild(sprite_bg_dep);
        
        auto sprite_dep = MButton::create("nem_gach_da/sprite_dep.png", TAG_CLICK_DEP);
        sprite_dep->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_dep->setPosition(sprite_bg_dep->getPosition());
        node_emoticon->addChild(sprite_dep);
        
        float y = sqrt(pow(this->getWidth() / 2 + PADDING + sprite_bg_phao->getWidth() / 2, 2) - pow(this->getWidth() / 2, 2));
        auto sprite_bg_beer = MSprite::create("nem_gach_da/background_nem.png");
        sprite_bg_beer->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_bg_beer->setPosition(Vec2(0, this->getHeight() / 2 + y));
        node_emoticon->addChild(sprite_bg_beer);
        
        auto sprite_beer = MButton::create("nem_gach_da/sprite_beer.png", TAG_CLICK_BEER);
        sprite_beer->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_beer->setPosition(sprite_bg_beer->getPosition());
        node_emoticon->addChild(sprite_beer);
        
        auto sprite_bg_cachua = MSprite::create("nem_gach_da/background_nem.png");
        sprite_bg_cachua->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_bg_cachua->setPosition(Vec2(this->getWidth(), this->getHeight() / 2 + y));
        node_emoticon->addChild(sprite_bg_cachua);
        
        auto sprite_cachua = MButton::create("nem_gach_da/sprite_cachua.png", TAG_CLICK_CACHUA);
        sprite_cachua->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_cachua->setPosition(sprite_bg_cachua->getPosition());
        node_emoticon->addChild(sprite_cachua);
        
        auto sprite_bg_egg = MSprite::create("nem_gach_da/background_nem.png");
        sprite_bg_egg->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_bg_egg->setPosition(Vec2(0, this->getHeight() / 2 - y));
        node_emoticon->addChild(sprite_bg_egg);
        
        auto sprite_egg = MButton::create("nem_gach_da/sprite_trung.png", TAG_CLICK_TRUNG);
        sprite_egg->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_egg->setPosition(sprite_bg_egg->getPosition());
        node_emoticon->addChild(sprite_egg);
        
        auto sprite_bg_rose = MSprite::create("nem_gach_da/background_nem.png");
        sprite_bg_rose->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_bg_rose->setPosition(Vec2(this->getWidth(), this->getHeight() / 2 - y));
        node_emoticon->addChild(sprite_bg_rose);
        
        auto sprite_rose = MButton::create("nem_gach_da/sprite_hoahong.png", TAG_CLICK_ROSE);
        sprite_rose->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sprite_rose->setPosition(sprite_bg_rose->getPosition());
        node_emoticon->addChild(sprite_rose);
        
        if (common->getUserId() == common->getOwnerUserId()){
            //neu la chu phong thi hien thi nut duoi
            auto btn_out = MButton::create("nem_gach_da/btn_extends.png", "Đuổi", 20, TAG_CLICK_USER_OUT);
            btn_out->setTitleFontSize(btn_out->getHeight() / 2);
            btn_out->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
            btn_out->setPosition(Vec2(this->getWidth() / 2, this->getHeight() + 5));
            node_emoticon->addChild(btn_out);
        }
    }
    
    //add nut info
    auto btn_info_user = MButton::create("nem_gach_da/btn_extends.png", "Thông tin", 20, TAG_CLICK_USER_INFO);
    btn_info_user->setTitleFontSize(btn_info_user->getHeight() / 2);
    btn_info_user->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    btn_info_user->setPosition(Vec2(this->getWidth() / 2, -5));
    node_emoticon->addChild(btn_info_user);
    
    this->addChild(node_emoticon);
    //end test
}
