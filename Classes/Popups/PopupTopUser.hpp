#ifndef PopupTopUser_hpp
#define PopupTopUser_hpp

#include "UI/Popup.hpp"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
//#include <protobufObject/user_info.pb.h>
#include <protobufObject/user_info.pb.h>

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class PopupTopUser : public Popup, TableViewDelegate, TableViewDataSource {
public:
	CREATE_FUNC(PopupTopUser);
    
    bool init();
    virtual void onExit();
    void addTab();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void tabCallBack(Ref *sender, ui::Widget::TouchEventType type);
	
	Node* getItemRow(BINUserInfo userInfo, int idx);
	void update(float);
	void getFilterTopUser();

	void requestTopUser();

	virtual Size cellSizeForTable(TableView *table);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
private:
    MSprite* tab;
	TableView* tableView;
	vector<BINUserInfo> lstTopUser;
	int topUserType = 0;
	MSprite* contentPopupLeft;
	MSprite* contentPopupRight;
	float padding_left;
	float heightTab;
};

#endif
