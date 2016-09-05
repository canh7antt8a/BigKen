#include "WaitingPlayer.hpp"

using namespace cocos2d;

bool WaitingPlayer::init(){
    if (!Node::init())
        return false;
    
    this->setAnchorPoint(Point::ZERO);

    avatar = MSprite::create("avatar0.png");
	avatar->setScale(0.5f);
	avatar->setContentSize(avatar->getContentSize()*0.5f);
    this->addChild(avatar);
    
	name = MLabel::create("z", avatar->getHeight()/5);
    name->setAlignment(TextHAlignment::CENTER);
    this->addChild(name);
    
    return true;
}

void WaitingPlayer::setAvatar(std::string playerName, int index){
	int avatar_id = index;
	if (index < 100000){
		avatar_id = 0;
	}
	avatar->setTexture(StringUtils::format("avatar%d.png", avatar_id));
	name->setString(playerName);
}

void WaitingPlayer::setPositionAvatar(Vec2 origin, int position){
	avatar->setPosition(Vec2(origin.x + position, origin.y + 5));
	name->setPosition(Vec2(avatar->getPosition().x + avatar->getWidth()*0.5f / 2-name->getWidth()/2,
		avatar->getPosition().y+avatar->getHeight()*0.5f + 5));
}

MSprite* WaitingPlayer::getAvatar(){
	return avatar;
}

void WaitingPlayer::onExit() {
    Node::onExit();
}
