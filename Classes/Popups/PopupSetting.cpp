//
//  PopupSetting.cpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupSetting.cpp
#include "PopupSetting.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "Utils/NetworkManager.h"

bool PopupSetting::init() {
  if (!Popup::init())
    return false;

  backgroundPopup = MSprite::create(IMAGE_BG_POPUP_SETTING);
  backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
                                    visibleSize.height / 2 - backgroundPopup->getHeight() / 2));

  backgroundContentSize = background->getContentSize();

  m_popupLayer->addChild(backgroundPopup);

  contentBackground = MSprite::create("content_cai_dat.png");
  contentBackground->setAnchorPoint(Point::ANCHOR_MIDDLE);
  contentBackground->setPosition(Vec2(backgroundPopup->getPosition().x + backgroundPopup->getWidth() / 2
	  , backgroundPopup->getPosition().y + backgroundPopup->getHeight() / 2));
  m_popupLayer->addChild(contentBackground);

  auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
  bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
	  backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
  backgroundPopup->addChild(bg_title_popup);

  auto title = Label::createWithTTF(SETTING_TEXT, "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
  title->setColor(Color3B::BLACK);
  title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
	  bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
  bg_title_popup->addChild(title);

  float width_text = contentBackground->getWidth() * 0.85f;
  float width_icon = contentBackground->getWidth() * 0.8f; // khoang cach den icon
  //Button nhac nen
  std::string _name_png_music = IMAGE_OFF;
  if (getPrefs(MUSIC)){
    _name_png_music = IMAGE_ON;
  }

  auto _button_music = MButton::createExtendsIcon(_name_png_music, MUSIC_TEXT,
    1.5f, TAG_POPUP_BTN_MUSIC, width_text);
  float height_icon = contentBackground->getHeight() * 1 / 12 - _button_music->getHeight() / 2;
  float delta_height = contentBackground->getHeight() * 1 / 6;

  _button_music->setPosition(Vec2(width_icon, height_icon + delta_height * 5));
  _button_music->addTouchEventListener(CC_CALLBACK_2(
    PopupSetting::menuPopupCallBack, this));
  contentBackground->addChild(_button_music, 1);

  // Am thanh
  auto _button_sound = MButton::createExtendsIcon(getImagePrefs(SOUND), SOUND_TEXT,
    1.5f, TAG_POPUP_BTN_SOUND, width_text);
  _button_sound->setPosition(Vec2(width_icon, height_icon + delta_height * 4));
  _button_sound->addTouchEventListener(CC_CALLBACK_2(
    PopupSetting::menuPopupCallBack, this));

  contentBackground->addChild(_button_sound, 1);

  // Rung
  auto _button_vibarte = MButton::createExtendsIcon(getImagePrefs(VIBARTE), VIBARTE_TEXT,
    1.5f, TAG_POPUP_BTN_VIBARTE, width_text);
  _button_vibarte->setPosition(Vec2(width_icon, height_icon + delta_height * 3));
  _button_vibarte->addTouchEventListener(CC_CALLBACK_2(
    PopupSetting::menuPopupCallBack, this));
  contentBackground->addChild(_button_vibarte, 1);

  //tu dong san sang
  auto _button_auto_ready = MButton::createExtendsIcon(getImagePrefs(AUTOREADY),
    AUTO_READY_TEXT, 1.5f, TAG_POPUP_BTN_AUTO_READY, width_text);
  _button_auto_ready->setPosition(Vec2(width_icon, height_icon + delta_height * 2));
  _button_auto_ready->addTouchEventListener(CC_CALLBACK_2(
    PopupSetting::menuPopupCallBack, this));
  contentBackground->addChild(_button_auto_ready, 1);

  //tu choi moi choi
  auto _button_deny_invite = MButton::createExtendsIcon(getImagePrefs(DENY_INVITES),
    DENY_INVITES_TEXT, 1.5f, TAG_POPUP_BTN_DENNY_INVITE, width_text);
  _button_deny_invite->setPosition(Vec2(width_icon, height_icon + delta_height * 1));
  _button_deny_invite->addTouchEventListener(CC_CALLBACK_2(
    PopupSetting::menuPopupCallBack, this));
  contentBackground->addChild(_button_deny_invite, 1);

  //tu dong ngoi xuong
  //auto _button_auto_sit = MButton::createExtendsIcon(getImagePrefs(AUTO_SIT),
  //  AUTO_SIT_TEXT, 1.5f, TAG_POPUP_BTN_AUTO_SIT, width_text);
  //_button_auto_sit->setPosition(Vec2(width_icon, height_icon + delta_height));
  ////_button_deny_invite->setColor(Color3B(0, 0, 0));
  //_button_auto_sit->addTouchEventListener(CC_CALLBACK_2(
  //  PopupSetting::menuPopupCallBack, this));
  //contentBackground->addChild(_button_auto_sit, 1);

  //thong bao trong ban choi
  std::string _name_png_notify_table = IMAGE_OFF;
  auto _button_notify_table = MButton::createExtendsIcon(getImagePrefs(NOTIFY_TANLE_TEXT),
    NOTIFY_TANLE_TEXT, 1.5f, TAG_POPUP_BTN_NOTIFY_TABLE, width_text);
  _button_notify_table->setPosition(Vec2(width_icon, height_icon));
  //_button_deny_invite->setColor(Color3B(0, 0, 0));
  _button_notify_table->addTouchEventListener(CC_CALLBACK_2(
    PopupSetting::menuPopupCallBack, this));
  contentBackground->addChild(_button_notify_table, 1);

  //button close
  auto btn_back = MButton::create();
  btn_back->loadTextureNormal(IMAGE_CLOSE);
  btn_back->setZoomScale(0.02f);
  btn_back->setAnchorPoint(cocos2d::Vec2(0, 0));
  btn_back->setTag(TAG_POPUP_BTN_BACK);

  btn_back->setPosition(Vec2(backgroundPopup->getPosition().x + backgroundPopup->getWidth() - btn_back->getWidth() / 2,
	  backgroundPopup->getPosition().y + backgroundPopup->getHeight() - btn_back->getHeight() / 2));
  m_popupLayer->addChild(btn_back);

  btn_back->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
    switch (type)
    {
    case ui::Widget::TouchEventType::BEGAN:
      break;
    case ui::Widget::TouchEventType::ENDED:
      this->disappear();
      break;
    default:
      break;
    }
  });

  this->scheduleUpdate();

  return true;
}

void PopupSetting::updateUserSettingResponse(){
	BINUpdateUserSettingResponse *response = (BINUpdateUserSettingResponse*) 
		Common::getInstance()->checkEvent(NetworkManager::UPDATE_USER_SETTING);
	if (response != 0){
		CCLOG("update user setting response: %s", response->DebugString().c_str());
		if (response->responsecode() && TAG_BTN_CLICKED != 0){
			if (TAG_BTN_CLICKED == TAG_POPUP_BTN_AUTO_READY){  //tu dong san sang
				PopupSetting::changeOnOffSetting((MButton*)contentBackground->getChildByTag(TAG_BTN_CLICKED), AUTOREADY);
			}
			else if (TAG_BTN_CLICKED == TAG_POPUP_BTN_DENNY_INVITE){  //tu choi loi moi
				PopupSetting::changeOnOffSetting((MButton*)contentBackground->getChildByTag(TAG_BTN_CLICKED), DENY_INVITES);
			}
		}
	}
}

void PopupSetting::update(float){
	updateUserSettingResponse();
}

void PopupSetting::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED){
    MButton *button = (MButton*)sender;
	TAG_BTN_CLICKED = button->getTag();
	switch (TAG_BTN_CLICKED) {
    case TAG_POPUP_BTN_MUSIC:
      //CCLOG("%s", "Button Music");
      PopupSetting::changeOnOffSetting(button, MUSIC);
      break;
    case TAG_POPUP_BTN_AUTO_READY:
      //CCLOG("%s", "AUTOREADY");
	  NetworkManager::getInstance()->getUpdateUserSettingFromServer(!getPrefs(AUTOREADY), getPrefs(DENY_INVITES));
      break;
    case TAG_POPUP_BTN_AUTO_SIT:
      //CCLOG("%s", "AUTO_SIT");
      PopupSetting::changeOnOffSetting(button, AUTO_SIT);
      break;
    case TAG_POPUP_BTN_DENNY_INVITE:
      //CCLOG("%s", "DENY_INVITES");
		NetworkManager::getInstance()->getUpdateUserSettingFromServer(getPrefs(AUTOREADY), !getPrefs(DENY_INVITES));
      break;
    case TAG_POPUP_BTN_SOUND:
      //CCLOG("%s", "SOUND");
      PopupSetting::changeOnOffSetting(button, SOUND);
      break;
    case TAG_POPUP_BTN_VIBARTE:
      //CCLOG("%s", "VIBARTE");
      PopupSetting::changeOnOffSetting(button, VIBARTE);
      break;
    case TAG_POPUP_BTN_NOTIFY_TABLE:
      //CCLOG("%s", "VIBARTE");
      PopupSetting::changeOnOffSetting(button, NOTIFY_TABLE);
      break;
    default:
      break;
    }
  }
}

void PopupSetting::changeOnOffSetting(MButton * button, const char* pkey) {
  if (getPrefs(pkey)){
    CCLOG("%s", "Button Music true");
    setPrefs(pkey, false);
    button->loadTextureNormal(IMAGE_OFF);
  }
  else {
    CCLOG("%s", "Button Music false");
    setPrefs(pkey, true);
    button->loadTextureNormal(IMAGE_ON);
  }
}

void PopupSetting::onExit() {
  Popup::onExit();
}
