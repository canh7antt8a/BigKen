//
//  ItemCell.cpp
//  MyCards
//
//  Created by hungle on 5/25/16.
//
//

#include "ItemCell.hpp"
#include "UI/MLabel.hpp"
#include "ui/UILoadingBar.h"
#include "Utils/Common.h"
#include "Utils/TLMNConfig.hpp"

ItemCell::ItemCell(){}

ItemCell::~ItemCell(){}

ItemCell* ItemCell::create(int _index, bool passwordRequired, float width, float height, int minBet, int number_user,
	bool isVipRoom, int max_number_user, long long minEnterMoney){
    ItemCell *cell = new ItemCell();
    if (cell && cell->init()){
        cell->autorelease();
    } else{
        CC_SAFE_DELETE(cell);
    }
	float posY = height / 2;
	float sizeText = height / 3;

	//so ban
	auto lb_soban = MLabel::create(cocos2d::StringUtils::format("%d", _index), sizeText);
	lb_soban->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lb_soban->setPosition(Vec2(width / (3 * 6), posY));
	cell->addChild(lb_soban);

	//khoa
	if (passwordRequired){
		auto lock = cocos2d::Sprite::create("icon_lock_mini.png");
		lock->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		lock->setPosition(cocos2d::Vec2(width / (2 * 6), posY));
		cell->addChild(lock);
	}

	//muc cuoc
	auto lb_muccuoc = MLabel::create(Common::getInstance()->convertIntToMoneyView100k(minBet), sizeText);
	lb_muccuoc->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lb_muccuoc->setPosition(cocos2d::Vec2(width / 6 + width / (4 * 6), posY));
	cell->addChild(lb_muccuoc);

	//xu ken
	std::string bg_xuken = isVipRoom ? "sprite_xu_mini.png" : "sprite_ken_mini.png";
	auto sprite_xuken = MSprite::create(bg_xuken);
	sprite_xuken->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	sprite_xuken->setPosition(cocos2d::Vec2(width / 6 + 3 * width / (4 * 6), posY));
	cell->addChild(sprite_xuken);

	//so nguoi choi
	auto sprite = cocos2d::Sprite::create("under_progressbar.png");
	sprite->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprite->setScaleX(((5 * width) / (7 * 3)) / sprite->getContentSize().width);
	sprite->setPosition(cocos2d::Vec2(3 * width / 6, posY));
	cell->addChild(sprite);

	auto loadingBar = ui::LoadingBar::create();
	loadingBar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	loadingBar->setName("LoadingBar");
	loadingBar->setPercent(100 * number_user / max_number_user);
	loadingBar->setScaleX(((5 * width) / (7 * 3)) / sprite->getContentSize().width);
	loadingBar->setPosition(cocos2d::Vec2(3 * width / 6, posY));
	loadingBar->setScale9Enabled(true);

	std::string trangthai_text = "";
	cocos2d::Color3B colorTxt;

	if (number_user / max_number_user >= 1){
		trangthai_text = TABLE_CONTENT_CELL_STATUS_PLAYING;
		loadingBar->loadTexture("inside_progressbar.png");  //max_progressbar.png
		loadingBar->setContentSize(sprite->getContentSize());
		loadingBar->setColor(cocos2d::Color3B::RED);
		colorTxt = cocos2d::Color3B::YELLOW;
	}
	else {
		trangthai_text = TABLE_CONTENT_CELL_STATUS_MIS_SLOT;
		loadingBar->loadTexture("inside_progressbar.png");
		loadingBar->setContentSize(sprite->getContentSize());
		loadingBar->setColor(cocos2d::Color3B::GREEN);
		colorTxt = cocos2d::Color3B::WHITE;
	}
	
	cell->addChild(loadingBar);

	//toi thieu
	auto lb_toithieu = MLabel::create(Common::getInstance()->convertIntToMoneyView100k(minEnterMoney), sizeText);
	lb_toithieu->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lb_toithieu->setPosition(cocos2d::Vec2(4 * width / 6 + width / (4 * 6), posY));
	cell->addChild(lb_toithieu);

	//xuken
	auto sprite_xuken_min = MSprite::create(bg_xuken);
	sprite_xuken_min->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	sprite_xuken_min->setPosition(cocos2d::Vec2(4 * width / 6 + 3 * width / (4 * 6), posY));
	cell->addChild(sprite_xuken_min);

	//trang thai
	auto lb_trangthai = MLabel::create(trangthai_text, sizeText);
	lb_trangthai->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_trangthai->setColor(colorTxt);
	lb_trangthai->setPosition(cocos2d::Vec2(5 * width / 6 + width / (2 * 6), posY));
	cell->addChild(lb_trangthai);
	
	auto labelSoNguoi = MLabel::create(cocos2d::StringUtils::format("%d/%d", number_user, max_number_user), sizeText);
	labelSoNguoi->setAnchorPoint(Point::ANCHOR_MIDDLE);
	labelSoNguoi->setPosition(cocos2d::Vec2(width / 2, posY));
	cell->addChild(labelSoNguoi);
    
    return cell;
}

//void ItemCell::addEvents(int index, bool passwordRequired){
//    auto listener = cocos2d::EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    
//    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
//        cocos2d::Vec2 p = touch->getLocation();
//        cocos2d::Rect rect = this->getBoundingBox();
//        
//        // get the location of the touch on screen
//        auto location = touch->getLocation();
//        // get the location of the touch relative to your button
//        auto nodeSpaceLocation = this->getParent()->convertToNodeSpace(location);
//        // check if touch is inside node's bounding box
//        if (rect.containsPoint(nodeSpaceLocation)) {
//            // node has been touched; add code here
//            return true;
//        }
//        
//        return false;
//    };
//    
//    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
//        CCLOG("touch roomindex : %d",index);
//        CCLOG("%d", Common::getInstance()->getGameTag());
//        CCLOG("%d", Common::getInstance()->getZoneId());
//
//        if (passwordRequired){
//            sceneTable->showPopupPassWord(index);
//        }
//        else {
//            NetworkManager::getInstance()->getEnterRoomMessageFromServer(index, "");
//        }
//    };
//    
//    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
//}

float ItemCell::getWidth(){
    return this->getContentSize().width;
}

float ItemCell::getHeight(){
    return this->getContentSize().height;
}

bool ItemCell::init() {
    if (!Node::init())
        return false;

    return true;
}

void ItemCell::onExit() {
    Node::onExit();
}
