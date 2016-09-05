//
//  NodeContactUser.cpp
//  MyCards
//
//  Created by hungle on 6/30/16.
//
//

#include "NodeContactUser.hpp"
#include "UI/MSprite.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
#include "Utils/image.h"
#include "Utils/NetworkManager.h"

using namespace std;
using namespace cocos2d::ui;

bool NodeContactUser::init() {
    if (!Node::init())
        return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto background = LayerColor::create(Color4B(0, 0, 0, 160));
	background->setContentSize(visibleSize);
	background->setPosition(Vec2(0, 0));
	background->setOpacity(200);
	this->addChild(background);

	backgroundPopup = MSprite::create("user_info/sprite_bg_contact_user.png");
	backgroundPopup->setAnchorPoint(Point::ANCHOR_MIDDLE);
	backgroundPopup->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->setContentSize(background->getContentSize());
	this->addChild(backgroundPopup);

	auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
	bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
		backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
	backgroundPopup->addChild(bg_title_popup);

	auto title = Label::createWithTTF("THÔNG TIN CÁ NHÂN", "fonts/font_title.otf", 0.45f * bg_title_popup->getHeight());
	title->setColor(Color3B::BLACK);
	title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
		bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
	bg_title_popup->addChild(title);

	auto underBackground = MSprite::create("user_info/sprite_under_background.png");
	underBackground->setPosition(Vec2(backgroundPopup->getWidth() / 2 - underBackground->getWidth() / 2,
		backgroundPopup->getWidth() / 2 - underBackground->getWidth() / 2));
	backgroundPopup->addChild(underBackground);

	auto backgroundAvatar = MSprite::create("user_info/sprite_avata.png");
	backgroundAvatar->setPosition(Vec2(backgroundPopup->getWidth() / 2 - backgroundAvatar->getWidth() / 2,
		backgroundPopup->getHeight()*0.75f - backgroundAvatar->getHeight() / 2));
	backgroundPopup->addChild(backgroundAvatar);

	avatar = MSprite::create("avatar0.png", backgroundAvatar->getSize());
	avatar->setPosition(backgroundAvatar->getPosition());
	backgroundPopup->addChild(avatar);

	auto change_avatar = MButton::create("user_info/sprite_thayvata.png", TAG_CHANGE_AVATAR);
	change_avatar->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
	change_avatar->setPosition(Vec2(avatar->getPosition().x + avatar->getWidth(), avatar->getPosition().y));
	backgroundPopup->addChild(change_avatar);

	auto roundAvatar = MSprite::create("user_info/sprite_vienavata.png");
	roundAvatar->setPosition(Vec2(backgroundPopup->getWidth() / 2 - roundAvatar->getWidth() / 2,
		backgroundPopup->getHeight()*0.75f - roundAvatar->getHeight() / 2));
	backgroundPopup->addChild(roundAvatar);

	float fontSize = avatar->getHeight()*0.2f;
	auto fontColor = Color3B(82, 194, 252);
	auto fontEditColor = Color3B(255, 255, 255);

	auto userID = MLabel::create("ID:", fontSize, fontColor);
	userID->setPosition(Vec2(100, backgroundPopup->getHeight()*0.75f - userID->getHeight() / 2));
	backgroundPopup->addChild(userID);

	userID_text = MLabel::create("", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_ID);
	userID_text->setPosition(userID->getPosition().x + userID->getWidth() + 10, userID->getPosition().y);
	backgroundPopup->addChild(userID_text);

	auto userLevel = MLabel::create("Level:", fontSize, fontColor);
	userLevel->setPosition(Vec2(userID->getPosition().x,
		userID->getPosition().y + userID->getHeight()));
	backgroundPopup->addChild(userLevel);

	userLevel_text = MLabel::create("", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_LEVEL);
	userLevel_text->setPosition(userLevel->getPosition().x + userLevel->getWidth() + 10, userLevel->getPosition().y);
	backgroundPopup->addChild(userLevel_text);

	userName_text = MLabel::create("", fontSize, fontColor, TAG_POPUP_USERINFO_LBL_NAME);
	userName_text->setPosition(Vec2(userID->getPosition().x,
		userLevel->getPosition().y + userLevel->getHeight()));
	backgroundPopup->addChild(userName_text);

	auto userVip = MLabel::create("VIP:", fontSize, fontColor);
	userVip->setPosition(Vec2(userID->getPosition().x,
		userID->getPosition().y - userID->getHeight()));
	backgroundPopup->addChild(userVip);

	userVip_text = MLabel::create("0/10", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_VIP);
	userVip_text->setPosition(Vec2(userVip->getPosition().x + userVip->getWidth() + 10, userVip->getPosition().y));
	backgroundPopup->addChild(userVip_text);

	userSdt = MLabel::create("SDT:", fontSize, fontColor);
	userSdt->setPosition(userID->getPosition().x, userVip->getPosition().y - userVip->getHeight());
	backgroundPopup->addChild(userSdt);

	userSdt_text = MLabel::create("", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_SDT);
	userSdt_text->setPosition(Vec2(userSdt->getPosition().x + userSdt->getWidth() + 10, userSdt->getPosition().y));
	backgroundPopup->addChild(userSdt_text);

	auto xu_background = MSprite::create("user_info/sprite_hienxuken.png");
	xu_background->setPosition(Vec2(backgroundPopup->getWidth() - 100 - xu_background->getWidth(),
		backgroundPopup->getHeight()*0.75f));
	backgroundPopup->addChild(xu_background);

	xu_text = MLabel::create("xu", xu_background->getHeight() * 0.5f, fontColor);
	xu_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	xu_text->setPosition(Vec2(xu_background->getPosition().x + 5,
		xu_background->getPosition().y + xu_background->getHeight() / 2));
	backgroundPopup->addChild(xu_text);

	auto icon_xu = MSprite::create(TABLE_SPRITE_XU);
	icon_xu->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	icon_xu->setPosition(Vec2(xu_background->getPosition().x + xu_background->getWidth(),
		xu_background->getPosition().y + xu_background->getHeight() / 2));
	backgroundPopup->addChild(icon_xu);

	auto ken_background = MSprite::create("user_info/sprite_hienxuken.png");
	ken_background->setPosition(Vec2(backgroundPopup->getWidth() - 100 - ken_background->getWidth(),
		backgroundPopup->getHeight()*0.75f
		- ken_background->getHeight()*0.3f - ken_background->getHeight()));
	backgroundPopup->addChild(ken_background);

	ken_text = MLabel::create("", ken_background->getHeight() * 0.5f, fontColor);
	ken_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	ken_text->setPosition(Vec2(ken_background->getPosition().x + 5,
		ken_background->getPosition().y + ken_background->getHeight() / 2));
	backgroundPopup->addChild(ken_text);

	auto icon_ken = MSprite::create(TABLE_SPRITE_KEN);
	icon_ken->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	icon_ken->setPosition(Vec2(ken_background->getPosition().x + ken_background->getWidth(),
		ken_background->getPosition().y + ken_background->getHeight() / 2));
	backgroundPopup->addChild(icon_ken);

	auto chisotinnhiem = MLabel::create("Chỉ số tín nhiệm :", fontSize*0.8f, fontColor);
	chisotinnhiem->setPosition(Vec2(xu_background->getPosition().x,
		xu_background->getPosition().y + xu_background->getHeight() + 10));
	backgroundPopup->addChild(chisotinnhiem);

	chisotinnhiem_text = MLabel::create("", fontSize*0.8f, fontColor, TAG_POPUP_USERINFO_LBL_CHISOTINNHIEM);
	chisotinnhiem_text->setPosition(Vec2(chisotinnhiem->getPosition().x + chisotinnhiem->getWidth() + 10,
		chisotinnhiem->getPosition().y));
	backgroundPopup->addChild(chisotinnhiem_text);

	btnAddFriend = MButton::create("user_info/btn_doimatkhau.png", TXT_ADD_FRIEND, 20, TAG_ADD_FRIEND);
	//btnAddFriend->setTitleFontSize(btnAddFriend->getHeight() / 2);
	btnAddFriend->setPosition(Vec2(backgroundPopup->getWidth() / 2 - btnAddFriend->getWidth() / 2,
		backgroundPopup->getHeight()*0.2f*0.5f));
	btnAddFriend->addTouchEventListener(CC_CALLBACK_2(NodeContactUser::clickCallBack, this));
	btnAddFriend->setVisible(false);
	backgroundPopup->addChild(btnAddFriend);

	btnRemoveFriend = MButton::create("user_info/btn_doimatkhau.png", TXT_REMOVE_FRIEND, 20, TAG_REMOVE_FRIEND);
	//btnRemoveFriend->setTitleFontSize(btnRemoveFriend->getHeight() / 2);
	btnRemoveFriend->setPosition(Vec2(backgroundPopup->getWidth() / 2 - btnRemoveFriend->getWidth() / 2,
		backgroundPopup->getHeight()*0.2f*0.5f));
	btnRemoveFriend->addTouchEventListener(CC_CALLBACK_2(NodeContactUser::clickCallBack, this));
	btnRemoveFriend->setVisible(false);
	backgroundPopup->addChild(btnRemoveFriend);

	btnAccpeptFriend = MButton::create("user_info/btn_doimatkhau.png", TXT_ACCEPT_FRIEND, 20, TAG_ACCEPT_FRIEND);
	//btnAccpeptFriend->setTitleFontSize(btnAccpeptFriend->getHeight() / 2);
	btnAccpeptFriend->setPosition(Vec2(backgroundPopup->getWidth() / 2 - btnAccpeptFriend->getWidth() - 10,
		backgroundPopup->getHeight()*0.2f*0.5f));
	btnAccpeptFriend->addTouchEventListener(CC_CALLBACK_2(NodeContactUser::clickCallBack, this));
	btnAccpeptFriend->setVisible(false);
	backgroundPopup->addChild(btnAccpeptFriend);

	btnDenyFriend = MButton::create("user_info/btn_doimatkhau.png", TXT_DENY_FRIEND, 20, TAG_DENY_FRIEND);
	btnDenyFriend->setPosition(Vec2(backgroundPopup->getWidth() / 2 + 10,
		backgroundPopup->getHeight()*0.2f*0.5f));
	btnDenyFriend->addTouchEventListener(CC_CALLBACK_2(NodeContactUser::clickCallBack, this));
	btnDenyFriend->setVisible(false);
	backgroundPopup->addChild(btnDenyFriend);

	lbStatusFriend = MLabel::create("", btnRemoveFriend->getHeight() / 2);
	lbStatusFriend->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lbStatusFriend->setPosition(Vec2(backgroundPopup->getWidth() / 2,
		backgroundPopup->getHeight()*0.2f*0.5f));
	lbStatusFriend->setVisible(false);
	backgroundPopup->addChild(lbStatusFriend);

	auto spriteSoVanChoi = MSprite::create("user_info/sprite_sovanchoi.png");
	spriteSoVanChoi->setPosition(Vec2(50, backgroundPopup->getHeight()*0.625f*0.5f));
	backgroundPopup->addChild(spriteSoVanChoi);

	auto sovanchoi = MLabel::create("Số ván chơi", fontSize, fontColor);
	sovanchoi->setPosition(Vec2(spriteSoVanChoi->getPosition().x + spriteSoVanChoi->getWidth() + 10,
		spriteSoVanChoi->getPosition().y
		+ spriteSoVanChoi->getHeight() - sovanchoi->getHeight() + 10));
	backgroundPopup->addChild(sovanchoi);

	sovanchoi_text = MLabel::create("0", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_SOVANCHOI);
	sovanchoi_text->setPosition(Vec2(sovanchoi->getPosition().x + sovanchoi->getWidth() / 2 - sovanchoi_text->getWidth() / 2,
		sovanchoi->getPosition().y - sovanchoi_text->getHeight()));
	backgroundPopup->addChild(sovanchoi_text);

	auto spriteSoVanThang = MSprite::create("user_info/sprite_sovanthang.png");
	spriteSoVanThang->setPosition(Vec2(btnAddFriend->getPosition().x,
		backgroundPopup->getHeight()*0.625f*0.5f));
	backgroundPopup->addChild(spriteSoVanThang);

	auto sovanthang = MLabel::create("Số ván thắng", fontSize, fontColor);
	sovanthang->setPosition(Vec2(spriteSoVanThang->getPosition().x + spriteSoVanThang->getWidth() + 10,
		spriteSoVanThang->getPosition().y
		+ spriteSoVanThang->getHeight() - sovanthang->getHeight() + 10));
	backgroundPopup->addChild(sovanthang);

	sovanthang_text = MLabel::create("0", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_SOVANTHANG);
	sovanthang_text->setPosition(Vec2(sovanthang->getPosition().x + sovanthang->getWidth() / 2 - sovanthang_text->getWidth() / 2,
		sovanthang->getPosition().y - sovanthang_text->getHeight()));
	backgroundPopup->addChild(sovanthang_text);

	auto sovanthua = MLabel::create("Số ván thua", fontSize, fontColor);
	sovanthua->setPosition(Vec2(backgroundPopup->getWidth() - 50 - sovanthua->getWidth(),
		spriteSoVanChoi->getPosition().y
		+ spriteSoVanChoi->getHeight() - sovanthua->getHeight() + 10));
	backgroundPopup->addChild(sovanthua);

	auto spriteSoVanThua = MSprite::create("user_info/sprite_sovanthua.png");
	spriteSoVanThua->setPosition(Vec2(sovanthua->getPosition().x - spriteSoVanThua->getWidth() - 10,
		backgroundPopup->getHeight()*0.625f*0.5f));
	backgroundPopup->addChild(spriteSoVanThua);

	sovanthua_text = MLabel::create("0", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_SOVANTHUA);
	sovanthua_text->setPosition(Vec2(sovanthua->getPosition().x + sovanthua->getWidth() / 2 - sovanthua_text->getWidth() / 2,
		sovanthua->getPosition().y - sovanthua_text->getHeight()));
	backgroundPopup->addChild(sovanthua_text);

	//btn close
	auto btn_close = MButton::create(IMAGE_CLOSE, TAG_CLOSE);
	btn_close->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	btn_close->setPosition(Vec2(backgroundPopup->getWidth() - btn_close->getWidth() / 2,
		backgroundPopup->getHeight() - btn_close->getHeight() / 2));
	btn_close->addTouchEventListener(CC_CALLBACK_2(NodeContactUser::clickCallBack, this));
	backgroundPopup->addChild(btn_close);

	this->scheduleUpdate();

    return true;
}

void NodeContactUser::viewUserInfo(BINViewUserInfoResponse *viewUserInfo){
	BINUserInfo userInfo = viewUserInfo->userinfo();
	int friend_status = viewUserInfo->friendstatus();

	auto common = Common::getInstance();
	int avatar_id = userInfo.avatarid();
	if (avatar_id < 100000){
		avatar_id = 0;
	}
	avatar->setTexture(StringUtils::format("avatar%d.png", avatar_id));
	userID_text->setString(common->convertIntToString(userInfo.userid()));
	userLevel_text->setString(common->convertIntToString(userInfo.level().level()));
	userName_text->setString(userInfo.displayname());

	ken_text->setString(common->numberFormatWithCommas(userInfo.gold()));
	xu_text->setString(common->numberFormatWithCommas(userInfo.cash()));

	if (userInfo.userid() == common->getUserId()){
		targetUserId = 0;
		userSdt_text->setString(common->getPhoneNumber());
		common->setCash(userInfo.cash());
		common->setGold(userInfo.gold());
	}
	else {
		targetUserId = userInfo.userid();

		userSdt_text->setVisible(false);
		userSdt->setVisible(false);

		showFriendStatus(friend_status);
	}

	chisotinnhiem_text->setString(common->convertIntToString(userInfo.trustedindex()));
	sovanchoi_text->setString(common->convertIntToString(userInfo.totalmatch()));
	sovanthang_text->setString(common->convertIntToString(userInfo.totalwin()));
	sovanthua_text->setString(common->convertIntToString(userInfo.totalmatch() - userInfo.totalwin()));
}

void NodeContactUser::showFriendStatus(int friendStatus){
	if (friendStatus == 1){
		//neu la ban be cua nguoi choi thi hien thi nut huy ket ban
		btnRemoveFriend->setVisible(true);
		btnAddFriend->setVisible(false);
		btnAccpeptFriend->setVisible(false);
		btnDenyFriend->setVisible(false);
		lbStatusFriend->setVisible(false);
	}
	else if (friendStatus == 0){
		//neu khong phai ban cua nguoi choi thi hien thi nut them ban be
		btnRemoveFriend->setVisible(false);
		btnAccpeptFriend->setVisible(false);
		btnDenyFriend->setVisible(false);
		lbStatusFriend->setVisible(false);
		btnAddFriend->setVisible(true);
	}
	else if (friendStatus == 2){  //da gui yeu cau ket ban
		lbStatusFriend->setVisible(true);
		lbStatusFriend->setString("Đã gửi yêu cầu kết bạn");
		lbStatusFriend->setPosition(Vec2(backgroundPopup->getWidth() / 2,
			backgroundPopup->getHeight()*0.2f*0.5f));

		btnDenyFriend->setVisible(false);
		btnAccpeptFriend->setVisible(false);
		btnRemoveFriend->setVisible(false);
		btnAddFriend->setVisible(false);
	}
	else if (friendStatus == 3){  //co yeu cau ket ban
		btnDenyFriend->setVisible(true);
		btnAccpeptFriend->setVisible(true);
		btnRemoveFriend->setVisible(false);
		btnAddFriend->setVisible(false);
		lbStatusFriend->setVisible(false);
	}
}

void NodeContactUser::update(float){
	viewUserInfoFromServer();
	addFriendResponse();
	removeFriendResponse();
	approveFriendResponse();
}

void NodeContactUser::addFriendResponse(){
	BINAddFriendResponse *response = (BINAddFriendResponse*) Common::getInstance()->checkEvent(NetworkManager::ADD_FRIEND);
	if (response != 0){
		CCLOG("add friend response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			showFriendStatus(response->friendstatus());
		}
	}
}

void NodeContactUser::approveFriendResponse(){
	BINApproveAddFriendResponse *response = (BINApproveAddFriendResponse*)Common::getInstance()->checkEvent(NetworkManager::APPROVE_ADD_FRIEND);
	if (response != 0){
		CCLOG("approve friend response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			showFriendStatus(response->friendstatus());
		}
	}
}

void NodeContactUser::removeFriendResponse(){
	BINRemoveFriendResponse *response = (BINRemoveFriendResponse*)Common::getInstance()->checkEvent(NetworkManager::REMOVE_FRIEND);
	if (response != 0){
		CCLOG("remove friend response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			showFriendStatus(response->friendstatus());
			//NetworkManager::getInstance()->getViewUserInfoFromServer(targetUserId);
		}
	}
}

void NodeContactUser::viewUserInfoFromServer(){
	BINViewUserInfoResponse *response = (BINViewUserInfoResponse*)Common::getInstance()->checkEvent(NetworkManager::VIEW_USER_INFO);
	if (response != 0){
		CCLOG("view userinfo response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			if (response->has_userinfo()){
				viewUserInfo(response);
			}
		}
	}
}

void NodeContactUser::clickCallBack(Ref *pSender, Widget::TouchEventType eventType){
	if (eventType == Widget::TouchEventType::ENDED){
		MButton *button = (MButton*)pSender;
		int tag = button->getTag();
		switch (tag){
		case TAG_CLOSE:
			_eventDispatcher->resumeEventListenersForTarget(Director::getInstance()->getRunningScene(), true);
			this->removeFromParentAndCleanup(true);
			break;
		case TAG_ADD_FRIEND:
			if (targetUserId != 0){
				NetworkManager::getInstance()->getAddFriend(targetUserId);
			}
			break;
		case TAG_REMOVE_FRIEND:
			if (targetUserId != 0){
				NetworkManager::getInstance()->getRemoveFriendFromServer(targetUserId);
			}
			break;
		case TAG_ACCEPT_FRIEND:
			if (targetUserId != 0){
				NetworkManager::getInstance()->getApproveAddFriendFromServer(targetUserId, true);
			}
			break;
		case TAG_DENY_FRIEND:
			if (targetUserId != 0){
				NetworkManager::getInstance()->getApproveAddFriendFromServer(targetUserId, false);
			}
			break;
		default:
			break;
		}
	}
}

void NodeContactUser::changeText(int tag,std::string text){
    MLabel* label = (MLabel*)this->getChildByTag(tag);
    label->setString(text);
}

float NodeContactUser::getWidth(){
    return this->getContentSize().width;
}

float NodeContactUser::getHeight(){
    return this->getContentSize().height;
}

void NodeContactUser::onExit(){
    Node::onExit();
}
