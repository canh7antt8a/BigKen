//
//  PopupChangePhone.cpp
//  
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupChangePass.cpp
#include "PopupChangePass.h"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "Utils/NetworkManager.h"
bool PopupChangePass::init() {
  if (!Popup::init())
    return false;

  backgroundPopup = MSprite::create(IMAGE_POPUP_CHANGE_PASS);
  backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
    visibleSize.height / 2 - backgroundPopup->getHeight() / 2));

  backgroundContentSize = background->getContentSize();

  m_popupLayer->addChild(backgroundPopup);

  auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
  bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
	  backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
  backgroundPopup->addChild(bg_title_popup);

  auto title = Label::createWithTTF(CHANGE_PASS, "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
  title->setColor(Color3B::BLACK);
  title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
	  bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
  bg_title_popup->addChild(title);

  /*auto label = Label::createWithTTF(CHANGE_PASS, "fonts/gamevina.otf", 28);
  label->setPosition( backgroundPopup->getWidth() * 0.5f - label->getWidth()/2
    , backgroundPopup->getHeight()* 0.93f);
  backgroundPopup->addChild(label);*/
  auto background_input_pass = MSprite::create(BGR_INPUT_PASS);
  auto icon_lock = MSprite::create(ICON_LOCK);

  auto sprite_new = MSprite::create(BGR_INPUT_PASS);
  sprite_new->setPosition(Vec2(backgroundPopup->getWidth() / 2 - sprite_new->getWidth()/2,
    backgroundPopup->getHeight()* 0.5f));
  icon_lock->setPosition(Vec2(icon_lock->getWidth() / 2, sprite_new->getHeight() / 2 - icon_lock->getHeight() / 2));
  sprite_new->addChild(icon_lock);
  input_new_pass = MEditBox::create(background_input_pass->getContentSize(), IMAGE_SPOT,
    background_input_pass->getHeight() / 3);
  input_new_pass->setPosition(Vec2(icon_lock->getWidth() * 2, sprite_new->getHeight() / 2 - input_new_pass->getHeight()/2));
  input_new_pass->setMaxLength(12);
  input_new_pass->setPlaceHolder(NEW_PASS_TEXT);
  sprite_new->addChild(input_new_pass);
  input_new_pass->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
  backgroundPopup->addChild(sprite_new);

  auto sprite_old = MSprite::create(BGR_INPUT_PASS);
  sprite_old->setPosition(Vec2(sprite_new->getPosition().x,
    sprite_new->getPosition().y + sprite_new->getHeight() * 1.25f));
  auto icon_lock1 = MSprite::create(ICON_LOCK);
  icon_lock1->setPosition(Vec2(icon_lock->getWidth() / 2, sprite_old->getHeight() / 2 - icon_lock->getHeight() / 2));
  sprite_old->addChild(icon_lock1);
  input_old_pass = MEditBox::create(background_input_pass->getContentSize(), IMAGE_SPOT,
    background_input_pass->getHeight() / 3);
  input_old_pass->setPosition(Vec2(icon_lock->getWidth() * 2, sprite_old->getHeight() / 2 - input_old_pass->getHeight()/2));
  input_old_pass->setMaxLength(12);
  input_old_pass->setPlaceHolder(OLD_PASS_TEXT);
  sprite_old->addChild(input_old_pass);
  input_old_pass->setInputFlag(ui::EditBox::InputFlag::PASSWORD);

  backgroundPopup->addChild(sprite_old);

  auto sprite_confirm = MSprite::create(BGR_INPUT_PASS);
  sprite_confirm->setPosition(Vec2(sprite_new->getPosition().x,
    sprite_new->getPosition().y - sprite_new->getHeight() * 1.25f));
  auto icon_lock2 = MSprite::create(ICON_LOCK);
  icon_lock2->setPosition(Vec2(icon_lock2->getWidth() / 2, sprite_confirm->getHeight() / 2 - icon_lock->getHeight() / 2));
  sprite_confirm->addChild(icon_lock2);

  input_confirm_pass = MEditBox::create(background_input_pass->getContentSize(), IMAGE_SPOT,
    background_input_pass->getHeight() / 3);
  input_confirm_pass->setPosition(Vec2(icon_lock->getWidth() * 2, sprite_confirm->getHeight() / 2 - input_confirm_pass->getHeight() / 2));
  input_confirm_pass->setMaxLength(12);
  input_confirm_pass->setPlaceHolder(CONFIRM_PASS_TEXT);
  sprite_confirm->addChild(input_confirm_pass);
  input_confirm_pass->setInputFlag(ui::EditBox::InputFlag::PASSWORD);

  backgroundPopup->addChild(sprite_confirm);

  auto btn_exit = MButton::create(BUTTON_EXIT, "Thoát", 30, TAG_POPUP_CHANGE_PASS_EXIT);
  btn_exit->setPosition(Vec2(backgroundPopup->getWidth() / 2 - btn_exit->getHeight() / 2 - btn_exit->getWidth(),
    sprite_confirm->getPosition().y / 2 - btn_exit->getHeight() / 2));
  btn_exit->addTouchEventListener(CC_CALLBACK_2(
    PopupChangePass::menuPopupCallBack, this));
  backgroundPopup->addChild(btn_exit);

  auto btn_save = MButton::create(BUTTON_SAVE, "Lưu lại", 30, TAG_POPUP_CHANGE_PASS_SAVE);
  btn_save->setPosition(Vec2(backgroundPopup->getWidth() / 2 + btn_save->getHeight() / 2,
    btn_exit->getPosition().y));
  btn_save->addTouchEventListener(CC_CALLBACK_2(
    PopupChangePass::menuPopupCallBack, this));
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

void PopupChangePass::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED){
    MButton *button = (MButton*)sender;
    int tag = button->getTag();
    switch (tag) {
        case TAG_POPUP_BTN_MUSIC:
          //CCLOG("%s", "Button Music");
            break;
        case TAG_POPUP_CHANGE_PASS_EXIT:
            this->disappear();
            break; 
        case TAG_POPUP_CHANGE_PASS_SAVE:
            {
                CCLOG("getUpdateUserInfoMessageFromServer");
                BINEditingInfo *edit_info = new BINEditingInfo[1];
                edit_info[0].set_infofield(Common::UPDATE_PASSWORD);
                std::string old_pass = input_old_pass->getText();
                std::string new_pass = input_new_pass->getText();
                std::string confirm_pass = input_confirm_pass->getText();
                if (old_pass == "" || new_pass == "" || confirm_pass == ""){
                  cocos2d::MessageBox(BLANK_USERNAME, CHANGE_PASS);
                  return;
                }
                if (new_pass != confirm_pass) {
                  cocos2d::MessageBox(PASSWORD_NOT_MATCH, CHANGE_PASS);
                  return;
                }
                if (old_pass == new_pass) {
                  cocos2d::MessageBox(PASSWORD_NOT_CHANGE, CHANGE_PASS);
                  return;
                }

                if (new_pass.length() < MIN_LENGTH_PASSWORD
                  || new_pass.length() > MAX_LENGTH_PASSWORD){
                  cocos2d::MessageBox(INVALID_PASSWORD, CHANGE_PASS);
                  return;
                }
                edit_info[0].set_oldvalue(old_pass);
                edit_info[0].set_newvalue(new_pass);
                edit_info[0].set_confirmvalue(confirm_pass);
                NetworkManager::getInstance()->getUpdateUserInfoMessageFromServer(edit_info, 1);
                break;
            }

    default:
        break;

    }
  }
}

void PopupChangePass::onExit() {
  Popup::onExit();
}
