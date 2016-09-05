//
//  MCircleBar.cpp
//  MyCards
//
//  Created by hungle on 5/4/16.
//
//

#include "MCircleBar.hpp"
#include "UI/MLabel.hpp"

#define pExpRedBarBG "round.png"

#define kRedBarTag 1
#define effectTag 2

using namespace cocos2d;

MCircleBar *MCircleBar::createWithPer(float percent,float time) {
    MCircleBar *bar = new MCircleBar();
    if (bar && bar->initWithPer(percent,time)) {
        bar->autorelease();
        return bar;
    }
    CC_SAFE_DELETE(bar);
    return NULL;
}

bool MCircleBar::initWithPer(float percent,float time) {
    
    if (!Sprite::init()) {
        return false;
    }
    makeProgressBar(percent,time);
    
    return true;
}

void MCircleBar::makeProgressBar(float percent,float time) {
    Size size = this->getContentSize();
    
    auto redBar = Sprite::create(pExpRedBarBG);
	this->setContentSize(redBar->getContentSize());
    
    auto pt = ProgressTimer::create(redBar);
    pt->setType(ProgressTimer::Type::RADIAL);
    pt->setBarChangeRate(Vec2(1, 0));
    pt->setTag(kRedBarTag);
    addChild(pt);
    pt->setPosition(Vec2(size.width/2, redBar->getContentSize().height/2));
    
    auto effect = Sprite::create("effect_circleBar.png");
    effect->setPosition(Vec2(size.width/2, redBar->getContentSize().height/2));
    effect->setTag(effectTag);
    addChild(effect);
    
    upDatePer(percent,time);
}

void MCircleBar::setBarValue(int divisorValue, int dividendValue) {}

void MCircleBar::upDatePer(float percent,float time) {
    //int times = percent/100;
    ProgressTimer *redBarProgress = dynamic_cast<ProgressTimer *>(this->getChildByTag(kRedBarTag));
	redBarProgress->stopAllActions();
    
    Sprite *effect = (Sprite*)this->getChildByTag(effectTag);
    effect->stopAllActions();
    effect->setRotation(0);
    if(percent == 0){
        effect->setVisible(false);
    }else{
        effect->setVisible(true);
    }
    
    Vector<FiniteTimeAction*> rotateArr;
    auto rotateFrom = RotateBy::create(time, 360*percent/100.0f);
    rotateArr.pushBack(rotateFrom);
    
    auto *rotateTo = RotateBy::create(time,0);
    rotateArr.pushBack(rotateTo);
    effect->runAction(Sequence::create(rotateArr));
    
    //===========
	Vector<FiniteTimeAction*> progressArr;
	ProgressFromTo *progressFrom = ProgressFromTo::create(time, 0.0, percent);
	progressArr.pushBack(progressFrom);

	ProgressFromTo *progressTo = ProgressFromTo::create(time, 0.0, 0.0);
	progressArr.pushBack(progressTo);

	redBarProgress->runAction(Sequence::create(progressArr));
        
}
