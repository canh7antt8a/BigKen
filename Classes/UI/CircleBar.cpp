//
//  CircleBar.cpp
//  MyCards
//
//  Created by hungle on 4/20/16.
//
//

#include "CircleBar.hpp"

bool CircleBar::init() {
    if (!Node::init())
        return false;
    
    this->setAnchorPoint(Point::ZERO);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    background = MSprite::create("bg.png",visibleSize);
    background->setPosition(Point::ZERO);
    background->setColor(Color3B(0,0,0));
    background->setOpacity(0);
    
    progress = Sprite::create("loading.png");
    progress->setPosition(visibleSize.width/2,visibleSize.height/2);
    
    m_popupLayer = Layer::create();
    m_popupLayer->setAnchorPoint(Vec2::ZERO);
    m_popupLayer->setPosition(Vec2(origin.x,
                                   origin.y+visibleSize.height));
    addChild(m_popupLayer);
    
    m_popupLayer->addChild(background);
    m_popupLayer->addChild(progress);    
    
    return true;
}

void CircleBar::disappear() {
    background->setOpacity(0);
    progress->stopAllActions();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_popupLayer->runAction(MoveTo::create(0.0f,Vec2(origin.x, origin.y+background->getContentSize().height)));
}

void CircleBar::appear(float time) {
    auto callAppear = CallFunc::create([this](){
        background->setOpacity(200);
    });
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_popupLayer->runAction(Sequence::create(MoveTo::create(0.0f,Vec2(origin.x,origin.y)),
                                             callAppear, nullptr));
    if(time ==0){
        progress->runAction(RepeatForever::create(RotateBy::create(0.2f, 40.0f)));
    }else{
        float count = time / 0.2f;
        progress->runAction(Repeat::create(RotateBy::create(0.2f, 40.0f),count));
    }
    
}

void CircleBar::onExit() {
    Node::onExit();
}