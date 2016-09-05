//
//  ItemShowGame.cpp
//  MyCards
//
//  Created by hungle on 8/5/16.
//
//

#include "ItemShowGame.hpp"

ItemShowGame* ItemShowGame::create(std::string texture,int index,cocos2d::Size size,CardSpriteEventDelegate *cardEvent){
    ItemShowGame* cardSprite = ItemShowGame::create();
    cardSprite->setTexture(texture);
    cardSprite->setScale(size.width/cardSprite->getContentSize().width);
    //cardSprite->setContentSize(size);
    cardSprite->setTag(index);
    cardSprite->setEvent(cardEvent);
    cardSprite->addEvents();
    return cardSprite;
}

bool ItemShowGame::init() {
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

void ItemShowGame::addEvents(){
    
    
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    //listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p)) {
            this->touchEvent(touch);
            return true;
        }
        return false;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        cardEvent->onEvent(this->getTag());
    };
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void ItemShowGame::setEvent(CardSpriteEventDelegate *cardEvent) {
    this->cardEvent = cardEvent;
}

void ItemShowGame::onEnter(){
    Sprite::onEnter();
}

void ItemShowGame::touchEvent(cocos2d::Touch *touch){
    
    auto scale = cocos2d::ScaleTo::create(0, 1);
    auto zoomOut = cocos2d::ScaleTo::create(0.1f,1.2f);
    auto zoomIn = cocos2d::ScaleTo::create(0.2f,0.9f);
    auto zoom = cocos2d::ScaleTo::create(0.05f, 1.0f);
    this->runAction(cocos2d::Sequence::create(scale,zoomOut,zoomIn,zoom,NULL));
}
