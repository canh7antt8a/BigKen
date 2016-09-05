//
//  PasswordPopup.cpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 6/11/16.
//
//

#include "PasswordPopup.hpp"
#include "Utils/Image.h"
#include "UI/MButton.hpp"
#include "UI/MLabel.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Utils/NetworkManager.h"

bool PasswordPopup::init() {
    if (!Popup::init())
        return false;
    this->setAnchorPoint(Point::ZERO);

    backgroundPopup = MSprite::create("popup_xacnhan/bg_popup.png");
    backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
        visibleSize.height / 2 - backgroundPopup->getHeight() / 2));

    m_popupLayer->addChild(backgroundPopup);

	auto contenPopup = MSprite::create("popup_xacnhan/content_popup.png");
	contenPopup->setAnchorPoint(Point::ANCHOR_MIDDLE);
	contenPopup->setPosition(Vec2(backgroundPopup->getWidth() / 2, backgroundPopup->getHeight() / 2));
	backgroundPopup->addChild(contenPopup);
    
    //=====

	auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
	bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
		backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
	backgroundPopup->addChild(bg_title_popup);

	auto title = Label::createWithTTF("Vào bàn", "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
	title->setColor(Color3B::BLACK);
	title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
		bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
	bg_title_popup->addChild(title);

    auto sprite_pasword = MSprite::create("sprite_nhapmatkhau.png");

    auto password = MEditBox::create(sprite_pasword->getSize(), "sprite_nhapmatkhau.png", sprite_pasword->getHeight() / 3);
    password->setPosition(Vec2(backgroundPopup->getWidth() / 2 - sprite_pasword->getWidth() / 2,
        backgroundPopup->getHeight() / 2));
    password->setPlaceHolder("  Nhập mật khẩu");
    password->setMaxLength(12);
    password->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    password->setDelegate(this);
    backgroundPopup->addChild(password);

    auto ok = MButton::create("btn_boluot.png", "OK", 30, TAG_POPUP_LOCKTABLE_OK);
    ok->setPosition(Vec2(backgroundPopup->getWidth() / 2 + ok->getWidth()*0.2f,
        backgroundPopup->getHeight()*0.25f - ok->getHeight() / 2));
    ok->addTouchEventListener(CC_CALLBACK_2(PasswordPopup::menuPopupCallBack, this));
    backgroundPopup->addChild(ok);

    auto exit = MButton::create("btn_batdau.png", "Hủy", 30, TAG_POPUP_LOCKTABLE_EXIT);
    exit->setPosition(Vec2(backgroundPopup->getWidth() / 2 - exit->getWidth()*1.2f,
        backgroundPopup->getHeight()*0.25f - exit->getHeight() / 2));
    exit->addTouchEventListener(CC_CALLBACK_2(PasswordPopup::menuPopupCallBack, this));
    backgroundPopup->addChild(exit);

    return true;
}

void PasswordPopup::setRoomIndex(int roomIndex){
    this->roomIndex = roomIndex;
}

int PasswordPopup::getRoomIndex(){
    return this->roomIndex;
}

void PasswordPopup::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED) {
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
        case TAG_POPUP_LOCKTABLE_OK:
        {
            if (!password.empty() && password.length() > 0) {
                NetworkManager::getInstance()->getEnterRoomMessageFromServer(this->roomIndex, password);
                this->disappear();
            }
        }
            break;
        case TAG_POPUP_LOCKTABLE_EXIT:
            this->disappear();
            break;
        default:
            break;
        }
    }
}

PasswordPopup* PasswordPopup::create(int roomIndex){
    auto popup = PasswordPopup::create();
    popup->roomIndex = roomIndex;
    return popup;
}

void PasswordPopup::onExit() {
    Popup::onExit();
}

void PasswordPopup::editBoxEditingDidBegin(ui::EditBox *editBox) {
    CCLOG("%s", "edit begin!");
    password = "";
}

void PasswordPopup::editBoxEditingDidEnd(ui::EditBox *editBox) {
    password = editBox->getText();
}

void PasswordPopup::editBoxTextChanged(ui::EditBox *editBox, const std::string& text) {
    CCLOG("%s", "edit changed!");
}

void PasswordPopup::editBoxReturn(ui::EditBox *editBox) {
    CCLOG("%s", "edit return!");
}
