//
//  PopupMuaThe.cpp
//  MyCards
//
//  Created by hungle on 6/21/16.
//
//

#include "PopupMuaThe.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "UI/MButton.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"
bool PopupMuaThe::init() {
  if (!Popup::init())
    return false;

  auto underBackground = MSprite::create("under_bkg.png");
  underBackground->setPosition(Vec2(visibleSize.width / 2 - underBackground->getWidth() / 2,
    visibleSize.height / 2 - underBackground->getHeight() / 2));
  m_popupLayer->addChild(underBackground);

  backgroundPopup = MSprite::create(BGR_POP_UP_BUY_CARD);
  backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
    underBackground->getPosition().y + underBackground->getWidth() / 2
    - backgroundPopup->getWidth() / 2));

  backgroundContentSize = background->getContentSize();

  addTab();
  addMenu();
  this->scheduleUpdate();
  return true;
}

void PopupMuaThe::addMenu(){
  btnViettel = MButton::create(LOGO_VIETTEL_ACTIVE);
  btnViettel->setAnchorPoint(Vec2(0, 1));
  btnViettel->setPosition(Vec2(backgroundPopup->getWidth() / 2 - btnViettel->getWidth() * 2,
    backgroundPopup->getHeight() - btnViettel->getHeight() / 4));
  btnViettel->addTouchEventListener(CC_CALLBACK_2(PopupMuaThe::menuPopupCallBack, this));
  btnViettel->setTag(TAG_POPUP_DOITHE_VIETTEL);
  backgroundPopup->addChild(btnViettel);
  type_selected = "VTT";

  btnVinaphone = MButton::create(LOGO_VINAPHONE);
  btnVinaphone->setAnchorPoint(Vec2(0, 1));
  btnVinaphone->setPosition(Vec2(backgroundPopup->getWidth() / 2 - btnVinaphone->getWidth() / 2,
    btnViettel->getPosition().y));
  btnVinaphone->addTouchEventListener(CC_CALLBACK_2(PopupMuaThe::menuPopupCallBack, this));
  btnVinaphone->setTag(TAG_POPUP_DOITHE_VINAPHONE);
  backgroundPopup->addChild(btnVinaphone);

  btnMobiphone = MButton::create(LOGO_MOBIFONE);
  btnMobiphone->setAnchorPoint(Vec2(0, 1));
  btnMobiphone->setPosition(Vec2(backgroundPopup->getWidth() / 2 + btnVinaphone->getWidth(),
    btnVinaphone->getPosition().y));
  btnMobiphone->addTouchEventListener(CC_CALLBACK_2(PopupMuaThe::menuPopupCallBack, this));
  btnMobiphone->setTag(TAG_POPUP_DOITHE_MOBIFONE);
  backgroundPopup->addChild(btnMobiphone);
}

void PopupMuaThe::addTab(){
  float width = backgroundPopup->getWidth();
  float height = backgroundPopup->getHeight();

  for (int i = 0; i<6; i++){
    auto tabSprite = MSprite::create("btn_tabbutton.png");
    tabSprite->setScaleX((width - 6 * 2) / (6 * tabSprite->getWidth()));
    tabSprite->setContentSize(Size((width - 6 * 2) / 6, tabSprite->getHeight()));
    tabSprite->setPosition(Vec2(backgroundPopup->getPosition().x + 2 * (i + 1) + i*(width - 6 * 2) / 6,
      backgroundPopup->getPosition().y + height - 10));
    // m_popupLayer->addChild(tabSprite);
  }

  m_popupLayer->addChild(backgroundPopup);

  tab = MSprite::createExtendsDown(TABLE_SPRITE_TABBUTTION, (width - 6 * 2) / 6);
  tab->setPosition(Vec2(backgroundPopup->getPosition().x + 2,
    backgroundPopup->getPosition().y + height - 10));
  m_popupLayer->addChild(tab);

  vector<std::string> nameTabButton = { "Đổi thẻ cào", "Vật phẩm", "lịch sử đổi thường"};
  vector<int> tagTabButton = { TAG_TABLE_BTN_PHONGCHO, TAG_TABLE_BTN_VIPXU, TAG_TABLE_BTN_KEN, TAG_TABLE_BTN_MUCCUOC,
    TAG_TABLE_BTN_SONGUOI, TAG_TABLE_BTN_KHOA };

  //for (int i = 0; i<6; i++){
  //  auto tabButton = MButton::create("btn_tabbutton_null.png", nameTabButton[i], 30, tagTabButton[i]);
  //  tabButton->setScaleX((width - 6 * 2) / (6 * tabButton->getWidth()));
  //  tabButton->setContentSize(Size((width - 6 * 2) / 6, tabButton->getHeight()));
  //  tabButton->setPosition(Vec2(backgroundPopup->getPosition().x + 2 * (i + 1) + i*(width - 6 * 2) / 6,
  //    backgroundPopup->getPosition().y + height - 10));
  //  tabButton->addTouchEventListener(CC_CALLBACK_2(PopupMuaThe::tabCallBack, this));
  //  m_popupLayer->addChild(tabButton);
  //}
}

void PopupMuaThe::tabCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED){
    MButton *button = (MButton*)sender;
    int tag = button->getTag();
    switch (tag) {
    default:
      break;

    }
  }
}

void PopupMuaThe::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
    }
}

#pragma mark - EditBoxDelegate

void PopupMuaThe::editBoxEditingDidBegin(ui::EditBox *editBox) {
  CCLOG("%s", "edit begin!");
}

void PopupMuaThe::editBoxEditingDidEnd(ui::EditBox *editBox) {

  switch (editBox->getTag()) {
  default:
    break;
  }
}

void PopupMuaThe::editBoxTextChanged(ui::EditBox *editBox, const std::string& text) {
  CCLOG("%s", "edit changed!");
}

void PopupMuaThe::editBoxReturn(ui::EditBox *editBox) {

}

void PopupMuaThe::onExit() {
  Popup::onExit();
}
void PopupMuaThe::update(float delta){
  //handle login
  BINPurchaseMoneyResponse* purchaseMoneyResponse = (BINPurchaseMoneyResponse *)Common::getInstance()->checkEvent(NetworkManager::PURCHASE_MONEY);
  if (purchaseMoneyResponse != 0) {
    CCLOG("purchaseMoneyResponse response: %s", purchaseMoneyResponse->DebugString().c_str());
    if (purchaseMoneyResponse->responsecode()) {
      cocos2d::MessageBox(purchaseMoneyResponse->message().c_str(), "Nạp thẻ thành công");
    
    }
    else {
      cocos2d::MessageBox(purchaseMoneyResponse->message().c_str(), "Thất bại");
    }
  }
}

