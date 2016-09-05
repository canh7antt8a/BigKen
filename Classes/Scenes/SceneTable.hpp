//
//  SceneTable.hpp
//  MyCards
//
//  Created by hungle on 4/13/16.
//
//


#ifndef __SCENE_TABLE_HPP__
#define __SCENE_TABLE_HPP__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UI/MSprite.hpp"
#include "BaseScene.hpp"
#include "ui/CocosGUI.h"
#include "UI/MLabel.hpp"
#include "UI/M9Path.hpp"
#include "protobufObject/filter_room.pb.h"
#include "protobufObject/enter_room.pb.h"
#include "protobufObject/create_room.pb.h"
#include "protobufObject/instant_message.pb.h"
#include "Popups/PopupCreateRoom.hpp"
#include "Popups/PasswordPopup.hpp"
#include "Objects/OnEvenListener.hpp"
#include "Popups/PopupHotLine.hpp"

using namespace cocos2d;
using namespace cocos2d::extension;
USING_NS_CC;

class SceneTable : public BaseScene, TableViewDelegate, TableViewDataSource, OnEvenListener<BINRoomPlay>{
public :
    static cocos2d::Scene* createScene(bool enableDisplayRoomList);
    
    void menuCallBack(Ref *sender,ui::Widget::TouchEventType type);
    void phongCallBack(Ref *sender,ui::Widget::TouchEventType type);
    void tableCallBack(Ref *sender,ui::Widget::TouchEventType type);
    
    virtual bool init();
    virtual void onExit();

    void update(float);
    
    void reloadRoom(float dt);

    CREATE_FUNC(SceneTable);

public:
    virtual void tableItemCallBack(cocos2d::Ref *sender, Widget::TouchEventType type);
    
    virtual void scrollViewDidScroll(ui::ScrollView* view){};
    virtual void scrollViewDidZoom(ui::ScrollView* view){};
    virtual Size cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual void tableCellHighlight (TableView * table,TableViewCell * cell);
    virtual void tableCellUnhighlight (TableView * table, TableViewCell * cell);
    
	void onEvent(int enventType, BINRoomPlay sender);

    void showPopupPassWord(int roomIndex);

    //response handle
    void instantMessageResponseHandle();

	void loadEmail(vector<Mail> lstEmail);
	void readMail(Mail mail);
	void deleteMail(vector<long> lstMailId);
	void showNumberNewMail();

	void replyToInviteResponse();

	void viewUserInfo(BINViewUserInfoResponse *viewUserInfo);

	void loadMoneyLogHistory(vector<BINMoneyLog> lstMoneyLogs);

	void updateMoneyResponseHandler();
    void exitZoneResponseHandler();
    
	void inviteToRoomResponseHandler();

	void getCapchaMessageResponse();
public:
	void initTitleTable(float posX, float posY);
    void initMenu();
    void initTable();
    void setEnableDisplayRoomList(bool enable);
    bool getEnableDisplayRoomList();

protected:
    
    MSprite * tab;
    Sprite* bkg_item;
    
    ui::ListView* lvRight;
    ui::ListView* lvLeft;
    
    bool scroll_bottom;
    std::vector<BINRoomPlay> listRoomPlay;
    bool canCreateRoom;
    void loadTabButton(float x,bool zone);
private:
    MSprite* scrollBkg;
	MSprite* bg_lst_table;
    TableView *tableView;
	float hightTable;
    bool enableDisplayRoomList;
    bool is_vip_room = false;
	MLabel* label_xu;
	MLabel* label_ken;
	int totalNewMail = 0;
	int orderByField = -1;
	MButton* btn_sort_muccuoc;
	MButton* btn_sort_songuoichoi;
	MButton* btn_sort_toithieu;
	int roomIndexInvite = 0;
	MSprite* sprite_new_mail;
	MLabel* label_number_new_mail;
};
#endif // __SCENE_TABLE_HPP__
