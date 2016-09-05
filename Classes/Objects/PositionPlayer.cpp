#include "PositionPlayer.h"
#include "Utils/NetworkManager.h"

using namespace cocos2d;


bool PositionPlayer::init(){
	if (!Sprite::init()){
		return false;
	}
	
	this->setTexture("add_position.png");
	this->setScale(0.8);
	this->addEvent();

	return true;
}

void PositionPlayer::addEvent(){
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		cocos2d::Vec2 p = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p)) {
			return true; // to indicate that we have consumed it.
		}

		return false;
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		NetworkManager::getInstance()->getReadyToPlayMessageFromServer(roomIndex, tableIndex);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void PositionPlayer::setPositionPlayer(int roomIndex, int tableIndex, Vec2 origin, Size visibleSize){
	Vec2 pos = Vec2(0, 0);
	this->tableIndex = tableIndex;
	this->roomIndex = roomIndex;

	switch (tableIndex) {
	case 3:
		pos = Vec2(origin.x + 10, origin.y + visibleSize.height / 2 - this->getContentSize().height / 2);
		break;
	case 2:
		pos = Vec2(origin.x + visibleSize.width / 2 - this->getContentSize().width - 10,
			origin.y + visibleSize.height - this->getContentSize().height - 10);
		break;
	case 1:
		pos = Vec2(origin.x + visibleSize.width - this->getContentSize().width - 10,
			origin.y + visibleSize.height / 2 - this->getContentSize().height / 2);
		break;
	case 0:
		pos = Vec2(origin.x + 10, origin.y + 10 + this->getContentSize().height / 2);
		break;
	default:
		break;
	}

	this->setPosition(pos);
}