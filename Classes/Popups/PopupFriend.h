//
//  PopupFriend.h
//  
//
//  Created by Black3rry on 4/6/16.
//
//

///@ PopupChangePass.h
#ifndef __POPUP_FRIEND_H__
#define __POPUP_FRIEND_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UI/Popup.hpp"
#include "UI/MButton.hpp"
#include "UI/MLabel.hpp"
#include "UI/MEditBox.hpp"
#include <Utils/Common.h>
#include <protobufObject/user_info.pb.h>
#include "FriendCell.h"
#include "Utils/LoadingManager.hpp"
#include "Scenes/BaseScene.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;

class PopupFriend : public Popup, public TableViewDelegate, public TableViewDataSource {

public:
  CREATE_FUNC(PopupFriend);

  bool init();
  virtual void onExit();
  void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
  void setFriendList(vector<BINUserInfo> friendsList, int add_size);
  void resetFriendList();
  void showListFriends(vector<BINUserInfo> listFriends);
  void showFriendDetails(int index);
  void createNumberView(MLabel *label, std::string text_bot, MSprite *msprite, MLabel *label_number);
  void menuCallBack(Ref *sender, ui::Widget::TouchEventType type);
  void menuCallBackRight(Ref *sender, ui::Widget::TouchEventType type);
  static PopupFriend* createFriendCell(BINUserInfo friendCell, int pos);
  void update(float) override;
  int getAddSize();
  vector<BINUserInfo> getFriendList();
  MSprite                     *bgr_left;
  MSprite                     *bgr_right;
private:
  virtual void scrollViewDidScroll(ui::ScrollView* view){};
  virtual void scrollViewDidZoom(ui::ScrollView* view){};

  virtual void tableCellHighlight(TableView*  table, TableViewCell*  cell);
  virtual void tableCellUnhighlight(TableView*  table, TableViewCell*  cell);
  virtual Size cellSizeForTable(TableView *table) override;
  virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override;
  virtual ssize_t numberOfCellsInTableView(TableView *table) override;
  virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;
  TableView* tableView;
  float heightTable;
  int add_size;
protected:
  vector<BINUserInfo> friendList;
  BINUserInfo friendDetails;
  MSprite *btn_avatar;
  MButton *tab_friend_active;
  int index_active;
  MLabel *label_friend_name; 
  MButton * btn_send_sms;
  MButton * btn_unfriend;
  MLabel *label_xu;
  MLabel *label_ken;
  MLabel *number_play_total;
  MLabel *number_play_win;
  MLabel *number_play_lost;
  MSprite *circle_avatar;
  MSprite *icon_xu;
  MSprite *icon_ken;
  MSprite * bgr_number_play;
  MSprite * bgr_number_play_win;
  MSprite * bgr_number_play_lost;
  float text_size;
  float padding;
  MLabel *label_number_play;
  MLabel *label_number_win;
  MLabel *label_number_lost;
};

#endif /* defined (__POPUP_FRIEND_H__) */