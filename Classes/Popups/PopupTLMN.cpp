//
//  PopupTLMN.cpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupSetting.cpp
#include "PopupTLMN.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "Utils/Utility.h"
#include "protobufObject/exit_room.pb.h"
#include "Utils/Common.h"

bool PopupTLMN::init() {
    if (!Popup::init())
        return false;
    this->setAnchorPoint(Point::ZERO);

    auto button = MSprite::create(IMAGE_MENU);
    
    backgroundPopup = MSprite::create(IMAGE_POPUP_TLMN);
// vi tri xuat hien
    backgroundPopup->setPosition(Vec2(20,visibleSize.height - button->getHeight()
                                        - backgroundPopup->getHeight()- 10));

    m_popupLayer->setPosition(Vec2(-backgroundPopup->getWidth() - 20,0));

    m_popupLayer->addChild(backgroundPopup);
    
    //  thoat
    check_exit_room = false;
    auto btn_exit = MButton::createExtendsWithSizeTextLeft(IMAGE_SPOT, 
      cocos2d::Size(backgroundPopup->getWidth(), backgroundPopup->getHeight() / 5), 
        "Roi ban", 30, TAG_TLMN_BTN_EXIT);
    btn_exit->setPosition(Vec2(backgroundPopup->getPosition().x + 5, backgroundPopup->getPosition().y));
    backgroundPopup->setOpacity(200);
    btn_exit->addTouchEventListener(CC_CALLBACK_2(PopupTLMN::menuPopupCallBack, this));

    m_popupLayer->addChild(btn_exit);
    
    return true;
}
void PopupTLMN::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED) {
    MButton *button = (MButton*)sender;
    int tag = button->getTag();
    switch (tag) {
    case TAG_TLMN_BTN_EXIT:
      //CCLOG("%s", "TAG_TLMN_BTN_EXIT DIEP" + PopupTLMN::getRoomIndex());
      //CCLOG("%d", PopupTLMN::getRoomIndex());
      {
        if (!check_exit_room) {
            NetworkManager::getInstance()->getExitRoomMessageFromServer(PopupTLMN::getRoomIndex());
        }
        else {
            NetworkManager::getInstance()->getCancelExitRoomMessageFromServer(PopupTLMN::getRoomIndex());
        }
        check_exit_room = !check_exit_room;
        //this->disappear();
      }
      break;
    default:
      break;
    }
  }
}

PopupTLMN* PopupTLMN::createPopup(int roomIndex) {
    auto popup = PopupTLMN::create();
    popup->setRoomIndex(roomIndex);
    return popup;
}

void PopupTLMN::onExit() {
    Popup::onExit();
}
void PopupTLMN::setRoomIndex(int roomIndex) {
    this->roomIndex = roomIndex;
}
int PopupTLMN::getRoomIndex() {
    return this->roomIndex;
}
