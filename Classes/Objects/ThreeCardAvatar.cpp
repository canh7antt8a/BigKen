//
//  Avatar.cpp
//  MyCards
//
//  Created by hungle on 4/22/16.
//
//

#include "ThreeCardAvatar.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/SoundManager.h"
#include <math.h>

using namespace cocos2d::ui;

#define PADDING 15

bool ThreeCardAvatar::init(){
    /*if (!Avatar::init())
        return false;*/
    
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

	ic_register_exit_room = MSprite::create("ic_exit_room.png");
	ic_register_exit_room->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	ic_register_exit_room->setPosition(Vec2(background->getPosition().x
		, background->getPosition().y + background->getHeight() / 2));
	ic_register_exit_room->setVisible(false);
	this->addChild(ic_register_exit_room, 1);

	//
	betBarier1 = MButton::create(SPRITE_BARIER, TAG_BTN_BET_BARIER1);
	betBarier1->setTitleColor(cocos2d::Color3B::BLACK);
	betBarier1->setAnchorPoint(Point::ANCHOR_MIDDLE);
	betBarier1->setPosition(Vec2(0, background->getPosition().y + background->getHeight()));
	betBarier1->addTouchEventListener(CC_CALLBACK_2(ThreeCardAvatar::menuCallBack, this));
	betBarier1->setVisible(false);

	auto sprite_barier1 = MSprite::create(BTN_BET_BARIER);
	sprite_barier1->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprite_barier1->setPosition(Vec2(betBarier1->getWidth() / 2,
		betBarier1->getHeight() / 2));
	sprite_barier1->runAction(RepeatForever::create(RotateBy::create(0.1f, 30)));
	betBarier1->addChild(sprite_barier1);

	betBarier2 = MButton::create(SPRITE_BARIER, TAG_BTN_BET_BARIER2);
	betBarier2->setTitleColor(cocos2d::Color3B::BLACK);
	betBarier2->setAnchorPoint(Point::ANCHOR_MIDDLE);
	betBarier2->setPosition(Vec2(background->getWidth(), background->getPosition().y + background->getHeight()));
	betBarier2->addTouchEventListener(CC_CALLBACK_2(ThreeCardAvatar::menuCallBack, this));
	betBarier2->setVisible(false);

	auto sprite_barier2 = MSprite::create(BTN_BET_BARIER);
	sprite_barier2->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprite_barier2->setPosition(Vec2(betBarier2->getWidth() / 2,
		betBarier2->getHeight() / 2));
	sprite_barier2->runAction(RepeatForever::create(RotateBy::create(0.1f, 30)));
	betBarier2->addChild(sprite_barier2);

	this->addChild(betBarier1);
	this->addChild(betBarier2);

	chuong = MSprite::create(SPRITE_CHUONG);
	chuong->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	chuong->setPosition(Vec2(background->getWidth()/2, 0));

	ga = MSprite::create(SPRITE_GA);
	ga->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	ga->setPosition(Vec2(background->getWidth()/2, 0));

	this->addChild(chuong);
	this->addChild(ga);

	under_money = MSprite::create("sprite_diem.png");
	under_money->setPosition(Vec2(background->getWidth() / 2 - under_money->getWidth() / 2,
		-5 - chuong->getHeight()/2 - under_money->getHeight()));
	this->addChild(under_money);

	money = MLabel::create("10$", background->getWidth() / 6);
	money->setPosition(Vec2(background->getWidth() / 2 - money->getWidth() / 2,
		under_money->getPosition().y + under_money->getHeight() / 2 - money->getHeight() / 2 + 5));
	money->setAlignment(TextHAlignment::CENTER);
	this->addChild(money);
    bg_bet_money = MSprite::create("ba_cay/sprite_hienthi2.png");
    bg_bet_money->setPosition(Vec2(background->getWidth() / 2 - bg_bet_money->getWidth() / 2, 
        under_money->getPosition().y - bg_bet_money->getHeight() + 5));
    this->addChild(bg_bet_money);
    bg_bet_money->setVisible(false);
    bet_money = MLabel::create("", bg_bet_money->getHeight() * 0.5f);
    bet_money->setTextColor(Color4B::GRAY);
    bet_money->setPosition(Vec2(bg_bet_money->getPosition().x + bg_bet_money->getWidth() / 2 - bet_money->getWidth() / 2, 
        bg_bet_money->getPosition().y + bg_bet_money->getHeight() / 2 - bet_money->getHeight() * 0.7f));
    bet_money->setVisible(false);
    this->addChild(bet_money);
    this->setContentSize(background->getContentSize());
    
    this->addEvents();

    return true;
}

void ThreeCardAvatar::setConfirm(bool isConfirm){
	this->isConfirm = isConfirm;
}

bool ThreeCardAvatar::getConfirm(){
	return this->isConfirm;
}

void ThreeCardAvatar::showBetBarier(){
	betBarier1->setVisible(true);
	betBarier2->setVisible(true);

	betBarier1->setTitleText(Common::getInstance()->convertIntToMoneyView(minBet));
	betBarier2->setTitleText(Common::getInstance()->convertIntToMoneyView(minBet * 2));
}

void ThreeCardAvatar::showBetBarier(long long value, bool isConfirm){
	setConfirm(isConfirm);

	if (value == minBet){
		betBarier1->setVisible(true);
		betBarier2->setVisible(false);

		betBarier1->setTitleText(Common::getInstance()->convertIntToMoneyView(minBet));
	}
	else {
		betBarier1->setVisible(false);
		betBarier2->setVisible(true);

		betBarier2->setTitleText(Common::getInstance()->convertIntToMoneyView(minBet * 2));
	}
}

void ThreeCardAvatar::hiddenBetBarier(){
	betBarier1->setVisible(false);
	betBarier2->setVisible(false);

	setConfirm(false);
}

void ThreeCardAvatar::showChuong(bool isChuong){
	chuong->setVisible(isChuong);
}

void ThreeCardAvatar::showGa(bool isGa){
	ga->setVisible(isGa);
}

void ThreeCardAvatar::setBetMoney(int betMoney) {
    bet_money->setString(StringUtils::format("%d", betMoney));
    bet_money->setPosition(Vec2(bg_bet_money->getPosition().x + bg_bet_money->getWidth() / 2 - bet_money->getWidth() / 2,
        bg_bet_money->getPosition().y + bg_bet_money->getHeight() / 2 - bet_money->getHeight() * 0.7f));
    bet_money->setVisible(betMoney != 0);
    bg_bet_money->setVisible(betMoney != 0);
}

void ThreeCardAvatar::menuCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
	if (type == Widget::TouchEventType::ENDED) {
		MButton *button = (MButton*)sender;
		int tag = button->getTag();

		vector<std::pair<int, int>> lstBets;
		std::pair<int, int> pair_bet;
		pair_bet.first = player_id;
        pair_bet.second = (tag == TAG_BTN_BET_BARIER1 ? minBet : minBet * 2);

        lstBets.push_back(pair_bet);
        
		if (isConfirm){
			NetworkManager::getInstance()->getConfirmBetByBarier(roomIndex, lstBets);
		}
		else {
			NetworkManager::getInstance()->getBetByBarier(roomIndex, lstBets);
		}

		hiddenBetBarier();
	}
}

void ThreeCardAvatar::hideCard() {
    for (int i = 0; i < 3; i++)
        cardCover[i]->setVisible(false);
}

void ThreeCardAvatar::showCardCover() {
    for (int i = 0; i < 3; i++) {
        cardCover[i]->setSpriteFrame("card_cover.png");
        cardCover[i]->setVisible(true);
    }
}

void ThreeCardAvatar::addCardCover(float cardWidth){
	int init_pos_card = cardWidth / 2;
	for (int i = 0; i < 3; i++){
        cardCover[i] = MSprite::createwithFrameName("card_cover.png");
        cardCover[i]->setAnchorPoint(Point::ANCHOR_MIDDLE);
        card[i].setValue(0);
        cardCover[i]->setScale(cardWidth / cardCover[i]->getWidth());
        Vec2 posCardCover = getCardCoverPostion(posIndex, avatar->getContentSize(), cardCover[i]->getContentSize() * cardCover[i]->getScale());
        cardCover[i]->setPosition(Vec2(posCardCover.x + init_pos_card*i, posCardCover.y));
        this->addChild(cardCover[i]);
        cardCover[i]->setVisible(false);
	}
}



void ThreeCardAvatar::setCards(vector<int> cards) {
    for (int i = 0; i < 3; i++) 
        card[i].setValue(cards[i]);
}

void ThreeCardAvatar::clear() {
    for (int i = 0; i < 3; i++) {
        card[i].setValue(0);
    }
}

void ThreeCardAvatar::flipCards() {
    auto camera1 = OrbitCamera::create(0.25f, 1, 0, 0.0f, 90.0f, 0, 0);
    auto camera2 = OrbitCamera::create(0.25f, 1, 0, 270.0f, 90.0f, 0, 0);
    
    for (int i = 0; i < 3; i++) {
        if (cardCover[i] != NULL && cardCover[i]->getParent() != NULL) {
            auto callbackJump = CallFunc::create([=]() {
                SoundManager::getInstance()->playSound("");
                cardCover[i]->setSpriteFrame(card[i].getActualName());
            });
            auto sequence = Sequence::create(camera1->clone(), callbackJump, camera2->clone(), NULL);
            cardCover[i]->runAction(sequence);
        }
    }
}

ThreeCardAvatar::~ThreeCardAvatar(){
}

void ThreeCardAvatar::loadAvatar(int index, std::string id, std::string _name, std::string _money, int roomIndex, int minBet) {
    this->roomIndex = roomIndex;
	this->minBet = minBet;
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

void ThreeCardAvatar::setAvatarPostion(int index, Vec2 origin, Size visibleSize, float buttonHeight){
    Vec2 pos = Vec2(0, 0);
    Size size = Size(visibleSize.width*0.75f,visibleSize.width*0.75f*461/955.0f);
    posIndex = index;
    
    switch (index) {
        case 7:
            pos = Vec2(-size.width*0.45f - this->getContentSize().width / 2, -this->getContentSize().height * 1.3f);
            break;
        case 6:
            pos = Vec2(-size.width*0.45f - this->getContentSize().width / 2, this->getContentSize().height * 1.2f);
            break;
        case 5:
            pos = Vec2(-size.width*0.25f - this->getContentSize().width/2,size.height/2-this->getContentSize().height * 0.4f);
            break;
        case 4:
            pos = Vec2( size.width*0.25f - this->getContentSize().width/2,size.height/2-this->getContentSize().height * 0.4f);
            break;
        case 3:
            pos = Vec2( size.width*0.5f - this->getContentSize().width, this->getContentSize().height * 1.2f);
            break;
        case 2:
            pos = Vec2( size.width*0.52f - this->getContentSize().width,-this->getContentSize().height * 0.9f);
            break;
        case 1:
            pos = Vec2(size.width*0.25f - this->getContentSize().width/2,-size.height/2);
            break;
        case 0:
            pos = Vec2(-size.width*0.25f - this->getContentSize().width/2,-size.height/2);
            break;
        default:
            break;
    }
    this->setPosition(pos + Vec2(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height/2));
}

Vec2 ThreeCardAvatar::getCardCoverPostion(int index, Size avatarSize, Size cardSize){
    Vec2 pos;
    
    if(index == 7 || index == 6 || index == 4 || index == 0){
		pos = Vec2(-2 * cardSize.width - 10, 0) + cardSize/2;//- cardSize.height / 2);
    }else{
		pos = Vec2(avatarSize.width + cardSize.width * 0.2f, 0) + cardSize/2;//- cardSize.height / 2);
    }
    return pos;
}

void ThreeCardAvatar::onExit() {
    Avatar::onExit();
}