#ifndef PopupInviteToPlay_hpp
#define PopupInviteToPlay_hpp

#include "UI/Popup.hpp"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include <Popups/ItemInviteToPlay.hpp>
#include <protobufObject/user_info.pb.h>
#include "UI/MToast.hpp"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class PopupInviteToPlay : public Popup, TableViewDelegate, TableViewDataSource {
public:
	CREATE_FUNC(PopupInviteToPlay);
    
    bool init();
    virtual void onExit();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
	
	void update(float);

	void getLookupUserToInviteFromServer();
	void setRoomIndex(int roomIndex);
	void setVipRoom(bool isVipRoom);
	void removeItemSelected(long userId);
	void addItemSelected(long userId);

	//response message
	void lookupUserToInviteResponse();
	void inviteToRoomResponse();
	//void replyToInviteResponse();
	//end

	virtual Size cellSizeForTable(TableView *table);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
private:
	int roomIndex;
	bool isVipRoom;
    MSprite* tab;
	TableView* tableView;
	MSprite* contentPopup;
	vector<BINUserInfo> lstFriend;  //danh sach nguoi choi trong zone
	vector<long> lstIdFriendChecked; //id nhung nguoi dc chon de moi choi
	bool checkAll = false;
};

#endif
