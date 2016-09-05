#include "XocDiaAvatar.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/SoundManager.h"
#include <math.h>

using namespace cocos2d::ui;

#define PADDING 15

bool XocDiaAvatar::init(){
    
    this->setAnchorPoint(Point::ZERO);
    
    circleBar = MCircleBar::createWithPer(0, 0);
    this->addChild(circleBar);

    background = MSprite::create("sprite_avatar_background.png");
    background->setPosition(Point::ZERO);
    this->addChild(background);
    
    avatar = MSprite::create("null_bg.png", cocos2d::Size(background->getWidth(), background->getWidth()));
    avatar->setPosition(0,(background->getHeight() / 2 - background->getWidth() / 2));
    this->addChild(avatar);
    
    name = MLabel::create("z",background->getWidth()/5);
    name->setPosition(Vec2(background->getWidth()/2-name->getWidth()/2,
                           background->getHeight()+5));
    name->setAlignment(TextHAlignment::CENTER);
    this->addChild(name);

	under_money = MSprite::create("sprite_diem.png");
	under_money->setPosition(Vec2(background->getWidth() / 2 - under_money->getWidth() / 2,
		-5 - under_money->getHeight()));
	this->addChild(under_money);

	money = MLabel::create("10$", background->getWidth() / 6);
	money->setPosition(Vec2(background->getWidth() / 2 - money->getWidth() / 2,
		under_money->getPosition().y + under_money->getHeight() / 2 - money->getHeight() / 2 + 5));
	money->setAlignment(TextHAlignment::CENTER);
	this->addChild(money);
    
    this->setContentSize(background->getContentSize());

	this->addEvents();

    return true;
}

void XocDiaAvatar::loadAvatar(int index, std::string id, std::string _name, std::string _money, int roomIndex, int minBet) {
    this->roomIndex = roomIndex;
    std::stringstream ss(id);
    ss >> player_id;

    float scale = background->getWidth() / circleBar->getContentSize().width * 1.2;
    circleBar->setScale(scale);
    circleBar->setPosition(Vec2(background->getWidth() / 2 + circleBar->getContentSize().width*scale / 2,
        background->getHeight() / 2));

    avatar->setTexture(StringUtils::format("avatar%d.png", index));
    avatar->setScale(background->getWidth() / avatar->getWidth());
    
    name->setString(_name);
    name->setPosition(Vec2(background->getWidth()/2-name->getWidth()/2,
                           background->getHeight()+5));
    
    money->setString(_money);
    money->setPosition(Vec2(background->getWidth()/2-money->getWidth()/2,
                            under_money->getPosition().y+under_money->getHeight()/2-money->getHeight()/2));

}

void XocDiaAvatar::setAvatarPostion(int index, Vec2 origin, Size visibleSize){
    Vec2 pos = Vec2(0, 0);
    Size size = Size(visibleSize.width*0.75f,visibleSize.width*0.75f*461/955.0f);
    posIndex = index;
    switch (index) {
		case 9:
			pos = Vec2(-size.width*0.52f - 0.5f * this->getContentSize().width, - 1.3f * this->getContentSize().height);
			break;
		case 8:
			pos = Vec2(-size.width*0.52f - 0.5f * this->getContentSize().width, 0.5f * this->getContentSize().height);
			break;
        case 7:
			pos = Vec2(-size.width / 3 - this->getContentSize().width - 5, size.height / 2 - this->getContentSize().height * 0.7f);
            break;
        case 6:
			pos = Vec2(-size.width / 7 - this->getContentSize().width, size.height / 2 - this->getContentSize().height * 0.5f);
            break;
        case 5:
			pos = Vec2(size.width / 7, size.height / 2 - this->getContentSize().height * 0.5f);
            break;
        case 4:
            pos = Vec2(size.width / 3.2f, size.height/2-this->getContentSize().height * 0.65f);
            break;
        case 3:
			pos = Vec2(size.width*0.52f - 0.5f * this->getContentSize().width, 0.7f * this->getContentSize().height);
            break;
        case 2:
			pos = Vec2(size.width*0.52f - 0.5f * this->getContentSize().width, -this->getContentSize().height);
            break;
        case 1:
			pos = Vec2(-this->getContentSize().width - 10, -size.height / 2 - 0.65f * this->getContentSize().height);
            break;
        case 0:
			pos = Vec2(-size.width*0.25f - this->getContentSize().width / 2, -size.height / 2 - 0.65f * this->getContentSize().height);
            break;
        default:
            break;
    }
    this->setPosition(pos + Vec2(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height/2));
}

void XocDiaAvatar::onExit() {
    Avatar::onExit();
}