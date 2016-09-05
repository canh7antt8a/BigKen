//
//  AnimationManager.cpp
//  MyCards
//
//  Created by hungle on 6/30/16.
//
//

#include "AnimationManager.hpp"
#include "cocos2d.h"

AnimationManager*  AnimationManager::_instance = 0;

AnimationManager::AnimationManager(){
    Size _visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 _origin = Director::getInstance()->getVisibleOrigin();
    auto darkSprite = LayerColor::create(Color4B(0, 0, 0, 160));
    darkSprite->setContentSize(_visibleSize);
    darkSprite->setPosition(_origin);
    this->addChild(darkSprite);
    
}

void AnimationManager::show(int index,Size _visibleSize) {
    
    std::vector<std::string> list = {"win_background.png","vuotsang.png","gold_%d.png","toitrang.png"};
    
    auto winBackground = Sprite::create(list[0]);
    winBackground->setScale(2, 1);
    winBackground->setPosition(Vec2(_visibleSize.width/2,_visibleSize.height/2));
    this->addChild(winBackground);
    
    auto vuotsangLeft = Sprite::create(list[1]);
    vuotsangLeft->setPosition(Vec2(_visibleSize.width/2-winBackground->getContentSize().width/2,
                                   _visibleSize.height/2+ winBackground->getContentSize().height/2));
    vuotsangLeft->runAction(Sequence::create(MoveBy::create(2, Vec2(winBackground->getContentSize().width,0)),RemoveSelf::create(),NULL));
    this->addChild(vuotsangLeft);
    
    auto vuotsangRight = Sprite::create(list[1]);
    vuotsangRight->setPosition(Vec2(_visibleSize.width/2+winBackground->getContentSize().width/2,
                                    _visibleSize.height/2- winBackground->getContentSize().height/2));
    vuotsangRight->runAction(Sequence::create(MoveBy::create(2, Vec2(-winBackground->getContentSize().width,0)),RemoveSelf::create(),NULL));
    this->addChild(vuotsangRight);
    
    frames.clear();
    anims.clear();
    _anims.clear();
    
    frames = getAnimation(list[2].c_str(),6);
    
    for(int i=0;i<6;i++) {
        auto sprite = Sprite::createWithSpriteFrame(frames.front());
        sprite->setPosition(Vec2(_visibleSize.width/2,_visibleSize.height/2));
        anims.push_back(sprite);
        this->addChild(anims[i]);
    }
    for(int i=0;i<6;i++) {
        auto sprite = Sprite::createWithSpriteFrame(frames.front());
        sprite->setPosition(Vec2(_visibleSize.width/2,_visibleSize.height/2));
        _anims.push_back(sprite);
        this->addChild(_anims[i]);
    }
    
    auto toitrang = Sprite::create(list[3]);
    toitrang->setPosition(Vec2(_visibleSize.width/2,_visibleSize.height/2));
    this->addChild(toitrang);
    
    CCLOG("Count first");
    isRunning = true;
    count =0;
    deltaTime = 0;
    _deltaTime = 0;
    
    this->scheduleUpdate();
}

void AnimationManager::update(float delta){
    if(isRunning){
        _deltaTime +=delta;
        if(_deltaTime > 3) {
            _deltaTime = 0;
            this->removeAllChildren();
            this->removeFromParentAndCleanup(true);
            isRunning = false;
        }
        if(count < 6){
            deltaTime+=delta;
        }
        if(deltaTime>0.2f) {
            deltaTime = 0;
            Size _visibleSize = Director::getInstance()->getVisibleSize();
            auto animation = Animation::createWithSpriteFrames(frames, 1.0f/10);
            auto repeat =  RepeatForever::create(Animate::create(animation));
            auto _animation = Animation::createWithSpriteFrames(frames, 1.0f/10);
            auto _repeat =  RepeatForever::create(Animate::create(_animation));
            
            auto move = Sequence::create(MoveBy::create(0.8f,Vec2(_visibleSize.width/3 - count*10,0)),
                                         FadeOut::create(0.2f*count),NULL);
            auto _move = Sequence::create(MoveBy::create(0.8f,Vec2(-_visibleSize.width/3 + count*10,0)),
                                          FadeOut::create(0.2f*count),NULL);
            
            auto call = CallFunc::create([=](){
                isRunning = false;
                this->removeAllChildren();
                this->removeFromParentAndCleanup(true);
            });
            auto end = Sequence::create(FadeOut::create(0.8f),call,NULL);
            auto _end = Sequence::create(FadeOut::create(0.8f),call,NULL);
            anims[count]->runAction(repeat);
            _anims[count]->runAction(_repeat);
            if(count == 5){
                anims[count]->runAction(end);
                _anims[count]->runAction(_end);
            }else{
                anims[count]->runAction(move);
                _anims[count]->runAction(_move);
            }
            
            count++;
        }
    }
    
}

AnimationManager::~AnimationManager(){
}

Vector<SpriteFrame*> AnimationManager::getAnimation(const char *format, int count) {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++) {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

AnimationManager* AnimationManager::getInstance(){
    if(!_instance){
        _instance = new AnimationManager();
    }
    return _instance;
}

bool AnimationManager::init(){
    if(Node::init()){
        return true;
    }
    return false;
}
