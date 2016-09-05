//
//  MauBinhMauBinhCardSprite.cpp
//  MyCards
//
//  Created by hungle on 8/1/16.
//
//

#include "MauBinhCardSprite.hpp"
#include "Utils/SoundManager.h"

using namespace cocos2d;

MauBinhCardSprite* MauBinhCardSprite::createCard(Card card, PosIndex posIndex, float width,CardSpriteMoveDelegate* cardEvent) {
    
    MauBinhCardSprite* cardSprite = MauBinhCardSprite::create();
    string name = card.getActualName();
    cardSprite->setSpriteFrame(name);
    cardSprite->setNumberValue(card.getValue());
    cardSprite->setCard(card);
    cardSprite->setPosIndex(posIndex);
    cardSprite->setScale(width/cardSprite->getWidth());
    cardSprite->setEvent(cardEvent);
    cardSprite->addEvents();
    cardSprite->addHidden();
    return cardSprite;
}

void MauBinhCardSprite::addHidden() {
    hidden = Sprite::createWithSpriteFrameName("card_hidden.png");
    hidden->setColor(Color3B::BLACK);
    hidden->setOpacity(100);
    hidden->setScale(this->getWidth()/hidden->getContentSize().width,
                     this->getHeight()/hidden->getContentSize().height);
    hidden->setPosition(Vec2(this->getWidth()/2,this->getHeight()/2));
    this->addChild(hidden);
    hidden->setLocalZOrder(CARD_UP);
    hidden->setVisible(false);
}

void MauBinhCardSprite::showHidden(bool show){
    hidden->setVisible(show);
}

float MauBinhCardSprite::getWidth(){
    return this->getContentSize().width;
}

float MauBinhCardSprite::getHeight(){
    return this->getContentSize().height;
}

cocos2d::Size MauBinhCardSprite::getSize(){
    return this->getContentSize();
}

bool MauBinhCardSprite::init() {
    
    if (!Sprite::init()) {
        return false;
    }
    
    this->value = "1";
    this->cardState = Idle;
    this->posY = 0;
    
    return true;
}

void MauBinhCardSprite::onEnter() {
    Sprite::onEnter();
}

Point touchToPoint(Touch* touch){
    return Director::getInstance()->convertToGL(touch->getLocationInView());
}

void MauBinhCardSprite::addEvents(){
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p)) {
            this->touchOffset  = this->getPosition() - touchToPoint(touch);
            this->setLocalZOrder(CARD_UP);
            return true;
        }
        return false;
    };

    listener->onTouchMoved = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        this->setPosition(touch->getLocation() + this->touchOffset);
    };
    
    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        this->cardEvent->onEventCardSpriteMove(getNumberValue(),p.x,p.y);
        this->setLocalZOrder(CARD_DOWN);
    };
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// MOVE

void MauBinhCardSprite::setPosY(float posY){
    this->posY = posY;
}

void MauBinhCardSprite::setEvent(CardSpriteMoveDelegate *cardEvent){
    this->cardEvent = cardEvent;
}

void MauBinhCardSprite::setSuggest(bool _suggest){
    this->suggest = _suggest;
}

bool MauBinhCardSprite::getSuggest(){
    return  this->suggest;
}

void MauBinhCardSprite::setMoveUp(int index){
    cardState = OnHand;
    auto moveTo = MoveTo::create(0.05f+0.08f*index, cocos2d::Vec2(this->getPosition().x,posY+25));
    this->runAction(moveTo);
}

void MauBinhCardSprite::setMoveDown() {
    cardState = Idle;
    auto moveTo = MoveTo::create(0.05f, cocos2d::Vec2(this->getPosition().x,posY));
    this->runAction(moveTo);
}

// GET & SET

void MauBinhCardSprite::setState(CardState _state){
    this->cardState = _state;
}

CardState MauBinhCardSprite::getState(){
    return this->cardState;
}

void MauBinhCardSprite::setReady(bool _is_ready) {
    this->isReady = _is_ready;
}

bool MauBinhCardSprite::getReady() {
    return this->isReady;
}

void MauBinhCardSprite::setNumberValue(int numberValue){
    this->numberValue = numberValue;
}

int MauBinhCardSprite::getNumberValue(){
    return this->numberValue;
}
// Touch Event!

void MauBinhCardSprite::touchEvent(cocos2d::Touch* touch)
{
    CCLOG("touched : %s",getName().c_str());
}
