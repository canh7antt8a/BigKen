//
//  PopupChangePhone.cpp
//  
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupChangePhone.cpp
#include "PopupChangePhone.h"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "Utils/NetworkManager.h"
bool PopupChangePhone::init() {
  if (!Popup::init())
    return false;

  backgroundPopup = MSprite::create(IMAGE_POPUP_CHANGE_PHONE);
  backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
    visibleSize.height / 2 - backgroundPopup->getHeight() / 2));

  backgroundContentSize = background->getContentSize();

  m_popupLayer->addChild(backgroundPopup);

  auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
  bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
	  backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
  backgroundPopup->addChild(bg_title_popup);

  auto title = Label::createWithTTF(INFO_INPUT, "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
  title->setColor(Color3B::BLACK);
  title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
	  bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
  bg_title_popup->addChild(title);

  auto background_input_phone = MSprite::create(BGR_INPUT_NAME);
  input_phone = MEditBox::create(background_input_phone->getContentSize(), BGR_INPUT_PHONE,
    background_input_phone->getHeight() / 3);
  input_phone->setPosition(Vec2(backgroundPopup->getWidth() / 2 
      - background_input_phone->getWidth() / 2, backgroundPopup->getHeight()* 0.6f));
  input_phone->setText(Common::getInstance()->getPhoneNumber().c_str());
  input_phone->setMaxLength(12);
  backgroundPopup->addChild(input_phone);

  auto btn_exit = MButton::create(BUTTON_EXIT, "Thoat", 30, TAG_POPUP_UNSERINFO_EXIT);
  btn_exit->setPosition(Vec2(backgroundPopup->getWidth() / 2 - btn_exit->getHeight() / 2 - btn_exit->getWidth(),
    btn_exit->getHeight() * 3/2));
  btn_exit->addTouchEventListener(CC_CALLBACK_2(
    PopupChangePhone::menuPopupCallBack, this));
  backgroundPopup->addChild(btn_exit);

  auto btn_save = MButton::create(BUTTON_SAVE, "Luu lai", 30, TAG_POPUP_UNSERINFO_SAVE);
  btn_save->setPosition(Vec2(backgroundPopup->getWidth() / 2 + btn_save->getHeight() / 2,
    btn_exit->getPosition().y));
  btn_save->addTouchEventListener(CC_CALLBACK_2(
    PopupChangePhone::menuPopupCallBack, this));
  backgroundPopup->addChild(btn_save);

  //button close
  auto btn_back = MButton::create(IMAGE_CLOSE);
  btn_back->setZoomScale(0.02f);
  btn_back->setPosition(Vec2(backgroundPopup->getWidth() - btn_back->getWidth() / 2, 
      backgroundPopup->getHeight() - btn_back->getHeight() / 2));
  btn_back->setTag(TAG_POPUP_BTN_BACK);
  backgroundPopup->addChild(btn_back);

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
  return true;
}

void PopupChangePhone::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED){
    MButton *button = (MButton*)sender;
    int tag = button->getTag();
    switch (tag) {
        case TAG_POPUP_BTN_MUSIC:
          //CCLOG("%s", "Button Music");
            break;
        case TAG_POPUP_UNSERINFO_EXIT:
            this->disappear();
            break; 
        case TAG_POPUP_UNSERINFO_SAVE:
            {
                CCLOG("getUpdateUserInfoMessageFromServer");
                BINEditingInfo *edit_info = new BINEditingInfo[1];
                edit_info[0].set_infofield(3);
                std::string phone = input_phone->getText();
                edit_info[0].set_newvalue(phone);
                Common::getInstance()->setNewPhone(phone);
                NetworkManager::getInstance()->getUpdateUserInfoMessageFromServer(edit_info, 1);
                break;
            }

    default:
        break;

    }
  }
}


void PopupChangePhone::setPhone(string phone) {
  input_phone->setText(phone.c_str());
  this->phone = phone;
}
string PopupChangePhone::getPhone() {
  return this->phone;
}

void PopupChangePhone::onExit() {
  Popup::onExit();
}
