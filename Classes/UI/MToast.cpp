//
//  MToast.cpp
//  MyCards
//
//  Created by hungle on 6/7/16.
//
//

#include "MToast.hpp"

bool MToast::init() {
    if(!LayerColor::initWithColor(Color4B(0, 0, 0, 0))) {
        return false;
    }
    this->initUI();
    this->onEnter();
    return true;
}

void MToast::onEnter() {
    LayerColor::onEnter();
}

void MToast::onExit() {
    LayerColor::onExit();
}

MToast::~MToast() {
    this->onExit();
}

void MToast::show(const char *message, float duration) {
    labelMessasge->setString(message);

	if (labelMessasge->getWidth() >= (2 * spriteBackground->getContentSize().width - 2 * 20)){
		labelMessasge->setWidth(2 * spriteBackground->getContentSize().width - 2 * 20);
	}

	labelMessasge->setLineBreakWithoutSpace(true);
	labelMessasge->enableWrap(true);

    spriteBackground->setContentSize(Size(labelMessasge->getContentSize().width + 40,
                                          labelMessasge->getContentSize().height + 20));
    spriteBackground->setPosition(Vec2(0,0 + spriteBackground->getContentSize().height));
    labelMessasge->setPosition(Vec2(spriteBackground->getContentSize().width * 0.5,
                                    spriteBackground->getContentSize().height * 0.5));
    
    labelMessasge->runAction(Sequence::create(FadeIn::create(0.3f), DelayTime::create(duration),
                                              FadeOut::create(0.3f), NULL));
    auto callback = CallFunc::create([this]() {
        this->onHideToast();
    });
    spriteBackground->runAction(Sequence::create(FadeIn::create(0.3f), DelayTime::create(duration),
                                                 FadeOut::create(0.3f), callback, NULL));
}

void MToast::showWithWrap(const char *message, float duration){
	labelMessasge->setString(message);
	if (labelMessasge->getWidth() >= (spriteBackground->getContentSize().width - 2 * 20)){
		labelMessasge->setWidth(spriteBackground->getContentSize().width - 2 * 20);
	}
	
	labelMessasge->setLineBreakWithoutSpace(true);
	labelMessasge->enableWrap(true);

	spriteBackground->setContentSize(Size(labelMessasge->getContentSize().width + 40,
		labelMessasge->getContentSize().height + 20));
	//spriteBackground->setPosition(Vec2(0, 0 + spriteBackground->getContentSize().height));
	labelMessasge->setPosition(Vec2(spriteBackground->getContentSize().width * 0.5,
		spriteBackground->getContentSize().height * 0.5));

	labelMessasge->runAction(Sequence::create(FadeIn::create(0.3f), DelayTime::create(duration),
		FadeOut::create(0.3f), NULL));
	auto callback = CallFunc::create([this]() {
		this->onHideToast();
	});
	spriteBackground->runAction(Sequence::create(FadeIn::create(0.3f), DelayTime::create(duration),
		FadeOut::create(0.3f), callback, NULL));
}

void MToast::initParams() {
	spriteBackground->runAction(Sequence::create(MoveBy::create(0.05f, Vec2(-20, 0)), MoveBy::create(0.1f, Vec2(40, 0)),
		MoveBy::create(0.05f, Vec2(-20, 0)), NULL));
}

void MToast::initUI() {
    spriteBackground = ui::Scale9Sprite::create("toast.png");
    spriteBackground->setAnchorPoint(Vec2(0.5, 0.5));
    spriteBackground->setCapInsets(Rect(10,10, spriteBackground->getBoundingBox().size.width - 20,
                                        spriteBackground->getBoundingBox().size.height - 20));
    labelMessasge = MLabel::create("", 28,TOAST_TEXT_COLOR);
    labelMessasge->setAnchorPoint(Vec2(0.5f,0.5f));
    labelMessasge->setAlignment(TextHAlignment::CENTER);
    spriteBackground->addChild(labelMessasge);
    this->addChild(spriteBackground);
}

ui::Scale9Sprite* MToast::getBackground(){
	return spriteBackground;
}

MLabel* MToast::getLabelMessage(){
	return labelMessasge;
}

void MToast::onHideToast() {
    this->removeFromParentAndCleanup(true);
}
