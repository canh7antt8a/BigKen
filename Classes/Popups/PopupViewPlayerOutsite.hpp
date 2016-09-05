#ifndef PopupViewPlayerOutsite_hpp
#define PopupViewPlayerOutsite_hpp

#include "UI/Popup.hpp"
#include "UI/MEditbox.hpp"
#include "cocos2d.h"
#include "Objects/XocDiaPlayer.hpp"

using namespace cocos2d;
using namespace cocos2d::extension;

class PopupViewPlayerOutsite : public Popup, TableViewDelegate, TableViewDataSource {
public:
    CREATE_FUNC(PopupViewPlayerOutsite);
    bool init();
    virtual void onExit();

	void setLstUserOutsite(vector<XocDiaPlayer> lstUserOutsite);
	Node* getItemRow(XocDiaPlayer player);

	virtual Size cellSizeForTable(TableView *table);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
private:
    void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);

	vector<XocDiaPlayer> lstUserOutsite;
	MSprite* content_bg_popup;
	TableView* tableView;
};

#endif /* PopupViewPlayerOutsite */
