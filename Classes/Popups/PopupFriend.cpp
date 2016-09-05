//
//  PopupFriend.cpp
//  
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupFriend.cpp
#include "PopupFriend.h"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"

#define PADDING_ITEM 2
using namespace cocos2d;

bool PopupFriend::init() {
  if (!Popup::init())
    return false;

  backgroundPopup = MSprite::create(BGR_FRIEND);
  backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
    visibleSize.height / 2 - backgroundPopup->getHeight() / 2));

  backgroundContentSize = background->getContentSize();

  auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
  bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
	  backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
  backgroundPopup->addChild(bg_title_popup);

  auto title = Label::createWithTTF(FRIEND_TEXT, "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
  title->setColor(Color3B::BLACK);
  title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
	  bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
  bg_title_popup->addChild(title);

  m_popupLayer->addChild(backgroundPopup);

  auto tab_active = MSprite::create(TAB_FRIEND_ACTIVE);
  bgr_left = MSprite::create(BGR_FRIEND_LEFT);
  bgr_right = MSprite::create(BGR_FRIEND_RIGHT);
  float distance_width = (backgroundPopup->getWidth() - (bgr_left->getWidth() + bgr_right->getWidth() + 5)) / 2;
  bgr_left->setPosition(Vec2(distance_width, backgroundPopup->getHeight() / 2 - bgr_left->getHeight()/2));
  bgr_right->setPosition(Vec2(bgr_left->getPosition().x + bgr_left->getWidth() + 5, bgr_left->getPosition().y));
  backgroundPopup->addChild(bgr_left);
  backgroundPopup->addChild(bgr_right);

  //auto btn_back = MButton::createExtendsIcon(IMAGE_CLOSE, SETTING_TEXT, 
  // 1.0f, TAG_POPUP_BTN_BACK, backgroundPopup->getWidth() * 1 / 2);
  //btn_back->setTitleFontSize(visibleSize.height / 15);

  //button close
  auto btn_back = MButton::create(IMAGE_CLOSE);
  btn_back->setZoomScale(0.02f);
  btn_back->setPosition(Vec2(backgroundPopup->getWidth() - btn_back->getWidth() / 2, 
      backgroundPopup->getHeight() - btn_back->getHeight() / 2));
  btn_back->setTag(TAG_POPUP_BTN_BACK);
  backgroundPopup->addChild(btn_back);
  heightTable = bgr_left->getHeight() / 6;
  tableView = TableView::create(this, Size(tab_active->getWidth(), bgr_left->getHeight()//- heightTable
    - PADDING_ITEM));

  tableView->setDirection(TableView::Direction::VERTICAL);
  tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
  tableView->setDelegate(this);
  tableView->setBounceable(true);
  tableView->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
  tableView->setEventDispatcher(_eventDispatcher);
  tableView->setPosition(Vec2(0, 0));

  bgr_left->addChild(tableView);

  circle_avatar = MSprite::create(CIRCLE_AVATAR_RIGHT);
  btn_avatar = MSprite::create("avatar0.png"
    , circle_avatar->getSize());
  padding = circle_avatar->getHeight() / 6;

  circle_avatar->setPosition(Vec2(padding, bgr_right->getHeight() - circle_avatar->getHeight() - padding));

  circle_avatar->addChild(btn_avatar);
  bgr_right->addChild(circle_avatar);
  icon_xu = MSprite::create(ICON_FRIEND_XU);
  icon_ken = MSprite::create(ICON_FRIEND_KEN);

  text_size = icon_ken->getHeight() * 0.8f;
  // text_size = 26;
  /*auto label = MLabel::create(FRIEND_TEXT, text_size * 1.75f);
  label->setColor(Color3B(87, 143, 178));
  label->setPosition(backgroundPopup->getWidth() * 0.5f - label->getWidth() / 2
    , backgroundPopup->getHeight() / 2 + bgr_left->getHeight() / 2 - label->getHeight() / 2 + bgr_left->getPosition().y/2);
  backgroundPopup->addChild(label);*/

  label_xu = MLabel::create("", text_size);
  label_ken = MLabel::create("", text_size);
  bgr_right->addChild(icon_ken);


  btn_send_sms = MButton::create(BTN_SEND_SMS, "", text_size, TAG_POPUP_SEND_SMS);
  btn_unfriend = MButton::create(BTN_UNFRIEND, "", text_size, TAG_POPUP_UNFRIEND);
  btn_send_sms->addTouchEventListener(CC_CALLBACK_2(PopupFriend::menuCallBackRight, this));
  btn_unfriend->addTouchEventListener(CC_CALLBACK_2(PopupFriend::menuCallBackRight, this));


  btn_send_sms->setPosition(Vec2(circle_avatar->getPosition().x + circle_avatar->getWidth() / 2
    - btn_send_sms->getWidth() / 2, btn_send_sms->getHeight() / 4));
  btn_unfriend->setPosition(Vec2(bgr_right->getWidth() - btn_unfriend->getWidth()
    - btn_send_sms->getPosition().x, btn_send_sms->getPosition().y));
  btn_send_sms->addTouchEventListener(CC_CALLBACK_2(PopupFriend::menuCallBackRight, this));
  bgr_number_play_lost = MSprite::create(BGR_NUMBER_PLAY);
  bgr_number_play = MSprite::create(BGR_NUMBER_PLAY);
  bgr_number_play->setPosition(Vec2(bgr_right->getWidth() - bgr_number_play->getWidth()
    , bgr_right->getHeight() - bgr_number_play->getHeight() - padding));
  bgr_number_play_win = MSprite::create(BGR_NUMBER_PLAY);
  bgr_number_play_win->setPosition(Vec2(bgr_number_play->getPosition().x
    , padding + btn_unfriend->getHeight() + btn_unfriend->getPosition().y));
  bgr_number_play_lost->setPosition(Vec2(bgr_number_play->getPosition().x
    , bgr_number_play_win->getPosition().y / 2 + bgr_number_play->getPosition().y / 2));
  label_friend_name = MLabel::create("", text_size);
  label_friend_name->setColor(Color3B(87, 143, 178));
  label_friend_name->setAnchorPoint(Vec2(0.5, 0));
  label_friend_name->setPosition(Vec2(circle_avatar->getPosition().x + circle_avatar->getWidth() / 2
    , bgr_number_play_lost->getPosition().y));
  bgr_right->addChild(label_friend_name);

  icon_xu->setPosition(Vec2(btn_send_sms->getPosition().x, (btn_send_sms->getPosition().y + btn_send_sms->getHeight()) / 2 + label_friend_name->getPosition().y / 2));
  label_xu->setPosition(Vec2(icon_xu->getRightPosition() + icon_xu->getHeight() / 2,
    icon_xu->getPosition().y + icon_xu->getHeight() / 2 - label_ken->getHeight() / 2));
  // auto icon_ken = MSprite::create(ICON_FRIEND_KEN);
  icon_ken->setPosition(Vec2(icon_xu->getPosition().x,
    icon_xu->getPosition().y / 2 + (btn_send_sms->getPosition().y + btn_send_sms->getHeight()) / 2));
  bgr_right->addChild(icon_xu);
  bgr_right->addChild(label_xu);
  bgr_right->addChild(label_ken);


  number_play_total = MLabel::create("", text_size);
  number_play_lost = MLabel::create("", text_size);
  number_play_win = MLabel::create("", text_size);

  bgr_number_play->addChild(number_play_total);
  bgr_number_play_win->addChild(number_play_win);
  bgr_number_play_lost->addChild(number_play_lost);

  label_number_play = MLabel::create(NUMBER_PLAY_TEXT, text_size);
  label_number_win = MLabel::create(NUMBER_PLAY_WIN_TEXT, text_size);
  label_number_lost = MLabel::create(NUMBER_PLAY_LOST_TEXT, text_size);
  label_number_play->setColor(Color3B(87, 143, 178));
  label_number_win->setColor(Color3B(87, 143, 178));
  label_number_lost->setColor(Color3B(87, 143, 178));
  label_number_play->setPosition(Vec2(bgr_number_play->getWidth() / 2
    - label_number_play->getWidth() / 2, bgr_number_play->getHeight() * 0.5f));
  label_number_win->setPosition(Vec2(bgr_number_play_win->getWidth() / 2
    - label_number_win->getWidth() / 2, bgr_number_play_win->getHeight() * 0.5f));
  label_number_lost->setPosition(Vec2(bgr_number_play_lost->getWidth() / 2
    - label_number_lost->getWidth() / 2, bgr_number_play_lost->getHeight() * 0.5f));

  bgr_number_play->addChild(label_number_play);
  bgr_number_play_win->addChild(label_number_win);
  bgr_number_play_lost->addChild(label_number_lost);

  bgr_right->addChild(btn_send_sms);
  bgr_right->addChild(btn_unfriend);

  bgr_right->addChild(bgr_number_play);
  bgr_right->addChild(bgr_number_play_win);
  bgr_right->addChild(bgr_number_play_lost);
  index_active = 0;

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

void PopupFriend::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
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
            }

    default:
        break;

    }
  }

}

void PopupFriend::showListFriends(vector<BINUserInfo> friendList){
  if (!friendList.empty()){
    this->friendList.insert(this->friendList.end(), friendList.begin(), friendList.end());

    tableView->reloadData();

    if ((this->friendList.size() - this->add_size) > NUM_LOAD_MORE_FRIEND){ //set lai selection
      int a = (this->friendList.size() - this->add_size)% NUM_LOAD_MORE_FRIEND;
      a = a == 0 ? NUM_LOAD_MORE_FRIEND : this->friendList.size();
  
      tableView->getContainer()->setPosition(Vec2(0, - a * heightTable));
    }
    showFriendDetails(0);
  }

}

void PopupFriend::showFriendDetails(int index){
    BINUserInfo friendDetails = friendList[index];
    int avatar_id = friendDetails.avatarid();
    btn_avatar->setTexture(StringUtils::format("avatar%d.png", avatar_id));

    btn_send_sms->setPosition(Vec2(circle_avatar->getPosition().x + circle_avatar->getWidth() / 2 
      - btn_send_sms->getWidth() / 2, btn_send_sms->getHeight()/4));
    if (index < this->add_size){
      btn_unfriend->setTitleText(REMOVE_REQUEST_TEXT);
     btn_send_sms->setTitleText(ACCEPT_FRIEND_TEXT);
    }
    else {
      btn_unfriend->setTitleText(UNFRIEND_TEXT);
      btn_send_sms->setTitleText(SEND_SMS_TEXT);
    }
    btn_unfriend->setPosition(Vec2(bgr_right->getWidth() - btn_unfriend->getWidth()
        - btn_send_sms->getPosition().x, btn_send_sms->getPosition().y));
    btn_send_sms->addTouchEventListener(CC_CALLBACK_2(PopupFriend::menuCallBackRight, this));

    CCLOG("showFriendDetails call");

    createNumberView(label_number_play, Common::getInstance()->convertIntToString(friendDetails.totalmatch())
        , bgr_number_play, number_play_total);
    createNumberView(label_number_win, Common::getInstance()->convertIntToString(friendDetails.totalwin())
      , bgr_number_play_win, number_play_win);
    createNumberView(label_number_lost, Common::getInstance()->convertIntToString(friendDetails.totalmatch()
      - friendDetails.totalwin()), bgr_number_play_lost, number_play_lost);

    label_friend_name->setString(friendDetails.displayname());

    label_xu->setString(Common::getInstance()->convertIntToString(friendDetails.cash()) + " XU");
    label_ken->setString(Common::getInstance()->convertIntToString(friendDetails.gold()) + " KEN");
    label_xu->setPosition(Vec2(icon_xu->getRightPosition() + icon_xu->getHeight() / 2, 
        icon_xu->getPosition().y + icon_xu->getHeight() / 2 - label_ken->getHeight()/2));
    label_ken->setPosition(Vec2(label_xu->getPosition().x,
      icon_ken->getPosition().y + icon_ken->getHeight() / 2 - label_ken->getHeight() / 2));

}

void PopupFriend::menuCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED){
      MButton *button = (MButton*)sender;
      int tag = button->getTag();
      CCLOG("TAG_POPUP_FRIEND_LIST call");
      button->loadTextureNormal(TAB_FRIEND_ACTIVE);
      if (button != tab_friend_active)
          {
              tab_friend_active->loadTextureNormal(TAB_FRIEND_UNACTIVE);
              tab_friend_active = button;
              int i = tag - TAG_POPUP_FRIEND_LIST;
              BINUserInfo friendDetails = friendList[i];
              btn_avatar->setTexture(StringUtils::format("avatar%d.png", friendDetails.avatarid()));
              label_friend_name->setString(friendDetails.displayname());
              label_xu->setString(Common::getInstance()->convertIntToString(friendDetails.cash()) + " XU");
              label_ken->setString(Common::getInstance()->convertIntToString(friendDetails.gold()) + " KEN");
              number_play_total->setString(Common::getInstance()->convertIntToString(friendDetails.totalmatch()));
              number_play_lost->setString(Common::getInstance()->convertIntToString(friendDetails.totalwin()));
              number_play_win->setString(Common::getInstance()->convertIntToString(friendDetails.totalmatch() - friendDetails.totalwin()));
          }
  }
}
void PopupFriend::menuCallBackRight(cocos2d::Ref *sender, Widget::TouchEventType type){
  if (type == Widget::TouchEventType::ENDED){
    MButton *button = (MButton*)sender;
    int tag = button->getTag();
    switch (tag) {
    case TAG_POPUP_SEND_SMS:
        {
            CCLOG("TAG_POPUP_SEND_SMS %d", index_active);
            if (index_active < this->add_size) {
              NetworkManager::getInstance()->getApproveAddFriendFromServer(friendList[index_active].userid(), true);
              break;
            }
            else {
              // gui tin nhan
              //NetworkManager::getInstance()->getRemoveFriendFromServer(friendList[index_active].userid());
              break;
            }
        }
        case TAG_POPUP_UNFRIEND:
            {
                CCLOG("TAG_POPUP_UNFRIEND %d", index_active);
                if (index_active < this->add_size) {
                    // xoa yeu cau 
                    NetworkManager::getInstance()->getApproveAddFriendFromServer(friendList[index_active].userid(), false);
                    break;
                }
                else {
                    NetworkManager::getInstance()->getRemoveFriendFromServer(friendList[index_active].userid());
                    break;
                }
            }
        default:
          break;
    }
  }
}
void PopupFriend::resetFriendList() {
  this->friendList.clear();
}

void PopupFriend::setFriendList(vector<BINUserInfo> friendList, int add_size) {
    //this->friendList = friendList;
    //if (bgr_left->getParent() == nullptr && bgr_left->getParent() == nullptr){
    this->add_size = add_size;
    showListFriends(friendList);
    //}
   // bgr_right->removeAllChildren();
    // bgr_left->removeAllChildren();
   // showListFriends(PopupFriend::getFriendList());
}
int PopupFriend::getAddSize() {
  return this->add_size;
}

void PopupFriend::createNumberView(MLabel *label_top, std::string text_bot, MSprite *msprite, MLabel *label_number) {

  label_number->setString(text_bot);
  label_number->setPosition(Vec2(msprite->getWidth() / 2 - label_number->getWidth() / 2,
  label_top->getPosition().y / 2 - label_number->getHeight() / 2));
}
//update
void PopupFriend::update(float delta) {
    BINRemoveFriendResponse* remove_friend_response =
      (BINRemoveFriendResponse *)Common::getInstance()->checkEvent(NetworkManager::REMOVE_FRIEND);
    if (remove_friend_response != 0) {
        CCLOG("BINRemoveFriendResponse: %s", remove_friend_response->DebugString().c_str());
        if (remove_friend_response->responsecode()) {
          CCLOG("remove_friend_response: %s", remove_friend_response->DebugString().c_str());
              friendList.erase(friendList.begin() + index_active);
              MToast* mToast = MToast::create();
              mToast->setPosition(Vec2(backgroundPopup->getWidth() / 2, backgroundPopup->getHeight()*0.5f));
              mToast->show(UNFRIEND_SUCCESS_TEXT, 3);
              this->addChild(mToast, 4);
              showFriendDetails(index_active == 0 ? index_active : index_active -1);
              tableView->reloadData();
        }
    }
      BINApproveAddFriendResponse* approve_friend_response =
          (BINApproveAddFriendResponse *)Common::getInstance()->checkEvent(NetworkManager::APPROVE_ADD_FRIEND);
      if (approve_friend_response != 0) {
        CCLOG("BINApproveAddFriendResponse: %s", approve_friend_response->DebugString().c_str());
        if (approve_friend_response->responsecode()) {
          CCLOG("approve_friend_response: %s", approve_friend_response->DebugString().c_str());
                friendList.clear();
                this->resetFriendList();
                MToast* mToast = MToast::create();
                mToast->setPosition(Vec2(backgroundPopup->getWidth() / 2, backgroundPopup->getHeight()*0.5f));
                mToast->show(SUCCESS_TEXT, 3);
                this->addChild(mToast, 4);
                NetworkManager::getInstance()->getFilterAddFriendFromServer(-1,-1);
                NetworkManager::getInstance()->getFilterFriendFromServer(0, NUM_LOAD_MORE_FRIEND);

        }
      }
}

//========================= TableView

void PopupFriend::tableCellHighlight(TableView*  table, TableViewCell*  cell){
  MSprite* pSprite = (MSprite*) cell->getChildByTag(789);
  if (pSprite){
    pSprite->setTexture(TAB_FRIEND_ACTIVE);
  }
  MSprite* pSprite_add = (MSprite*)cell->getChildByTag(777);
  if (pSprite_add){
    pSprite_add->setTexture(TAB_FRIEND_ACTIVE);
  }
}

void PopupFriend::tableCellUnhighlight(TableView*  table, TableViewCell*  cell){
  MSprite*  pSprite = (MSprite*) cell->getChildByTag(789);
  if (pSprite){
    pSprite->setTexture(TAB_FRIEND_UNACTIVE);
  }
  MSprite*  pSprite_add = (MSprite*)cell->getChildByTag(777);
  if (pSprite_add){
    pSprite_add->setTexture(TAB_ADD_FRIEND);
  }
}

Size PopupFriend::cellSizeForTable(TableView *table) {
  return Size(this->getContentSize().width, heightTable);
}

ssize_t PopupFriend::numberOfCellsInTableView(TableView *table) {
  CCLOG(" numberOfCellsInTableView %d ", friendList.size());
  return this->friendList.size();
}

void PopupFriend::tableCellTouched(TableView *table, TableViewCell *cell) {
  CCLOG(" CEll %d ", cell->getIdx());
  showFriendDetails(cell->getIdx()); 
  index_active = cell->getIdx();
}

TableViewCell* PopupFriend::tableCellAtIndex(TableView *table, ssize_t idx) {
  CCLOG("tableCellAtIndex");
  TableViewCell *cell = table->dequeueCell();
  if (!cell){
    cell = new TableViewCell();
    cell->autorelease();
  }

  cell->removeAllChildrenWithCleanup(true);

  auto background = MSprite::create(idx < add_size? TAB_ADD_FRIEND :  TAB_FRIEND_UNACTIVE);
  background->setTag(idx < add_size ? 777 : 789);
  cell->addChild(background);

  auto friend_cell = FriendCell::createFriendCell(this->friendList[idx], idx, this->add_size);
  friend_cell->setAnchorPoint(Vec2(0, 0));
  friend_cell->setPosition(Vec2(0, 0));
  cell->addChild(friend_cell);

  if (idx + 1 == this->friendList.size() && this->friendList.size() % NUM_LOAD_MORE_FRIEND == 0){
    LoadingManager::getInstance()->showLoading();
    NetworkManager::getInstance()->getFilterFriendFromServer(idx + 1, NUM_LOAD_MORE_FRIEND);
  }

  return cell;
}

vector<BINUserInfo> PopupFriend::getFriendList() {
    return this->friendList;
}

void PopupFriend::onExit() {
  Popup::onExit();
}
