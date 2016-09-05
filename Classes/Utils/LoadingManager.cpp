//
//  LoadingManager.cpp
//  MyCards
//
//  Created by hungle on 6/20/16.
//
//

#include "LoadingManager.hpp"

LoadingManager*  LoadingManager::_instance = 0;

LoadingManager::LoadingManager(){
    Size _visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 _origin = Director::getInstance()->getVisibleOrigin();
    auto darkSprite = LayerColor::create(Color4B(0, 0, 0, 160));
    darkSprite->setContentSize(_visibleSize);
    darkSprite->setPosition(_origin);
    this->addChild(darkSprite);
    
    auto progressbar = Sprite::create("loading.png");
	progressbar->setTag(1);
    progressbar->setPosition(Vec2(_origin.x + _visibleSize.width/2,
                                  _origin.y+ _visibleSize.height/2));
    //progressbar->runAction(RepeatForever::create(RotateBy::create(0.1f, 30)));

	this->addChild(progressbar);
}

LoadingManager::~LoadingManager(){
}

LoadingManager* LoadingManager::getInstance(){
    if(!_instance){
        _instance = new LoadingManager();
    }
    return _instance;
}

bool LoadingManager::init(){
    if(Node::init()){
        return true;
    }
    return false;
}

void LoadingManager::showLoading() {
	if (this->getParent() == nullptr){
		if (this->getChildByTag(1) != nullptr){
			this->getChildByTag(1)->runAction(RepeatForever::create(RotateBy::create(0.1f, 30)));
		}
		
        Director::getInstance()->getRunningScene()->addChild(this, 2);
    }
}

void LoadingManager::hideLoading() {
	CCLOG("hideLoading()");
	if (this->getParent() != nullptr){
		CCLOG("hideLoading compeleted");
		this->removeFromParentAndCleanup(true);
		cocos2d::Director::getInstance()->getEventDispatcher()->setEnabled(true);
	}
}
