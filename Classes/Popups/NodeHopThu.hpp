//
//  NodeHopThu.hpp
//  MyCards
//
//  Created by hungle on 6/30/16.
//
//

#ifndef NodeHopThu_hpp
#define NodeHopThu_hpp

#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include <vector>
#include "Objects/Mail.h"
#include "ItemMail.hpp"

using namespace cocos2d;
using namespace cocos2d::extension;
USING_NS_CC;

class NodeHopThu : public Node,TableViewDelegate,TableViewDataSource {
public:
    CREATE_FUNC(NodeHopThu);
    
    static NodeHopThu* create(std::vector<std::string> listIndex);
    virtual bool init() ;
    virtual void onExit() ;
    
    std::vector<std::string> listIndex;
    
	void loadMail(vector<Mail> lstMail);
	void readMail(Mail mail);
	void deleteMail(vector<long> lstMailId);

	void showViewReadMail(Mail mail);
	void hiddenViewReadMail();

	void resetMail();

	void setPosDel();
	Vec2 getPosDel();

	void setIdMailDel(long idMailDel);
	long getIdMailDel();
	int getTotalMailLoaded();
	void setMailReaded(bool mailReaded);
	bool isMailReaded();
private:
    
    virtual Size cellSizeForTable(TableView *table) ;
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) ;
    virtual ssize_t numberOfCellsInTableView(TableView *table) ;
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
    float getWidth();
    float getHeight();

    TableView* tableView;
	vector<Mail> lstMail;
	float heightTable;
	Vec2 posDel;  //vi tri xoa
	long idMailDel = -1;  //id mail xoa
	bool mailReaded = false;
};

#endif /* NodeHopThu_hpp */
