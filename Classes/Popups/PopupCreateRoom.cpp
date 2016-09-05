//
//  PopupSetting.cpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupCreateRoom.cpp
#include "PopupCreateRoom.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"
#include <vector>
#include "UI/MButton.hpp"
#include "UI/MText.hpp"
using namespace std;
using namespace cocos2d;

bool PopupCreateRoom::init() {
  if (!Popup::init())
    return false;

  backgroundPopup = MSprite::create(POPUP_CREATE_ROOM);
  backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
    visibleSize.height / 2 - backgroundPopup->getHeight() / 2));

  backgroundContentSize = backgroundPopup->getContentSize();

  m_popupLayer->addChild(backgroundPopup);

  auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
  bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
	  backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
  backgroundPopup->addChild(bg_title_popup);

  auto title = Label::createWithTTF(CREATE_ROOM_TEXT, "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
  title->setColor(Color3B::BLACK);
  title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
	  bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
  bg_title_popup->addChild(title);

  auto btn_create_room = MButton::create(ICON_BTN_OK, CR_ROOM_BTN_OK, 30, TAG_TLMN_CREATE_ROOM);
  btn_create_room->setPosition(Vec2(backgroundPopup->getWidth()/2 - btn_create_room->getWidth() / 2,
    btn_create_room->getHeight()* 2/3));
  backgroundPopup->addChild(btn_create_room);
  btn_create_room->addTouchEventListener(CC_CALLBACK_2(PopupCreateRoom::menuPopupCallBack, this));

  auto money_cuoc_20K = MSprite::create(ICON_XU_DEACTIVE);
  //float padding = btn_create_room->getHeight() * 1 / 3;

  /*auto label = MLabel::create(CREATE_ROOM_TEXT, backgroundPopup->getHeight()*0.05f);
  label->setAnchorPoint(cocos2d::Vec2(0, 0));
  label->setPosition(Vec2(backgroundPopup->getWidth() / 2 - label->getWidth() / 2,
    backgroundPopup->getHeight() * 9.1f / 10));
  backgroundPopup->addChild(label);*/
  //tao ban
  float padding_width = money_cuoc_20K->getHeight();
  auto label_loaiban = MLabel::create(CR_ROOM_SELECT, backgroundPopup->getHeight()*0.04f);
  label_loaiban->setPosition(Vec2(padding_width, backgroundPopup->getHeight() * 0.78f));
  backgroundPopup->addChild(label_loaiban);

//ten phong
  auto background_tenphong = MSprite::create(BGR_INPUT_NAME);
  auto edit_tenphong = MEditBox::create(background_tenphong->getContentSize(), BGR_INPUT_NAME,
    background_tenphong->getHeight() / 3);
  input_password = MEditBox::create(background_tenphong->getContentSize(), BGR_INPUT_NAME,
    background_tenphong->getHeight() / 3);

//button tao ban thuong
  gold_button = MButton::create(BGR_TABLE_DEACTVE, GOLD_TABLE_TEXT, 30, TAG_TLMN_CREATE_ROOM_GOLD);
  cash_button = MButton::create(BGR_TABLE_DEACTVE, CASH_TABLE_TEXT, 30, TAG_TLMN_CREATE_ROOM_CASH);

  gold_button->loadTextureNormal(BGR_TABLE_ACTVE);
  gold_button->setPosition(Vec2(money_cuoc_20K->getHeight()* 1.2f + money_cuoc_20K->getWidth(),
    label_loaiban->getPosition().y - gold_button->getHeight() / 2 + label_loaiban->getHeight()/2));
  backgroundPopup->addChild(gold_button);

  cash_button->setPosition(Vec2(gold_button->getPosition().x + background_tenphong->getWidth() - cash_button->getWidth(), gold_button->getPosition().y));
  backgroundPopup->addChild(cash_button);
  auto icon_vip = MSprite::create(ICON_VIP);
  icon_vip->setPosition(Vec2(cash_button->getWidth() / 7, cash_button->getHeight() / 2 - icon_vip->getHeight() / 2));
  cash_button->addChild(icon_vip);
  gold_button->addTouchEventListener(CC_CALLBACK_2(PopupCreateRoom::menuPopupCallBack, this));
  cash_button->addTouchEventListener(CC_CALLBACK_2(PopupCreateRoom::menuPopupCallBack, this));

  is_vip_room = false;

  input_password->setPosition(Vec2(gold_button->getPosition().x, backgroundPopup->getHeight() * 0.5f));
  input_password->setPlaceHolder(CR_ROOM_INPUT_PASSWORD);
  input_password->setMaxLength(12);
  backgroundPopup->addChild(input_password);

  edit_tenphong->setPosition(Vec2(gold_button->getPosition().x, gold_button->getPosition().y/2 + input_password->getPosition().y/2));
  edit_tenphong->setPlaceHolder(CR_ROOM_INPUT_ROOMNAME);
  edit_tenphong->setMaxLength(12);
  backgroundPopup->addChild(edit_tenphong);

  auto label_tenphong = MLabel::create(CR_ROOM_ROOMNAME, backgroundPopup->getHeight()*0.04f);
  label_tenphong->setPosition(Vec2(padding_width, edit_tenphong->getPosition().y + edit_tenphong->getHeight() / 2 - label_tenphong->getHeight()/2));
  backgroundPopup->addChild(label_tenphong);
  auto label_password = MLabel::create(CR_ROOM_PASSWORD, backgroundPopup->getHeight()*0.04f);
  label_password->setPosition(Vec2(padding_width, input_password->getPosition().y + input_password->getHeight() / 2 - label_password->getHeight() / 2));
  backgroundPopup->addChild(label_password);

  auto goldRoomList = Common::getInstance()->getGoldRoomList();

  //top = input_password->getPosition().y / 2 + btn_create_room->getPosition().y / 2 + btn_create_room->getHeight() / 2;
  
  height = money_cuoc_20K->getHeight();
  int row_cuoc = ((int)goldRoomList.size() - 1) / 4 + 1;
  float delta = ((input_password->getPosition().y - (btn_create_room->getPosition().y + btn_create_room->getHeight())) / row_cuoc - height) / 2;
  top = input_password->getPosition().y - 2*delta - height; //input_password->getPosition().y - btn_create_room->getHeight() - 10;

  showGoldBet(goldRoomList, money_cuoc_20K, top, height);

  this->canCreateRoom = true;
  //button close
  auto btn_close = MButton::create();
  btn_close->loadTextureNormal(IMAGE_CLOSE);
  btn_close->setZoomScale(0.02f);
  btn_close->setAnchorPoint(cocos2d::Vec2(0, 0));
  btn_close->setTag(TAG_POPUP_BTN_BACK);
  btn_close->setPosition(Vec2(backgroundPopup->getWidth() - btn_close->getWidth() / 2,
	  backgroundPopup->getHeight() - btn_close->getHeight() / 2));
  backgroundPopup->addChild(btn_close);

  btn_close->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
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

void PopupCreateRoom::showGoldBet(vector<BINRoomConfig> goldRoomList, MSprite* itemRow, float top, float height){
  auto cashRoomList = Common::getInstance()->getCashRoomList();
  for (int i = 0; i < cashRoomList.size(); i++){
    if (backgroundPopup->getChildByTag(TAG_TLMN_CREATE_ROOM_BET + i) != nullptr){
      backgroundPopup->removeChildByTag(TAG_TLMN_CREATE_ROOM_BET + i);
    }
  }

  float padding_height = itemRow->getHeight() / 2;
  float padding_width_c = (backgroundPopup->getWidth() - 4 * itemRow->getWidth() - itemRow->getHeight() * 2) / 3;
  int row_cuoc = ((int)goldRoomList.size() - 1) / 4 + 1;

  CCLOG("so dong cuoc: %d", row_cuoc);
  float y_top = top + (row_cuoc - 1) * (itemRow->getHeight() / 4);

  for (int i = 0; i < goldRoomList.size(); i++)
  {
    auto money_cuoc = MButton::createWithIcon(i == 0 ? ICON_XU_ACTIVE : ICON_XU_DEACTIVE, ICON_KEN, Common::getInstance()->convertIntToMoneyView(goldRoomList[i].minbet()), 30, TAG_TLMN_CREATE_ROOM_BET + i);
    money_cuoc->setPosition(Vec2(itemRow->getHeight() + (i % 4) * (padding_width_c + money_cuoc->getWidth()),
      y_top - (height + padding_height) * (int(i / 4))));
    CCLOG("so dong cuoc: %d", goldRoomList[i].minbet());
    backgroundPopup->addChild(money_cuoc);
    money_cuoc->addTouchEventListener(CC_CALLBACK_2(PopupCreateRoom::moneyPopupCallBack, this));
    if (i == 0){
        active_bet = i;
        button_active = money_cuoc;
    }
  }
}

void PopupCreateRoom::showCashBet(vector<BINRoomConfig> cashRoomList, MSprite* itemRow, float top, float height){
   auto goldRoomList = Common::getInstance()->getGoldRoomList();
   for (int i = 0; i < goldRoomList.size(); i++){
    if (backgroundPopup->getChildByTag(TAG_TLMN_CREATE_ROOM_BET + i) != nullptr){
        backgroundPopup->removeChildByTag(TAG_TLMN_CREATE_ROOM_BET + i);
    }
  }

  float padding_height = itemRow->getHeight() / 2;
  float padding_width_c = (backgroundPopup->getWidth() - 4 * itemRow->getWidth() - itemRow->getHeight() * 2) / 3;
  int row_cuoc = ((int)cashRoomList.size() - 1) / 4 + 1;
  CCLOG("so dong cuoc: %d", row_cuoc);
  float y_top = top + (row_cuoc - 1) * (itemRow->getHeight() / 4);

  for (int i = 0; i < cashRoomList.size(); i++)
  {
	auto money_cuoc = MButton::createWithIcon(i == 0 ? ICON_XU_ACTIVE : ICON_XU_DEACTIVE, SPRITE_XU, Common::getInstance()->convertIntToMoneyView(cashRoomList[i].minbet()), 30, TAG_TLMN_CREATE_ROOM_BET + i);
    money_cuoc->setPosition(Vec2(itemRow->getHeight() + (i % 4) * (padding_width_c + money_cuoc->getWidth()),
      y_top - (height + padding_height) * (int(i / 4))));
    CCLOG("so dong cuoc: %d", cashRoomList[i].minbet());
    backgroundPopup->addChild(money_cuoc);
    money_cuoc->addTouchEventListener(CC_CALLBACK_2(PopupCreateRoom::moneyPopupCallBack, this));
    if (i == 0){
        active_bet = i;
        button_active = money_cuoc;
    }
  }
}

void PopupCreateRoom::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED){
    MButton *button = (MButton*)sender;
    int tag = button->getTag();
    switch (tag) {
    case TAG_TLMN_CREATE_ROOM:
        CCLOG("%s", "TAG_TLMN_CREATE_ROOM");
        {
            std::string pass_word = input_password->getText();
            vector<BINRoomConfig> roomType;
            if (is_vip_room){
                roomType = Common::getInstance()->getCashRoomList();
            }
            else {
                roomType = Common::getInstance()->getGoldRoomList();
            }

			if (!roomType.empty() && active_bet < roomType.size()){
				BINRoomConfig roomGroup = roomType.at(active_bet);
                if (roomGroup.has_roomgroupid()){
                    //lay ra tien cuoc
					int minbet = roomGroup.minbet();
					int room_group_id = roomGroup.roomgroupid();
					int player_size = roomGroup.playersize();
                    NetworkManager::getInstance()->
                        getCreateRoomMessageFromServer(Common::getInstance()->getZoneId(),
						room_group_id,
						is_vip_room, minbet, player_size, pass_word);
                }
            }
            else {
                CCLOG("PopupCreateRoom: click btn create room -> khong ton tai danh sach phong");
            }
            
        }
        break;
    case TAG_TLMN_CREATE_ROOM_GOLD:
        {
            CCLOG("%s", "TAG_TLMN_CREATE_ROOM_GOLD true");
            button->loadTextureNormal(BGR_TABLE_ACTVE);
            cash_button->loadTextureNormal(BGR_TABLE_DEACTVE);
            is_vip_room = false;
            auto goldRoomList = Common::getInstance()->getGoldRoomList();
            auto itemRow = MSprite::create(ICON_XU_DEACTIVE);
            showGoldBet(goldRoomList, itemRow, top, height);
        }
    
        break;
    case TAG_TLMN_CREATE_ROOM_CASH:
    {
            CCLOG("%s", "TAG_TLMN_CREATE_ROOM_CASH true");
            button->loadTextureNormal(BGR_TABLE_ACTVE);
            gold_button->loadTextureNormal(BGR_TABLE_DEACTVE);
            is_vip_room = true;
            auto cashRoomList = Common::getInstance()->getCashRoomList();
            auto itemRow = MSprite::create(ICON_XU_DEACTIVE);
            showCashBet(cashRoomList, itemRow, top, height);
    }
        break;
    default:
      break;
    }
  }

}
void PopupCreateRoom::moneyPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED){
    MButton *button = (MButton*)sender;
    int tag = button->getTag() - TAG_TLMN_CREATE_ROOM_BET;
    CCLOG("%s", "TAG_TLMN_CREATE_ROOM_GOLD true");
    if (button != button_active)
        {
            button->loadTextureNormal(ICON_XU_ACTIVE);
            active_bet = tag;
            button_active->loadTextureNormal(ICON_XU_DEACTIVE);
            button_active = button;
        }
    }
}

void PopupCreateRoom::onExit() {
  Popup::onExit();
}
