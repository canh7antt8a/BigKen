#ifndef PopupGiftCode_hpp
#define PopupGiftCode_hpp

#include "UI/Popup.hpp"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "UI/MEditBox.hpp"
#include "Scenes/ShowGame.h"
//#include "protobufObject/gift.pb.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class ShowGame;

class PopupGiftCode : public Popup, TableViewDelegate, TableViewDataSource {
public:
	CREATE_FUNC(PopupGiftCode);

    bool init();
    virtual void onExit();
    void addTab();
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);
    void tabCallBack(Ref *sender, ui::Widget::TouchEventType type);
	
	Node* getNodeInputGiftCode();
	Node* getNodeReceiveGiftCode();

	void update(float);
	void getRedeemGiftCode();
	void getRedeemGiftCodeHistory();
	//void updateMoneyResponseHandler();

	void requestRedeemGiftCode();
	void requestRedeemGiftCodeHistory();

	void setContext(ShowGame* showGame);

	Node* getItemRow(BINGiftCode binGiftCode);

	virtual Size cellSizeForTable(TableView *table);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
private:
	vector<BINGiftCode> lstGiftCodeHistory;
	ShowGame* showGame;
    MSprite* tab;
	float heightTab;
	MSprite* contentPopupLeft;
	MEditBox* edit_giftcode;
	Node* nodeInputGiftCode;
	Node* nodeReceiveGiftCode;
	TableView* tableView;
};

#endif
