//
//  FriendCell.cpp
//  MyCards
//
//  Created by hungle on 5/25/16.
//
//

#include "FriendCell.h"
#include "UI/MLabel.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"
#include "Utils/Image.h"

#define PADDING_ITEM 25

FriendCell::FriendCell(){}

FriendCell::~FriendCell(){}

FriendCell* FriendCell::createFriendCell(BINUserInfo friendCell, int pos, int add_size){
    FriendCell *cell = new FriendCell();
    if (cell && cell->init()){
        cell->autorelease();
    }else{
        CC_SAFE_DELETE(cell);
    }
    CCLOG("add_size %d %d", pos, add_size);
    auto background = MSprite::create(pos < add_size ? TAB_ADD_FRIEND : TAB_FRIEND_ACTIVE);

	//if (pos %2 == 0){
		cell->setContentSize(background->getContentSize());
	   // cell->addChild(background);
	//}
    background->setTag(TAG_POPUP_FRIEND_LIST);

	float sizeText = background->getHeight() / 3;
    CCLOG("createFriendCell FriendCell%d", TAG_POPUP_FRIEND_LIST + pos);

      auto circle_avatar = MSprite::create(CIRCLE_AVATAR_LEFT);
      float padding = cell->getHeight() / 2 - circle_avatar->getHeight() / 2;
      circle_avatar->setPosition(Vec2(padding, padding));
//      // avartar
      int avatar_id = friendCell.avatarid();
      auto btn_avatar = MButton::createWidthSize(StringUtils::format("avatar%d.png", avatar_id)
          , circle_avatar->getSize(), TAG_SHOW_BTN_AVATAR);
      btn_avatar->setPosition(Vec2(btn_avatar->getHeight() / 2, btn_avatar->getWidth()/2));
      circle_avatar->addChild(btn_avatar);
      cell->addChild(circle_avatar);
      if (pos < add_size){
        MSprite* icon_add = MSprite::create(ICON_ADD_FRIEND);
        icon_add->setPosition(Vec2(circle_avatar->getPosition().x + circle_avatar->getWidth() - icon_add->getWidth() * 0.75f,
          circle_avatar->getPosition().y + circle_avatar->getHeight() - icon_add->getHeight() * 0.75f));
        cell->addChild(icon_add);
      }

//        // ten 
      auto text_size = cell->getHeight() / 3;
      auto label_name = MLabel::create(friendCell.displayname(), text_size);
      label_name->setPosition(Vec2(circle_avatar->getWidth() + circle_avatar->getPosition().x 
          + padding, cell->getHeight() / 2 - label_name->getHeight() / 2));
      cell->addChild(label_name);
      // tab_friend->addTouchEventListener(CC_CALLBACK_2(PopupFriend::menuCallBack, this));
      //if (i == 0){
      //  tab_friend_active = tab_friend;
      //}



    return cell;
}

float FriendCell::getWidth(){
    return this->getContentSize().width;
}

float FriendCell::getHeight(){
    return this->getContentSize().height;
}

bool FriendCell::init() {
    if (!Node::init())
        return false;

    return true;
}

void FriendCell::onExit() {
    Node::onExit();
}
