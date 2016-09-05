//
//  PopupDoiThe.cpp
//  MyCards
//
//  Created by hungle on 6/21/16.
//
//

#include "PopupDoiThe.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "UI/MButton.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"
bool PopupDoiThe::init() {
  if (!Popup::init())
    return false;

  /*auto underBackground = MSprite::create("under_bkg.png");
  underBackground->setPosition(Vec2(visibleSize.width / 2 - underBackground->getWidth() / 2,
    visibleSize.height / 2 - underBackground->getHeight() / 2));
  m_popupLayer->addChild(underBackground);*/

  backgroundPopup = MSprite::create("common_popup/bg_popup.png");
  backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
	  visibleSize.height / 2 - backgroundPopup->getHeight() / 2));

  m_popupLayer->addChild(backgroundPopup);

  /*backgroundPopup = MSprite::create(BGR_POPUP_DOITHE);
  backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
    underBackground->getPosition().y + underBackground->getWidth() / 2
    - backgroundPopup->getWidth() / 2));*/

  backgroundContentSize = background->getContentSize();

  auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
  bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
	  backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
  backgroundPopup->addChild(bg_title_popup);

  auto title = Label::createWithTTF("ĐỔI THẺ", "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
  title->setColor(Color3B::BLACK);
  title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
	  bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
  bg_title_popup->addChild(title);

  auto sprite_arrow_right = MSprite::create("common_popup/icon_arrow_right.png");
  contentPopupLeft = MSprite::create("common_popup/content_popup_left.png");

  contentPopupRight = MSprite::create("common_popup/content_popup_right.png");
  padding_left = (backgroundPopup->getWidth() - (sprite_arrow_right->getWidth() + contentPopupLeft->getWidth()
	  + contentPopupRight->getWidth())) / 2;

  contentPopupLeft->setPosition(Vec2(padding_left, backgroundPopup->getHeight() / 2 - contentPopupLeft->getHeight() / 2));
  contentPopupRight->setPosition(Vec2(padding_left + contentPopupLeft->getWidth() + sprite_arrow_right->getWidth(),
	  backgroundPopup->getHeight() / 2 - contentPopupRight->getContentSize().height / 2));

  backgroundPopup->addChild(contentPopupLeft);
  backgroundPopup->addChild(contentPopupRight);

  addTab();
  addMenu();

  //btn close
  auto exit = MButton::create(IMAGE_CLOSE, TAG_POPUP_BTN_BACK);
  exit->setPosition(Vec2(backgroundPopup->getWidth() - exit->getWidth() / 2,
	  backgroundPopup->getHeight() - exit->getHeight() / 2));
  exit->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::menuPopupCallBack, this));
  backgroundPopup->addChild(exit);

  this->scheduleUpdate();
  return true;
}

void PopupDoiThe::addMenu(){

  btnViettel = MButton::create(LOGO_VIETTEL_ACTIVE);
  btnViettel->setAnchorPoint(Vec2(0, 1));
  btnViettel->setPosition(Vec2(contentPopupRight->getWidth() / 2 - btnViettel->getWidth() * 2,
    contentPopupRight->getHeight() - btnViettel->getHeight()/4));
  btnViettel->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::menuPopupCallBack, this));
  btnViettel->setTag(TAG_POPUP_DOITHE_VIETTEL);
  contentPopupRight->addChild(btnViettel);
  type_selected = "VTT";

  btnVinaphone = MButton::create(LOGO_VINAPHONE);
  btnVinaphone->setAnchorPoint(Vec2(0, 1));
  btnVinaphone->setPosition(Vec2(contentPopupRight->getWidth() / 2 - btnVinaphone->getWidth() / 2,
    btnViettel->getPosition().y));
  btnVinaphone->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::menuPopupCallBack, this));
  btnVinaphone->setTag(TAG_POPUP_DOITHE_VINAPHONE);
  contentPopupRight->addChild(btnVinaphone);

  btnMobiphone = MButton::create(LOGO_MOBIFONE);
  btnMobiphone->setAnchorPoint(Vec2(0, 1));
  btnMobiphone->setPosition(Vec2(contentPopupRight->getWidth() / 2 + btnVinaphone->getWidth(),
    btnVinaphone->getPosition().y));
  btnMobiphone->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::menuPopupCallBack, this));
  btnMobiphone->setTag(TAG_POPUP_DOITHE_MOBIFONE);
  contentPopupRight->addChild(btnMobiphone);

  auto sprite_tigia = MSprite::create("doi_the/sprite_tigia.png");
  contentPopupRight->addChild(sprite_tigia);

  // Textfield mat khau
  auto background_seria = MSprite::create(BGR_INPUT_TEXT);

  float padding_top = ((btnViettel->getPosition().y - btnViettel->getHeight() - 10 - sprite_tigia->getHeight()) / 3 - background_seria->getHeight()) / 2;

  auto background_captcha = MSprite::create(BGR_INPUT_CAPTCHA);
  input_captcha = MEditBox::create(background_captcha->getContentSize(), BGR_INPUT_TEXT,
	  background_captcha->getHeight() / 3);
  input_captcha->setPosition(Vec2(50, sprite_tigia->getPosition().y + sprite_tigia->getHeight() + padding_top));
  input_captcha->setPlaceHolder(" Kết quả");
  input_captcha->setMaxLength(15);
  input_captcha->setTag(TAG_POPUP_DOITHE_CAPTCHA);
  contentPopupRight->addChild(input_captcha);

  //ma the
  input_mathe = MEditBox::create(background_seria->getContentSize(), BGR_INPUT_TEXT,
	  background_seria->getHeight() / 3);
  input_mathe->setPosition(Vec2(input_captcha->getPosition().x,
	  input_captcha->getPosition().y + background_seria->getHeight() + padding_top));
  input_mathe->setPlaceHolder(" Mã thẻ");
  input_mathe->setMaxLength(15);
  input_mathe->setTag(TAG_POPUP_DOITHE_MATHE);
  //input_mathe->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
  input_mathe->setDelegate(this);
  contentPopupRight->addChild(input_mathe);

  //so seri
  input_seria = MEditBox::create(background_seria->getContentSize(), BGR_INPUT_TEXT,
	  background_seria->getHeight() / 3);
  input_seria->setPosition(Vec2(input_captcha->getPosition().x, input_mathe->getPosition().y + background_seria->getHeight() + padding_top));
  input_seria->setPlaceHolder(" Số seria");
  input_seria->setMaxLength(15);
  input_seria->setTag(TAG_POPUP_DOITHE_SERIA);
  //input_seria->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
  input_seria->setDelegate(this);
  contentPopupRight->addChild(input_seria);
  

  captcha = MLabel::createWithBitmapFont("", "font_capchaz.fnt");

  auto reload_captcha = MButton::create(ICON_RELOAD_CAPTCHA);
  reload_captcha->setPosition(Vec2(input_mathe->getPosition().x + background_seria->getWidth() - reload_captcha->getWidth(), input_captcha->getPosition().y));
  reload_captcha->setTag(TAG_POPUP_DOITHE_RELOAD_CAPTCHA);
  reload_captcha->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::menuPopupCallBack, this));
  contentPopupRight->addChild(reload_captcha);
  
  background_captcha->setPosition(Vec2(reload_captcha->getPosition().x - background_captcha->getWidth(), reload_captcha->getPosition().y));
  contentPopupRight->addChild(background_captcha);

  captcha->setAnchorPoint(Vec2(0.5, 0.5));
  captcha->setPosition(Vec2(background_captcha->getWidth() / 2, background_captcha->getHeight()));
  background_captcha->addChild(captcha);

  auto btn_napthe = MButton::create("btn_taoban.png", "Nạp", 30, TAG_POPUP_DOITHE_BTN_NAPTHE);
  btn_napthe->setPosition(Vec2(input_mathe->getPosition().x / 2 + background_seria->getWidth() / 2 - btn_napthe->getWidth() / 2,
	  input_captcha->getPosition().y / 2 - btn_napthe->getHeight() / 2));
  btn_napthe->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::menuPopupCallBack, this));
  contentPopupRight->addChild(btn_napthe);

  //auto seria_bkg = MSprite::create(BGR_DOITHE);
  //seria_bkg->setPosition(Vec2(contentPopupRight->getWidth() / 2 - seria_bkg->getWidth() / 2,
  //  btnVinaphone->getPosition().y / 2 - btnVinaphone ->getHeight()/2 - seria_bkg->getHeight() / 2));
  //contentPopupRight->addChild(seria_bkg);

  //// Textfield mat khau
  //auto background_seria = MSprite::create(BGR_INPUT_TEXT);

  //input_seria = MEditBox::create(background_seria->getContentSize(), BGR_INPUT_TEXT,
  //  background_seria->getHeight() / 3);
  //input_seria->setPosition(Vec2(seria_bkg->getWidth() / 2 - background_seria->getWidth(),
  //  seria_bkg->getHeight() / 2 - 10));
  //input_seria->setPlaceHolder("  Số seria");
  //input_seria->setMaxLength(15);
  //input_seria->setTag(TAG_POPUP_DOITHE_SERIA);
  ////input_seria->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
  //input_seria->setDelegate(this);
  //seria_bkg->addChild(input_seria);

  //input_mathe = MEditBox::create(background_seria->getContentSize(), BGR_INPUT_TEXT,
  //  background_seria->getHeight() / 3);
  //input_mathe->setPosition(Vec2(input_seria->getPosition().x,
  //  seria_bkg->getHeight() / 2 + background_seria->getHeight()*1.25f));
  //input_mathe->setPlaceHolder("  Mã thẻ");
  //input_mathe->setMaxLength(15);
  //input_mathe->setTag(TAG_POPUP_DOITHE_MATHE);
  ////input_mathe->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
  //input_mathe->setDelegate(this);
  //seria_bkg->addChild(input_mathe);

  //auto background_captcha = MSprite::create(BGR_INPUT_CAPTCHA);

  //input_captcha = MEditBox::create(background_captcha->getContentSize(), BGR_INPUT_TEXT,
  //  background_seria->getHeight() / 3);
  //input_captcha->setPosition(Vec2(input_mathe->getPosition().x,
  //  2 * input_seria->getPosition().y - input_mathe->getPosition().y));
  //input_captcha->setPlaceHolder("  Kết quả");
  //input_captcha->setMaxLength(15);
  //input_captcha->setTag(TAG_POPUP_DOITHE_CAPTCHA);
  //seria_bkg->addChild(input_captcha);

  //captcha = MLabel::createWithBitmapFont("", "font_capchaz.fnt");
  //  
  //auto reload_captcha = MButton::create(ICON_RELOAD_CAPTCHA);
  //reload_captcha->setPosition(Vec2(input_mathe->getPosition().x + background_seria->getWidth() - reload_captcha->getWidth(), input_captcha->getPosition().y));
  //reload_captcha->setTag(TAG_POPUP_DOITHE_RELOAD_CAPTCHA);
  //reload_captcha->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::menuPopupCallBack, this));
  //seria_bkg->addChild(reload_captcha);
  //background_captcha->setPosition(Vec2(reload_captcha->getPosition().x - background_captcha->getWidth(), reload_captcha->getPosition().y));
  //seria_bkg->addChild(background_captcha);

  //captcha->setAnchorPoint(Vec2(0.5, 0.5));
  //captcha->setPosition(Vec2(background_captcha->getWidth() / 2, background_captcha->getHeight()));
  //background_captcha->addChild(captcha);

  //auto btn_napthe = MButton::create("btn_taoban.png", "Nạp", 30, TAG_POPUP_DOITHE_BTN_NAPTHE);
  //btn_napthe->setPosition(Vec2(input_mathe->getPosition().x / 2 + background_seria->getWidth() / 2 - btn_napthe->getWidth() / 2,
  //  input_captcha->getPosition().y / 2 - btn_napthe->getHeight() / 2));
  //btn_napthe->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::menuPopupCallBack, this));
  //seria_bkg->addChild(btn_napthe);
}

void PopupDoiThe::addTab(){
  /*float width = backgroundPopup->getWidth();
  float height = backgroundPopup->getHeight();

  for (int i = 0; i<6; i++){
    auto tabSprite = MSprite::create("btn_tabbutton.png");
    tabSprite->setScaleX((width - 6 * 2) / (6 * tabSprite->getWidth()));
    tabSprite->setContentSize(Size((width - 6 * 2) / 6, tabSprite->getHeight()));
    tabSprite->setPosition(Vec2(backgroundPopup->getPosition().x + 2 * (i + 1) + i*(width - 6 * 2) / 6,
      backgroundPopup->getPosition().y + height - 10));
    m_popupLayer->addChild(tabSprite);
  }

  m_popupLayer->addChild(backgroundPopup);

  tab = MSprite::createExtendsDown(TABLE_SPRITE_TABBUTTION, (width - 6 * 2) / 6);
  tab->setPosition(Vec2(backgroundPopup->getPosition().x + 2,
    backgroundPopup->getPosition().y + height - 10));
  m_popupLayer->addChild(tab);

  vector<std::string> nameTabButton = { "Thẻ Cào", "SMS", "9092", "IAP", "Đổi Xu", "KEN Free" };
  vector<int> tagTabButton = { TAG_TABLE_BTN_PHONGCHO, TAG_TABLE_BTN_VIPXU, TAG_TABLE_BTN_KEN, TAG_TABLE_BTN_MUCCUOC,
    TAG_TABLE_BTN_SONGUOI, TAG_TABLE_BTN_KHOA };

  for (int i = 0; i<6; i++){
    auto tabButton = MButton::create("btn_tabbutton_null.png", nameTabButton[i], 30, tagTabButton[i]);
    tabButton->setScaleX((width - 6 * 2) / (6 * tabButton->getWidth()));
    tabButton->setContentSize(Size((width - 6 * 2) / 6, tabButton->getHeight()));
    tabButton->setPosition(Vec2(backgroundPopup->getPosition().x + 2 * (i + 1) + i*(width - 6 * 2) / 6,
      backgroundPopup->getPosition().y + height - 10));
    tabButton->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::tabCallBack, this));
    m_popupLayer->addChild(tabButton);
  }*/

	auto spriteTab = MSprite::create("common_popup/tab_click.png");
	heightTab = spriteTab->getHeight();
	float posX = contentPopupLeft->getPosition().x + contentPopupLeft->getWidth() / 2 - spriteTab->getWidth() / 2;

	string rs_tab;
	for (int i = 0; i<1; i++){
		if (i == 0){
			rs_tab = "common_popup/tab_click_round.png";
		}
		else {
			rs_tab = "common_popup/tab_click.png";
		}
		auto tabSprite = MSprite::create(rs_tab);
		tabSprite->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - (heightTab)*(i + 1)));
		backgroundPopup->addChild(tabSprite);
	}

	tab = MSprite::create("common_popup/tab_clicked_round.png");
	tab->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - heightTab));
	backgroundPopup->addChild(tab);

	vector<std::string> nameTabButton = { "Thẻ Cào" };
	vector<int> tagTabButton = { 1 };

	for (int i = 0; i<1; i++){ ///sprite tab null
		auto tabButton = MButton::create("common_popup/tab_click_null.png", nameTabButton[i], tab->getWidth() / 3, tagTabButton[i]);
		tabButton->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - (heightTab)*(i + 1)));
		tabButton->addTouchEventListener(CC_CALLBACK_2(PopupDoiThe::tabCallBack, this));
		backgroundPopup->addChild(tabButton);
	}

}

void PopupDoiThe::tabCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED){
    MButton *button = (MButton*)sender;
    int tag = button->getTag();
    switch (tag) {
    default:
      break;

    }
  }
}

void PopupDoiThe::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_POPUP_DOITHE_BTN_NAPTHE:
                {
                    std::string seria_text = input_seria->getText();
                    std::string mathe_text = input_mathe->getText(); 
                    std::string captcha_string = input_captcha->getText();
                    CCLOG("TAG_POPUP_DOITHE_BTN_NAPTHE  %s ",this->getSecurityKey().c_str());
                    if (captcha_string == "" || mathe_text == "" || seria_text == ""){
                      cocos2d::MessageBox(BLANK_USERNAME, "Nạp thẻ");
                      return;
                    }
                    if (seria_text.length() < MIN_LENGTH_SERIA || seria_text.length() > MAX_LENGTH_SERIA
                      || mathe_text.length() < MIN_LENGTH_SERIA || mathe_text.length() > MAX_LENGTH_SERIA){
                      cocos2d::MessageBox(INVALID_SERIA, "Nạp thẻ");
                      return;
                    }
                    NetworkManager::getInstance()->getPurchaseMoneyMessageFromServer(type_selected,
                      seria_text, mathe_text, this->getSecurityKey().c_str(), captcha_string,
                          true);
                }
                break;
            case TAG_POPUP_DOITHE_VINAPHONE:
                {
                                          CCLOG("%s", "LOGO_VINAPHONE_ACTIVE");
                    btnVinaphone->loadTextureNormal(LOGO_VINAPHONE_ACTIVE);
                    btnViettel->loadTextureNormal(LOGO_VIETTEL);
                    btnMobiphone->loadTextureNormal(LOGO_MOBIFONE);
                    type_selected = "VNP";
                }
                break;
            case TAG_POPUP_DOITHE_MOBIFONE:
                {
                    CCLOG("%s", "LOGO_MOBIFONE_ACTIVE");

                    btnVinaphone->loadTextureNormal(LOGO_VINAPHONE);
                    btnViettel->loadTextureNormal(LOGO_VIETTEL);
                    btnMobiphone->loadTextureNormal(LOGO_MOBIFONE_ACTIVE);
                    type_selected = "VMS";

                }
                break;
            case TAG_POPUP_DOITHE_VIETTEL:
                {
                    CCLOG("%s", "LOGO_VIETTEL_ACTIVE");

                    btnVinaphone->loadTextureNormal(LOGO_VINAPHONE);
                    btnViettel->loadTextureNormal(LOGO_VIETTEL_ACTIVE);
                    btnMobiphone->loadTextureNormal(LOGO_MOBIFONE);
                    type_selected = "VTT";

                }
                break;
            case TAG_POPUP_DOITHE_RELOAD_CAPTCHA:
                {
                    CCLOG("%s", "TAG_POPUP_DOITHE_RELOAD_CAPTCHA");
                    NetworkManager::getInstance()->getCaptchaMessageFromServer(true);
                }
			case TAG_POPUP_BTN_BACK:
				this->disappear();
				break;
            default:
              break;
        }
    }
}

#pragma mark - EditBoxDelegate

void PopupDoiThe::editBoxEditingDidBegin(ui::EditBox *editBox) {
  CCLOG("%s", "edit begin!");
}

void PopupDoiThe::editBoxEditingDidEnd(ui::EditBox *editBox) {

  switch (editBox->getTag()) {
  default:
    break;
  }
}

void PopupDoiThe::editBoxTextChanged(ui::EditBox *editBox, const std::string& text) {
  CCLOG("%s", "edit changed!");
}

void PopupDoiThe::editBoxReturn(ui::EditBox *editBox) {

}

void PopupDoiThe::onExit() {
  Popup::onExit();
}
void PopupDoiThe::update(float delta){
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

PopupDoiThe* PopupDoiThe::createPopup(string captcha_text, string security_key) {
  auto popup = PopupDoiThe::create();
  popup->setCaptchaText(captcha_text);
  popup->setSecurityKey(security_key);

  return popup;
}

void PopupDoiThe::setCaptchaText(string captcha_text) {
  this->captcha_text = captcha_text;
  CCLOG("catpcha text: %s", captcha_text.c_str());
  captcha->setString(captcha_text);
}
string PopupDoiThe::getCaptchaText() {
  return this->captcha_text;
}
void PopupDoiThe::setSecurityKey(string security_key) {
  this->security_key = security_key;
}
string PopupDoiThe::getSecurityKey() {
  return this->security_key;
}

