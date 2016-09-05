//
//  NodeLichSuDoiThuong.hpp
//  MyCards
//
//  Created by hungle on 6/30/16.
//
//

#ifndef NodeLichSuDoiThuong_hpp
#define NodeLichSuDoiThuong_hpp

#include "cocos-ext.h"
#include "cocos2d.h"
#include <vector>
#include "Utils/TLMNConfig.hpp"
#include "protobufObject/lookup_money_history.pb.h"
#include "ItemMoneyLog.hpp"
#include "UI/MButton.hpp"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class NodeLichSuDoiThuong : public Node,public TableViewDelegate,public TableViewDataSource {
public:
    CREATE_FUNC(NodeLichSuDoiThuong);
    
    static NodeLichSuDoiThuong* create(std::vector<std::string> listIndex);
    virtual bool init();
    virtual void onExit();
    
    std::vector<std::string> listIndex;
	void loadMoneyLogsHistory(vector<BINMoneyLog> lstMoneyLogs);
    
	float getWidth();
	float getHeight();

	void resetMoneyLog();
private:
	virtual void scrollViewDidScroll(ui::ScrollView* view){};
	virtual void scrollViewDidZoom(ui::ScrollView* view){};

	virtual Size cellSizeForTable(TableView *table) override;
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override;
	virtual ssize_t numberOfCellsInTableView(TableView *table) override;
	virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;

	TableView* tableView;
	vector<BINMoneyLog> lstMoneyLogs;
	float heightTable;
};

#endif /* NodeLichSuDoiThuong_hpp */
