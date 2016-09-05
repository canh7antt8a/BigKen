//
//  CardSprite.cpp

#include "CardSprite.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Utils/SoundManager.h"

using namespace cocos2d;

CardSprite* CardSprite::create(Card card, PositionIndex PositionIndex, float width,CardSpriteEventDelegate* cardEvent) {
    
    CardSprite* cardSprite = CardSprite::create();
    string name = card.getActualName(); 

    cardSprite->setSpriteFrame(name);
    cardSprite->setNumberValue(card.getValue());
    cardSprite->setCard(card);
    cardSprite->setPositionIndex(PositionIndex);
    cardSprite->setScale(width/cardSprite->getWidth());
    
    if (Common::getInstance()->getZoneId() != Common::BACAY_ZONE)  {
        cardSprite->setEvent(cardEvent);
        cardSprite->addEvents();
    }
    
    return cardSprite;
}

CardSprite* CardSprite::createCard(Card card, PositionIndex PositionIndex, float width, CardSpriteEventDelegate* cardEvent) {

    CardSprite* cardSprite = CardSprite::create();
    cardSprite->setSpriteFrame("card_cover.png");
    cardSprite->setNumberValue(card.getValue());
    cardSprite->setFlip(false);
    cardSprite->setCard(card);
    cardSprite->setPositionIndex(PositionIndex);
    cardSprite->setScale(width / cardSprite->getWidth());

    cardSprite->setEvent(cardEvent);
    cardSprite->addEvents();
    
    return cardSprite;
}

void CardSprite::addHidden() {
    hidden = Sprite::create("card_hidden.png");
    hidden->setColor(Color3B::BLACK);
    hidden->setOpacity(100);
    hidden->setScale(this->getWidth()/hidden->getContentSize().width,
                     this->getHeight()/hidden->getContentSize().height);
    hidden->setPosition(Vec2(this->getWidth()/2,this->getHeight()/2));
    this->addChild(hidden);
    hidden->setVisible(false);
}

void CardSprite::showHidden(bool show){
    hidden->setVisible(show);
}

float CardSprite::getWidth(){
    return this->getContentSize().width;
}

float CardSprite::getHeight(){
    return this->getContentSize().height;
}

cocos2d::Size CardSprite::getSize(){
    return this->getContentSize();
}

bool CardSprite::init() {
    
    if (!Sprite::init()) {
        return false;
    }
    
    this->value = "1";
    this->cardState = Idle;
    this->posY = 0;
    
    return true;
}

void CardSprite::onEnter() {
    Sprite::onEnter();
}

void CardSprite::flipCard() {
    if (!isFlip()) {
        auto camera1 = OrbitCamera::create(0.05f, 1, 0, 0.0f, 90.0f, 0, 0);
        auto camera2 = OrbitCamera::create(0.05f, 1, 0, 270.0f, 90.0f, 0, 0);
        auto callbackJump = CallFunc::create([=]() {
            SoundManager::getInstance()->playSound("");
            this->setSpriteFrame(this->getCard().getActualName());
        });
        
        auto sequence = Sequence::create(camera1, callbackJump, camera2, NULL);
        this->runAction(sequence);
        setFlip(true);
    }
}

void CardSprite::addEvents(){
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p)) {
            return true;
        }
        return false;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        CardSprite::touchEvent(touch);
        
        //Am thanh click_card
        SoundManager::getInstance()->playSound(soundTLMN[36]);
        if (Common::getInstance()->getZoneId() == Common::BACAY_ZONE) {
            if (!isFlip()) {
                flipCard();
            }
        }
        else {
            if (cardState == Idle){
                cardState = OnHand;
                cardEvent->onEvent(getNumberValue());
                auto moveTo = MoveTo::create(0.05f, cocos2d::Vec2(this->getPosition().x, getPosY() + 25));
                this->runAction(moveTo);
            }
            else if (cardState == OnHand){
                cardState = Idle;
                auto moveTo = MoveTo::create(0.05f, cocos2d::Vec2(this->getPosition().x, getPosY()));
                this->runAction(moveTo);
            }
        }
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// MOVE

void CardSprite::setPosY(float posY) {
    this->posY = posY;
}

float CardSprite::getPosY(){
    return posY;
}

void CardSprite::setEvent(CardSpriteEventDelegate *cardEvent){
    this->cardEvent = cardEvent;
}

void CardSprite::setSuggest(bool _suggest){
    this->suggest = _suggest;
}

bool CardSprite::getSuggest(){
    return  this->suggest;
}

void CardSprite::setMoveUp(int index){
    cardState = OnHand;
    auto moveTo = MoveTo::create(0.05f+0.08f*index, cocos2d::Vec2(this->getPosition().x,getPosY()+25));
    this->runAction(moveTo);
}

void CardSprite::setMoveDown(){
    cardState = Idle;
    auto moveTo = MoveTo::create(0.05f, cocos2d::Vec2(this->getPosition().x,getPosY()));
    this->runAction(moveTo);
}

// GET & SET

void CardSprite::setState(CardState _state){
    this->cardState = _state;
}

CardState CardSprite::getState(){
    return this->cardState;
}

void CardSprite::setReady(bool _is_ready) {
    this->isReady = _is_ready; 
}

bool CardSprite::getReady() {
    return this->isReady;
}

void CardSprite::setNumberValue(int numberValue){
    this->numberValue = numberValue;
}

int CardSprite::getNumberValue(){
    return this->numberValue;
}
// Touch Event!

void CardSprite::touchEvent(cocos2d::Touch* touch)
{
    CCLOG("touched : %s",getName().c_str());
}

bool CardSprite::isFlip() const {
    return _flip; 
}

void CardSprite::setFlip(bool _flip) {
    this->_flip = _flip; 
}
