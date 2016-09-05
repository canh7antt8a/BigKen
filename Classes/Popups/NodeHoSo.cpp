#include "NodeHoSo.hpp"
#include "UI/MSprite.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
#include "Utils/NetworkManager.h"
using namespace std;

#define PADDING 10

bool NodeHoSo::init() {
    if (!Node::init())
        return false;

	auto backgroundPopup = MSprite::create("user_info/bg_popup/content_popup_right.png");

	this->setContentSize(backgroundPopup->getContentSize());

	this->addChild(backgroundPopup);

	float width = backgroundPopup->getWidth();
	float height = backgroundPopup->getHeight();

	avatar = MSprite::create("avatar0.png");
	avatar->setAnchorPoint(Point::ANCHOR_MIDDLE);

	auto roundAvatar = MSprite::create("user_info/sprite_vienavata.png");
	roundAvatar->setScale(avatar->getWidth() * 1.4f / roundAvatar->getWidth());
	roundAvatar->setAnchorPoint(Point::ANCHOR_MIDDLE);

	float fontSize = avatar->getHeight()*0.3f;
	auto fontColor = Color3B(82, 194, 252);
	auto fontEditColor = Color3B(255, 255, 255);

	//user_id
	auto userID = MLabel::create("ID:", fontSize, fontColor);
	userID->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

	userID_text = MLabel::create("test", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_ID);
	userID_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

	userID->setPosition(Vec2(width / 4 - (userID->getWidth() + userID_text->getWidth() + PADDING) / 2
		, height / 2));
	userID_text->setPosition(userID->getPosition().x + userID->getWidth() + PADDING, userID->getPosition().y);

	//level
	auto userLevel = MLabel::create("Level:", fontSize, fontColor);
	userLevel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	userLevel_text = MLabel::create("", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_LEVEL);
	userLevel_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

	userLevel->setPosition(Vec2(width / 4 - (userLevel->getWidth() + userLevel_text->getWidth() + PADDING) / 2,
		userID->getPosition().y + userID->getHeight() + 5));
	userLevel_text->setPosition(userLevel->getPosition().x + userLevel->getWidth() + PADDING, userLevel->getPosition().y);

	//user name
	userName_text = MLabel::create("test", fontSize, fontColor, TAG_POPUP_USERINFO_LBL_NAME);
	userName_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	userName_text->setPosition(Vec2(width / 4 - userName_text->getWidth() / 2, userLevel->getPosition().y + userLevel->getHeight() + 5));
	
	roundAvatar->setPosition(Vec2(width / 4, userName_text->getPosition().y + userName_text->getHeight() / 2 
		+ (height - userName_text->getPosition().y - userName_text->getHeight() / 2) / 2));

	avatar->setPosition(roundAvatar->getPosition());

	auto change_avatar = MButton::create("user_info/sprite_thayvata.png", TAG_CHANGE_AVATAR);
	change_avatar->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
	change_avatar->setPosition(Vec2(avatar->getPosition().x + avatar->getWidth(), avatar->getPosition().y));

	/*auto userVip = MLabel::create("VIP:", fontSize, fontColor);
	userVip->setPosition(Vec2(userID->getPosition().x,
		userID->getPosition().y - userID->getHeight()));

	userVip_text = MLabel::create("0/10", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_VIP);
	userVip_text->setPosition(Vec2(userVip->getPosition().x + userVip->getWidth() + PADDING, userVip->getPosition().y));*/

	//phone
	userSdt = MLabel::create("SDT:", fontSize, fontColor);
	userSdt->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	userSdt_text = MLabel::create("0", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_SDT);
	userSdt_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

	userSdt->setPosition(width / 4 - (userSdt->getWidth() + userSdt_text->getWidth() + PADDING) / 2
		, userID->getPosition().y - userID->getHeight() - 5);
	userSdt_text->setPosition(Vec2(userSdt->getPosition().x + userSdt->getWidth() + PADDING, userSdt->getPosition().y));

	auto btn_edit_phone = MButton::create("user_info/btn_pencil.png", TAG_POPUP_USERINFO_BTN_EDIT_SDT);
	btn_edit_phone->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	btn_edit_phone->setPosition(Vec2(userSdt_text->getPosition().x + userSdt_text->getWidth() + PADDING,
		userSdt_text->getPosition().y));
	btn_edit_phone->addTouchEventListener(CC_CALLBACK_2(
		NodeHoSo::menuPopupCallBack1, this));

	//chi so tin nhiem
	auto chisotinnhiem = MLabel::create("Chỉ số tin nhiệm :", fontSize, fontColor);
	chisotinnhiem->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	chisotinnhiem_text = MLabel::create("0", fontSize, fontColor, TAG_POPUP_USERINFO_LBL_CHISOTINNHIEM);
	chisotinnhiem_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

	chisotinnhiem->setPosition(Vec2(width / 4 - (chisotinnhiem->getWidth() + chisotinnhiem_text->getWidth() + PADDING) / 2,
		userSdt->getPosition().y - userSdt->getHeight() - 5));
	chisotinnhiem_text->setPosition(Vec2(chisotinnhiem->getPosition().x + chisotinnhiem->getWidth() + PADDING,
		chisotinnhiem->getPosition().y));

	//xu
	auto xu_background = MSprite::create("user_info/sprite_hienxuken.png");
	xu_background->setPosition(Vec2(width / 4 - xu_background->getWidth() / 2,
		5 * (chisotinnhiem->getPosition().y - chisotinnhiem->getHeight() / 2) / 6 - xu_background->getHeight() / 2));

	xu_text = MLabel::create("0", xu_background->getHeight() * 0.5f, fontColor);
	xu_text->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	xu_text->setPosition(Vec2(xu_background->getPosition().x + xu_background->getWidth() - 5,
		xu_background->getPosition().y + xu_background->getHeight() / 2));

	auto icon_xu = MSprite::create(TABLE_SPRITE_XU);
	icon_xu->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	icon_xu->setPosition(Vec2(xu_background->getPosition().x + 5,
		xu_background->getPosition().y + xu_background->getHeight() / 2));
	/*icon_xu->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	icon_xu->setPosition(Vec2(xu_background->getPosition().x + xu_background->getWidth(),
		xu_background->getPosition().y + xu_background->getHeight() / 2));*/

	//ken
	auto ken_background = MSprite::create("user_info/sprite_hienxuken.png");
	ken_background->setPosition(Vec2(width / 4 - ken_background->getWidth() / 2,
		(chisotinnhiem->getPosition().y - chisotinnhiem->getHeight() / 2) / 2 - ken_background->getHeight() / 2));

	ken_text = MLabel::create("0", ken_background->getHeight() * 0.5f, fontColor);
	ken_text->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	ken_text->setPosition(Vec2(ken_background->getPosition().x + ken_background->getWidth() - 5,
		ken_background->getPosition().y + ken_background->getHeight() / 2));

	auto icon_ken = MSprite::create(TABLE_SPRITE_KEN);
	icon_ken->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	icon_ken->setPosition(Vec2(ken_background->getPosition().x + 5,
		ken_background->getPosition().y + ken_background->getHeight() / 2));

	//btn change pass
	auto btnChangePassword = MButton::create("user_info/btn_doimatkhau.png", CHANGE_PASSWORD, 20, TAG_CHANGE_PASSWORD);
	btnChangePassword->setPosition(Vec2(width / 4 - btnChangePassword->getWidth() / 2,
		(chisotinnhiem->getPosition().y - chisotinnhiem->getHeight() / 2) / 6 - btnChangePassword->getHeight() / 2));
	btnChangePassword->addTouchEventListener(CC_CALLBACK_2(NodeHoSo::menuPopupCallBack1, this));

	auto sp_outline_sovanchoi = MSprite::create("user_info/sprite_outline.png");
	sp_outline_sovanchoi->setAnchorPoint(Point::ANCHOR_MIDDLE);
	auto sp_outline_sovanthang = MSprite::create("user_info/sprite_outline.png");
	sp_outline_sovanthang->setAnchorPoint(Point::ANCHOR_MIDDLE);
	auto sp_outline_sovanthua = MSprite::create("user_info/sprite_outline.png");
	sp_outline_sovanthua->setAnchorPoint(Point::ANCHOR_MIDDLE);

	sp_outline_sovanchoi->setPosition(Vec2(width - sp_outline_sovanchoi->getWidth() / 2, 5 * height / 6));
	sp_outline_sovanthang->setPosition(Vec2(sp_outline_sovanchoi->getPosition().x, height / 2));
	sp_outline_sovanthua->setPosition(Vec2(sp_outline_sovanchoi->getPosition().x, height / 6));

	//so van choi
	auto spriteSoVanChoi = MSprite::create("user_info/sprite_sovanchoi.png");
	spriteSoVanChoi->setPosition(Vec2(sp_outline_sovanchoi->getWidth() / 4 - spriteSoVanChoi->getWidth() / 2
		, sp_outline_sovanchoi->getHeight() / 2 - spriteSoVanChoi->getHeight() / 2));

	auto sovanchoi = MLabel::create("Số ván chơi", fontSize, fontColor);
	sovanchoi->setPosition(Vec2(0.6 * sp_outline_sovanchoi->getWidth() - sovanchoi->getWidth() / 2,//spriteSoVanChoi->getPosition().x + spriteSoVanChoi->getWidth() * 2,
		spriteSoVanChoi->getPosition().y + spriteSoVanChoi->getHeight() - sovanchoi->getHeight() + PADDING));

	sovanchoi_text = MLabel::create("0", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_SOVANCHOI);
	sovanchoi_text->setPosition(Vec2(sovanchoi->getPosition().x + sovanchoi->getWidth() / 2 - sovanchoi_text->getWidth() / 2,
		sovanchoi->getPosition().y - sovanchoi_text->getHeight()));

	sp_outline_sovanchoi->addChild(spriteSoVanChoi);
	sp_outline_sovanchoi->addChild(sovanchoi);
	sp_outline_sovanchoi->addChild(sovanchoi_text);

	//so van thang
	auto spriteSoVanThang = MSprite::create("user_info/sprite_sovanthang.png");
	spriteSoVanThang->setPosition(Vec2(sp_outline_sovanthang->getWidth() / 4 - spriteSoVanThang->getWidth() / 2
		, sp_outline_sovanthang->getHeight() / 2 - spriteSoVanThang->getHeight() / 2));

	auto sovanthang = MLabel::create("Số ván thắng", fontSize, fontColor);
	sovanthang->setPosition(Vec2(0.6 * sp_outline_sovanthang->getWidth() - sovanthang->getWidth() / 2,
		spriteSoVanThang->getPosition().y + spriteSoVanThang->getHeight() - sovanthang->getHeight() + PADDING));

	sovanthang_text = MLabel::create("0", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_SOVANTHANG);
	sovanthang_text->setPosition(Vec2(sovanthang->getPosition().x + sovanthang->getWidth() / 2 - sovanthang_text->getWidth() / 2,
		sovanthang->getPosition().y - sovanthang_text->getHeight()));

	sp_outline_sovanthang->addChild(spriteSoVanThang);
	sp_outline_sovanthang->addChild(sovanthang);
	sp_outline_sovanthang->addChild(sovanthang_text);

	//so van thua
	auto spriteSoVanThua = MSprite::create("user_info/sprite_sovanthua.png");
	spriteSoVanThua->setPosition(Vec2(sp_outline_sovanthua->getWidth() / 4 - spriteSoVanThua->getWidth() / 2
		, sp_outline_sovanthua->getHeight() / 2 - spriteSoVanThua->getHeight() / 2));

	auto sovanthua = MLabel::create("Số ván thua", fontSize, fontColor);
	sovanthua->setPosition(Vec2(0.6 * sp_outline_sovanthua->getWidth() - sovanthua->getWidth() / 2,
		spriteSoVanThua->getPosition().y + spriteSoVanThua->getHeight() - sovanthua->getHeight() + PADDING));

	sovanthua_text = MLabel::create("0", fontSize, fontEditColor, TAG_POPUP_USERINFO_LBL_SOVANTHUA);
	sovanthua_text->setPosition(Vec2(sovanthua->getPosition().x + sovanthua->getWidth() / 2 - sovanthua_text->getWidth() / 2,
		sovanthua->getPosition().y - sovanthua_text->getHeight()));
	
	sp_outline_sovanthua->addChild(spriteSoVanThua);
	sp_outline_sovanthua->addChild(sovanthua);
	sp_outline_sovanthua->addChild(sovanthua_text);

	this->addChild(userID);
	this->addChild(userID_text);
	this->addChild(userLevel);
	this->addChild(userLevel_text);
	this->addChild(userName_text);
	this->addChild(userSdt);
	this->addChild(userSdt_text);
	this->addChild(btn_edit_phone);
	this->addChild(chisotinnhiem);
	this->addChild(chisotinnhiem_text);
	this->addChild(xu_background);
	this->addChild(icon_xu);
	this->addChild(ken_background);
	this->addChild(ken_text);
	this->addChild(icon_ken);
	this->addChild(xu_text);
	
	this->addChild(sp_outline_sovanchoi);
	this->addChild(sp_outline_sovanthang);
	this->addChild(sp_outline_sovanthua);

	this->addChild(roundAvatar);
	this->addChild(avatar);
	this->addChild(change_avatar);

	this->addChild(btnChangePassword);

    this->scheduleUpdate();
    return true;
}

void NodeHoSo::viewUserInfo(BINUserInfo userInfo){
	CCLOG("xx: %s", userInfo.DebugString().c_str());
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
		userSdt_text->setString(common->getPhoneNumber());
		common->setCash(userInfo.cash());
		common->setGold(userInfo.gold());
	}
	else {
		userSdt_text->setVisible(false);
		userSdt->setVisible(false);
	}

	chisotinnhiem_text->setString(common->convertIntToString(userInfo.trustedindex()));
	sovanchoi_text->setString(common->convertIntToString(userInfo.totalmatch()));
	sovanthang_text->setString(common->convertIntToString(userInfo.totalwin()));
	sovanthua_text->setString(common->convertIntToString(userInfo.totalmatch() - userInfo.totalwin()));
}

void NodeHoSo::menuPopupCallBack1(cocos2d::Ref *sender, ui::Widget::TouchEventType type){
  if (type == ui::Widget::TouchEventType::ENDED) {
    MButton *button = (MButton*)sender;
    int tag = button->getTag();
    auto origin = Director::getInstance()->getVisibleOrigin();
    switch (tag) {
    case TAG_POPUP_USERINFO_BTN_EDIT_SDT:
      CCLOG("%s", "TAG_POPUP_USERINFO_BTN_EDIT_SDT");
		  if (this->getChildByTag(POPUP_TAG_CHANGE_PHONE) == nullptr){
			  auto m_popupEditPhone = PopupChangePhone::create();
			  m_popupEditPhone->setPhone(Common::getInstance()->getPhoneNumber());
			  m_popupEditPhone->setTag(POPUP_TAG_CHANGE_PHONE);
              m_popupEditPhone->setPosition(-origin - this->getPosition());
              addChild(m_popupEditPhone, INDEX_POPUP);
			  m_popupEditPhone->appear();
		  }
      break;
    case TAG_CHANGE_PASSWORD:
      CCLOG("%s", "TAG_CHANGE_PASSWORD");
		  if (this->getChildByTag(POPUP_TAG_CHANGE_PASS) == nullptr){
			  auto m_popupChangePass = PopupChangePass::create();
			  m_popupChangePass->setTag(POPUP_TAG_CHANGE_PASS);
              m_popupChangePass->setPosition(-origin -this->getPosition());
			  addChild(m_popupChangePass, INDEX_POPUP);
			  m_popupChangePass->appear();
		  }
      break;
    default:
      break;
    }
  }
}
void NodeHoSo::update(float delta){
  //handle login
  BINUpdateUserInfoResponse* updateUserInfoResponse = (BINUpdateUserInfoResponse *)Common::getInstance()->checkEvent(NetworkManager::UPDATE_USER_INFO);
  if (updateUserInfoResponse != 0) {
    CCLOG("BINUpdateUserInfoResponse response: %s", updateUserInfoResponse->DebugString().c_str());
    if (updateUserInfoResponse->responsecode()) {
      cocos2d::MessageBox(updateUserInfoResponse->message().c_str(), "Thanh cong");
      userSdt_text->setString(Common::getInstance()->getNewPhone());
      Common::getInstance()->setPhoneNunber(Common::getInstance()->getNewPhone());

	  if (this->getChildByTag(POPUP_TAG_CHANGE_PASS) != nullptr){
		  ((PopupChangePass*)  this->getChildByTag(POPUP_TAG_CHANGE_PASS))->disappear();
	  }

	  if (this->getChildByTag(POPUP_TAG_CHANGE_PHONE) != nullptr){
		  ((PopupChangePhone*)  this->getChildByTag(POPUP_TAG_CHANGE_PHONE))->disappear();
	  }
      //m_popupEditPhone->disappear();
      //m_popupChangePass->disappear();
    }
    else {
      cocos2d::MessageBox(updateUserInfoResponse->message().c_str(), "That bai");
    }
  }
}

void NodeHoSo::changeText(int tag,std::string text){
    MLabel* label = (MLabel*)this->getChildByTag(tag);
    label->setString(text);
}

float NodeHoSo::getWidth(){
    return this->getContentSize().width;
}

float NodeHoSo::getHeight(){
    return this->getContentSize().height;
}

void NodeHoSo::onExit(){
    Node::onExit();
}
