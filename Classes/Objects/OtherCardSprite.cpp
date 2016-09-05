//
//  OtherCardSprite.cpp
//  MyCards
//
//  Created by hungle on 5/5/16.
//
//

#include "OtherCardSprite.hpp"
#include "Utils/SoundManager.h"
#include "Utils/Common.h"

using namespace cocos2d;
#define CARD_RATIO 1.3396
#define CARD_HIDDEN 1

//=================== Phom

OtherCardSprite* OtherCardSprite::createCardCover(float width) {
    OtherCardSprite* cardSprite = OtherCardSprite::create();
    cardSprite->setSpriteFrame("card_cover.png");
    cardSprite->setAnchorPoint(Vec2(0,0));
    cardSprite->setScale(width/cardSprite->getWidth());
    cardSprite->setContentSize(Size(width,width*CARD_RATIO));
    cardSprite->addHidden();
    return cardSprite;
}

void OtherCardSprite::setMoveFromToPhom(Vec2 pos1,Vec2 pos2) {
    
    this->setPosition(pos1);
    auto moveto = MoveTo::create(0.25f,pos2);
    auto sequene = Sequence::create(moveto,RemoveSelf::create(), NULL);
    this->runAction(sequene);
}

void OtherCardSprite::setMoveToCenterPhom(int indexUser,int indexCard,Vec2 origin,Size visibleSize,float cardWidth) {
    float x = visibleSize.width/2 + getCardPostionPhom(indexUser,indexCard,cardWidth).x;
    float y = visibleSize.height/2 + getCardPostionPhom(indexUser,indexCard,cardWidth).y;
    auto pos = Vec2(origin.x+x,origin.y+y);
    auto moveto = MoveTo::create(0.25f,pos);
    auto scale = ScaleBy::create(0.25f,0.8f);
    auto sequene = Spawn::create(moveto,scale,NULL);
    this->runAction(sequene);
}

void OtherCardSprite::setMoveHaBaiPhom(Vec2 pos, int indexUser,int indexCard,int sizePhom,int indexPhom,
                                       Vec2 origin,Size visibleSize,float cardWidth,bool animate){
    auto posx = Vec2(0,(sizePhom - indexPhom)*cardWidth*CARD_RATIO*0.3f) + Vec2(pos.x  + (indexCard - 2) *cardWidth*0.5f,pos.y);
    /*int time = animate ? 0.1f : 0;
    auto moveto = MoveTo::create(time,posx);
    auto scale = ScaleBy::create(0,0.8f);
    auto sequene = Spawn::create(moveto,scale,NULL);
    this->runAction(sequene);*/
    this->setPosition(posx);
    auto scale = ScaleBy::create(0,0.8f);
    this->runAction(scale);
    
}

void OtherCardSprite::setMoveGuiBaiPhom(Vec2 pos,float posY,int indexUser,int indexCard,int sizePhom,int indexPhom,Vec2 origin,Size visibleSize,float cardWidth){
    auto posx = Vec2(0,posY) + Vec2(pos.x  + (indexCard - 2) *cardWidth*0.5f,0);
    this->setPosition(posx);
    auto scale = ScaleBy::create(0,0.8f);
    this->runAction(scale);
    
}

Vec2 OtherCardSprite::getCardCoverPostionPhom(int index,float cardWidth,Size visibleSize){
    Vec2 pos;
    if(index == 1){
        pos = Vec2(visibleSize.width - 3*cardWidth,visibleSize.height/2);
    }else if(index == 2){
        pos = Vec2(visibleSize.width/2,visibleSize.height - cardWidth*CARD_RATIO*2/3.0);
    }else if(index == 3){
        pos = Vec2(3*cardWidth,visibleSize.height/2);
    }else{
        pos = Vec2(3*cardWidth, cardWidth * CARD_RATIO * 3);
    }
    return pos;
}

Vec2 OtherCardSprite::getCardPostionPhom(int indexUser,int indexCard,float cardWidth){
    Vec2 pos;
    if(indexUser == 1){
        pos = Vec2(cardWidth * 2+indexCard*cardWidth * 0.5f,-cardWidth * CARD_RATIO * 0.5f);
    }else if(indexUser == 2){
        pos = Vec2(-cardWidth + indexCard * cardWidth * 0.5f,cardWidth * CARD_RATIO * 0.5f);
    }else if(indexUser == 3){
        pos = Vec2(-cardWidth * 2 - cardWidth * 0.5f * 4 + indexCard*cardWidth * 0.5f,-cardWidth * CARD_RATIO * 0.5f);
    }else{
        pos = Vec2(-cardWidth + indexCard*cardWidth * 0.5f,-cardWidth * CARD_RATIO * 1.39f);
    }
    return pos;
}

//======== Tien len mien nam

OtherCardSprite* OtherCardSprite::create(int value, float width) {
    OtherCardSprite* cardSprite = OtherCardSprite::create();
    cardSprite->setSpriteFrame("card_cover.png");
    cardSprite->setValue(value);
    cardSprite->setScale(width/cardSprite->getWidth());
    cardSprite->setContentSize(Size(width,width*CARD_RATIO));
    cardSprite->addHidden();
    return cardSprite;
}

OtherCardSprite* OtherCardSprite::createSelf(int value, float width) {
    OtherCardSprite* cardSprite = OtherCardSprite::create();
    cardSprite->setSpriteFrame(cardSprite->getSpriteName(value));
    cardSprite->setAnchorPoint(Vec2(0,0));
    cardSprite->setValue(value);
    cardSprite->setScale(width/cardSprite->getWidth());
    cardSprite->setContentSize(Size(width,width*CARD_RATIO));
    cardSprite->addHidden();
    return cardSprite;
}


void OtherCardSprite::setMoveToCenter(int sizeIndex,int index,Vec2 origin,
                                      Size visibleSize,float cardWidth,int randomX){
    
    float x = visibleSize.width/2 + randomX - this->getWidth()/2;
    if(sizeIndex>1) {
        x = visibleSize.width/2+ (index - (float)(sizeIndex-1)/2)*cardWidth + randomX;
    }
    float y = visibleSize.height/2 - this->getHeight()/2;
    auto pos = Vec2(origin.x+x,origin.y+y);
    auto moveto = MoveTo::create(0.25f,pos);
    auto rotage = RotateBy::create(0.2f,RandomHelper::random_int(-10, 10));
    auto camera1 = OrbitCamera::create(0.05f, 1, 0, 0.0f, 90.0f, 0, 0);
    auto camera2 = OrbitCamera::create(0.05f, 1, 0, 270.0f, 90.0f, 0, 0);
    auto callbackJump = CallFunc::create([=]() {
        SoundManager::getInstance()->playSound("");
        this->setSpriteFrame(this->getSpriteName(this->getValue()));
        
        this->setPosition(Vec2(pos.x+cardWidth/4,
                               pos.y+this->getHeight()*cardWidth/this->getWidth()/4));
    });
    auto sequene = Sequence::create(moveto,rotage,camera1,callbackJump,camera2, NULL);
    this->runAction(sequene);
}

void OtherCardSprite::setMoveToCenterSelf(int sizeIndex,int index,Vec2 origin,
                                          Size visibleSize,float cardWidth,int randomX){
    
    float x = visibleSize.width/2 + randomX - this->getWidth()/2;
    if(sizeIndex>1) {
        x = visibleSize.width/2+ (index - (float)(sizeIndex-1)/2)*cardWidth + randomX;
    }
    float y = visibleSize.height/2 - this->getHeight()/2;
    auto pos = Vec2(origin.x+x,origin.y+y);
    auto moveto = MoveTo::create(0.25f,pos);
    auto rotage = RotateBy::create(0.2f,RandomHelper::random_int(-10, 10));
    auto sequene = Sequence::create(moveto,rotage, NULL);
    this->runAction(sequene);
}

void OtherCardSprite::addHidden() {
    auto hidden = Sprite::createWithSpriteFrameName("card_hidden.png");
    hidden->setTag(CARD_HIDDEN);
    hidden->setColor(Color3B::BLACK);
    hidden->setOpacity(100);
    hidden->setAnchorPoint(Point::ZERO);
    this->addChild(hidden);
    hidden->setVisible(false);
}

void OtherCardSprite::addEvent(int posIndex){
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
        
    };
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void OtherCardSprite::showHidden(bool show){
    if(this->getChildByTag(CARD_HIDDEN) != nullptr){
        auto sprite = this->getChildByTag(CARD_HIDDEN);
        sprite->setVisible(show);
    }
    
}

void OtherCardSprite::onEnter(){
    Sprite::onEnter();
}

float OtherCardSprite::getWidth(){
    return this->getContentSize().width;
}

float OtherCardSprite::getHeight(){
    return this->getContentSize().height;
}

void OtherCardSprite::setValue(int _value){
    value = _value;
}

int OtherCardSprite::getValue(){
    return value;
}

bool OtherCardSprite::init() {
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

string OtherCardSprite::getSpriteName(int value) {
    int nameValue = value;
    if (Common::getInstance()->getZoneId() == 4) {
        nameValue = nameValue - 8;
        if (nameValue < 1)
            nameValue = nameValue + 52;
    } else if (Common::getInstance()->getZoneId() == Common::BACAY_ZONE) {
        nameValue = value - 8;
        if (nameValue < 1) nameValue = nameValue + 52;
        if (nameValue % 4 == 0) {
            nameValue--;
        }
        else if (nameValue % 4 == 3) {
            nameValue++;
        }
    }
    else if (Common::getInstance()->getZoneId() == Common::MAUBINH_ZONE) {
        nameValue = value - 4;
        if (nameValue < 1) nameValue = nameValue + 52;
    }
    return StringUtils::format("%02dx.png", nameValue);
}
