//
//  BaCayCardSprite.cpp
//  MyCards
//
//  Created by hungle on 8/3/16.
//
//

#include "BaCayCardSprite.hpp"

BaCayCardSprite* BaCayCardSprite::createCard(Card card, float width) {
    
    BaCayCardSprite* cardSprite = BaCayCardSprite::create();
    string name = card.getActualName();
    
    cardSprite->setSpriteFrame(name);
    cardSprite->setCard(card);
    cardSprite->setScale(width/cardSprite->getWidth());
    cardSprite->addEvents();
    
    return cardSprite;
}

void BaCayCardSprite::addEvents(){
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p)) {
            this->touchOffset  = this->getPosition() - p;
            return true;
        }
        return false;
    };
    
    listener->onTouchMoved = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        this->setPositionX(touch->getLocation().x + this->touchOffset.x);
    };
    
    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
    };
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void BaCayCardSprite::removeEvents(){
	_eventDispatcher->removeEventListenersForTarget(this);
}

float BaCayCardSprite::getWidth(){
    return this->getContentSize().width;
}

float BaCayCardSprite::getHeight(){
    return this->getContentSize().height;
}

bool BaCayCardSprite::init(){
    if(!Sprite::init()){
        return false;
    }
    return true;
}

void BaCayCardSprite::onEnter(){
    Sprite::onEnter();
}
