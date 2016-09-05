//
//  ItemCell.cpp
//  MyCards
//
//  Created by hungle on 5/25/16.
//
//

#include "ItemMoneyLog.hpp"
#include "UI/MLabel.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"

#define PADDING_ITEM 25

ItemMoneyLog::ItemMoneyLog(){}

ItemMoneyLog::~ItemMoneyLog(){}

ItemMoneyLog* ItemMoneyLog::createMoneyLog(BINMoneyLog moneyLog, int pos){
    ItemMoneyLog *cell = new ItemMoneyLog();
    if (cell && cell->init()){
        cell->autorelease();
    }else{
        CC_SAFE_DELETE(cell);
    }
    
	auto background = MSprite::create(LS_DOITHUONG_ODD);
	background->setPosition(Vec2(0,0));

	if (pos %2 == 0){
		cell->setContentSize(background->getContentSize());
		cell->addChild(background);
	}

	float sizeText = background->getHeight() / 3;

	//nguoi gui
	auto labelSender = MLabel::create("Admin", sizeText, cocos2d::Color3B::WHITE);
	labelSender->setPosition(Vec2(10, 0));
	labelSender->setContentSize(Size(1 * background->getWidth() / 6, background->getHeight()));
	labelSender->setWidth(1 * background->getWidth() / 6);
	labelSender->setHeight(background->getHeight());
	labelSender->setHorizontalAlignment(TextHAlignment::LEFT);
	labelSender->setVerticalAlignment(TextVAlignment::CENTER);
	cell->addChild(labelSender);

	//noi dung
	auto labelContent = MLabel::create(moneyLog.description(), sizeText, cocos2d::Color3B::WHITE);
	labelContent->setPosition(Vec2(labelSender->getPosition().x - 10 + labelSender->getWidth(), 0));
	labelContent->setContentSize(Size(3.5 * background->getWidth() / 6, background->getHeight()));
	labelContent->setWidth(3.5 * background->getWidth() / 6);
	labelContent->setHeight(background->getHeight());
	labelContent->setHorizontalAlignment(TextHAlignment::LEFT);
	labelContent->setVerticalAlignment(TextVAlignment::CENTER);
	cell->addChild(labelContent);

	//thoi gian
	std::string insertTime = Common::getInstance()->convertMillisecondToTime(moneyLog.insertedtime());
	auto labelTime = MLabel::create(insertTime, sizeText, cocos2d::Color3B::WHITE);
	labelTime->setPosition(Vec2(labelContent->getPosition().x + labelContent->getWidth(), 0));
	labelTime->setContentSize(Size(1.5 * background->getWidth() / 6, background->getHeight()));
	labelTime->setWidth(1.5 * background->getWidth() / 6);
	labelTime->setHeight(background->getHeight());
	labelTime->setHorizontalAlignment(TextHAlignment::CENTER);
	labelTime->setVerticalAlignment(TextVAlignment::CENTER);
	cell->addChild(labelTime);
    
    return cell;
}

float ItemMoneyLog::getWidth(){
    return this->getContentSize().width;
}

float ItemMoneyLog::getHeight(){
    return this->getContentSize().height;
}

bool ItemMoneyLog::init() {
    if (!Node::init())
        return false;

    return true;
}

void ItemMoneyLog::onExit() {
    Node::onExit();
}
