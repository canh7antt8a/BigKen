///@ Popup.cpp


#include "Popup.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
#include "Utils/Image.h"

bool Popup::init() {
    if (!Node::init())
        return false;
    this->setAnchorPoint(Point::ZERO);
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    background = LayerColor::create(Color4B(0,0,0,160));
    background->setContentSize(visibleSize);
    background->setPosition(Vec2(origin.x,origin.y));
    background->setOpacity(0);

    this->addChild(background);
    
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, background);

    m_popupLayer = Layer::create();
    m_popupLayer->setAnchorPoint(Vec2::ZERO);
    m_popupLayer->setPosition(Vec2(origin.x,origin.y - visibleSize.height));
    addChild(m_popupLayer);

    disablePopup = true;
    return true;
}

void Popup::disappear() {
    
    auto callDisappear = CallFunc::create([this](){
        background->runAction(FadeTo::create(0.15f, 0));
        disablePopup = true;
        this->removeFromParentAndCleanup(true);
    });
    m_popupLayer->runAction(Sequence::create(MoveTo::create(0.15f,Vec2(origin.x, origin.y - visibleSize.height)),
                                             callDisappear, NULL));
}

void Popup::appear() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto sprite = event->getCurrentTarget();
        Point pt = touch->getLocation();
        Rect recTemp = sprite->getBoundingBox();
        if (!recTemp.containsPoint(pt)) {
            this->disappear();
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, backgroundPopup);
    
    auto callAppear = CallFunc::create([this](){
        background->runAction(FadeTo::create(0.15f, 200));
        disablePopup = false;
    });
    
    m_popupLayer->runAction(Sequence::create(MoveTo::create(0.15f,Vec2(origin.x, origin.y)),
                                             callAppear, nullptr));
    
}

void Popup::onExit() {
    
    Node::onExit();
}
