#include "ItemInviteToPlay.hpp"
#include "UI/MLabel.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"

#define TAG_CHECKED 111

ItemInviteToPlay::ItemInviteToPlay(){}

ItemInviteToPlay::~ItemInviteToPlay(){}

ItemInviteToPlay* ItemInviteToPlay::create(Size contentSize, BINUserInfo userInfo, bool isVipRoom, bool checkAll, PopupInviteToPlay* context){
    ItemInviteToPlay *cell = new ItemInviteToPlay();
    if (cell && cell->init()){
        cell->autorelease();
    }else{
        CC_SAFE_DELETE(cell);
    }

	cell->setContentSize(contentSize);

	cell->setContext(context);

	auto bg_avatar = MSprite::create("bk_avatar.png");
	float scale = 0.8f * contentSize.height / bg_avatar->getWidth();
	bg_avatar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	bg_avatar->setPosition(Vec2(bg_avatar->getWidth() * scale / 2, contentSize.height / 2));
	bg_avatar->setScale(scale);
	cell->addChild(bg_avatar);
    
	int avatar_id = userInfo.avatarid();
	if (avatar_id < 100000){
		avatar_id = 0;
	}

	auto avatar = MSprite::create(StringUtils::format("avatar%d.png", avatar_id));
	avatar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	avatar->setPosition(Vec2(bg_avatar->getPosition().x + bg_avatar->getWidth() * scale / 2 - avatar->getWidth() * scale / 2
		, bg_avatar->getPosition().y));
	avatar->setScale(scale);
	cell->addChild(avatar);

	auto lb_name = MLabel::create(userInfo.username(), bg_avatar->getHeight() / 3, Color3B::WHITE);
	lb_name->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lb_name->setPosition(Vec2(bg_avatar->getPosition().x + bg_avatar->getWidth() * scale + 10, bg_avatar->getPosition().y));
	lb_name->setWidth(contentSize.width / 4);
	cell->addChild(lb_name);

	string money = isVipRoom ? StringUtils::format("%lld XU", userInfo.cash()) : StringUtils::format("%lld KEN", userInfo.gold());

	auto lb_xu = MLabel::create(money, bg_avatar->getHeight() / 3.5f, Color3B::YELLOW);
	lb_xu->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lb_xu->setPosition(Vec2(cell->getWidth()/2, bg_avatar->getPosition().y));
	lb_xu->setWidth(2.5f * contentSize.width / 8);
	//lb_xu->setHeight(0.8f * cell->getHeight());
	lb_xu->setLineBreakWithoutSpace(true);
	lb_xu->enableWrap(true);
	cell->addChild(lb_xu);

	auto sprite_otrong = MButton::create("popup_moichoi/sprite_otrong.png", TAG_ITEM_INVITE_CHECKED);
	sprite_otrong->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	sprite_otrong->setPosition(Vec2(cell->getWidth() - bg_avatar->getWidth() * scale / 2 - sprite_otrong->getWidth()
		, bg_avatar->getPosition().y));
	sprite_otrong->addTouchEventListener(CC_CALLBACK_2(ItemInviteToPlay::menuCallBack, cell));
	cell->addChild(sprite_otrong);

	cell->setUserInviteId(userInfo.userid());

	if (checkAll){
		if (sprite_otrong->getChildByTag(TAG_CHECKED) != nullptr){  //neu check roi thi bo check
			sprite_otrong->removeChildByTag(TAG_CHECKED);
		}
		else { //chua check thi check
			auto sprite_checked = MSprite::create("popup_moichoi/sprite_tich.png");
			sprite_checked->setTag(TAG_CHECKED);
			sprite_checked->setAnchorPoint(Point::ANCHOR_MIDDLE);
			sprite_checked->setPosition(Vec2(sprite_otrong->getWidth() / 2, sprite_otrong->getHeight() / 2));
			sprite_otrong->addChild(sprite_checked);
		}
	}

	auto sprite_gach = MSprite::create("popup_moichoi/sprite_horizontal.png");
	cell->addChild(sprite_gach);

    return cell;
}

void ItemInviteToPlay::setUserInviteId(long userInviteId){
	this->userInviteId = userInviteId;
}

void ItemInviteToPlay::setContext(PopupInviteToPlay* context){
	this->context = context;
}

void ItemInviteToPlay::setRadioChecked(){
	auto btn_checked = (MButton*) this->getChildByTag(TAG_ITEM_INVITE_CHECKED);
	if (btn_checked != nullptr){
		if (btn_checked->getChildByTag(TAG_CHECKED) != nullptr){  //neu check roi thi bo check
			btn_checked->removeChildByTag(TAG_CHECKED);
			context->removeItemSelected(userInviteId);
		}
		else { //chua check thi check
			auto sprite_checked = MSprite::create("popup_moichoi/sprite_tich.png");
			sprite_checked->setTag(TAG_CHECKED);
			sprite_checked->setAnchorPoint(Point::ANCHOR_MIDDLE);
			sprite_checked->setPosition(Vec2(btn_checked->getWidth() / 2, btn_checked->getHeight() / 2));
			btn_checked->addChild(sprite_checked);
			context->addItemSelected(userInviteId);
		}
	}
}

void ItemInviteToPlay::menuCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type){
	if (type == ui::Widget::TouchEventType::ENDED) {
		MButton *button = (MButton*) sender;
		int tag = button->getTag();
		switch (tag) {
		case TAG_ITEM_INVITE_CHECKED:
			CCLOG("item checked");
			{
				setRadioChecked();
			}
			break;
		default:
			break;
		}
	}
}

float ItemInviteToPlay::getWidth(){
    return this->getContentSize().width;
}

float ItemInviteToPlay::getHeight(){
    return this->getContentSize().height;
}

bool ItemInviteToPlay::init() {
    if (!Node::init())
        return false;

    return true;
}

void ItemInviteToPlay::onExit() {
    Node::onExit();
}
