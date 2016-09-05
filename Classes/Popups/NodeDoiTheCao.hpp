#ifndef NodeDoiTheCao_hpp
#define NodeDoiTheCao_hpp

#include "cocos-ext.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "Utils/TLMNConfig.hpp"
#include "UI/MButton.hpp"
#include "UI/MSprite.hpp"
#include "UI/MLabel.hpp"
#include "protobufObject/exchange.pb.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class NodeDoiTheCao : public Node,public TableViewDelegate,public TableViewDataSource {
public:
    CREATE_FUNC(NodeDoiTheCao);
    
    virtual bool init();
    virtual void onExit();
    
	float getWidth();
	float getHeight();

	void setAssets(vector<BINAsset> assets);
	void showTheCao();

	void addTab();
	void menuPopupCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type);
private:

	virtual Size cellSizeForTable(TableView *table) override;
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override;
	virtual ssize_t numberOfCellsInTableView(TableView *table) override;
	virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;

	vector<BINAsset> lstAsset;
	vector<BINAsset> lstAssetConfig;

	TableView* tableView;
	float heightTable;
	MSprite *backgroundContent;

	MButton *btnViettel;
	MButton *btnVinaphone;
	MButton *btnMobiphone;

	string type_selected;
};

#endif /* NodeDoiTheCao_hpp */
