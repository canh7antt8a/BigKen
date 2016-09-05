#include "NodeLichSuDoiThuong.hpp"
#include "UI/MSprite.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/LoadingManager.hpp"

#define PADDING_ITEM 20

using namespace std;

bool NodeLichSuDoiThuong::init() {
    if (!Node::init())
        return false;

	auto backgroundPopup = MSprite::create("user_info/bg_popup/content_popup_right.png");

	this->setContentSize(backgroundPopup->getContentSize());

	this->addChild(backgroundPopup);

	auto backgroundContent = MSprite::create(LS_DOITHUONG_ODD);

	heightTable = backgroundContent->getHeight();

	float sizeTitleText = heightTable / 2;

	auto labelSender = MLabel::create(LS_DOITHUONG_TXT_SENDER, sizeTitleText, cocos2d::Color3B::GREEN);
	labelSender->setPosition(Vec2(0, backgroundPopup->getHeight() - heightTable));
	labelSender->setContentSize(Size(1 * backgroundContent->getWidth() / 6, heightTable));
	labelSender->setWidth(1 * backgroundContent->getWidth() / 6);
	labelSender->setHeight(backgroundContent->getHeight());
	labelSender->setHorizontalAlignment(TextHAlignment::CENTER);
	labelSender->setVerticalAlignment(TextVAlignment::CENTER);
	this->addChild(labelSender);

	auto labelContent = MLabel::create(LS_DOITHUONG_TXT_CONTENT, sizeTitleText, cocos2d::Color3B::GREEN);
	labelContent->setPosition(Vec2(labelSender->getPosition().x + labelSender->getWidth(), 
		labelSender->getPosition().y));
	labelContent->setContentSize(Size(3.5 * backgroundContent->getWidth() / 6, backgroundContent->getHeight()));
	labelContent->setWidth(3.5 * backgroundContent->getWidth() / 6);
	labelContent->setHeight(backgroundContent->getHeight());
	labelContent->setHorizontalAlignment(TextHAlignment::CENTER);
	labelContent->setVerticalAlignment(TextVAlignment::CENTER);
	this->addChild(labelContent);

	auto labelTime = MLabel::create(LS_DOITHUONG_TXT_TIME, sizeTitleText, cocos2d::Color3B::GREEN);
	labelTime->setPosition(Vec2(labelContent->getPosition().x + labelContent->getWidth(), 
		labelSender->getPosition().y));
	labelTime->setContentSize(Size(1.5 * backgroundContent->getWidth() / 6, backgroundContent->getHeight()));
	labelTime->setWidth(1.5 * backgroundContent->getWidth() / 6);
	labelTime->setHeight(backgroundContent->getHeight());
	labelTime->setHorizontalAlignment(TextHAlignment::CENTER);
	labelTime->setVerticalAlignment(TextVAlignment::CENTER);
	this->addChild(labelTime);

	tableView = TableView::create(this, Size(backgroundContent->getWidth(), backgroundPopup->getHeight() - heightTable
		- PADDING_ITEM));
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDelegate(this);
	tableView->setBounceable(true);
	tableView->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	tableView->setEventDispatcher(_eventDispatcher);
	tableView->setPosition(Vec2((backgroundPopup->getWidth() - backgroundContent->getWidth()) / 2 ,
		PADDING_ITEM));
	
	this->addChild(tableView);

    return true;
}

void NodeLichSuDoiThuong::resetMoneyLog(){
	this->lstMoneyLogs.clear();
}

float NodeLichSuDoiThuong::getWidth(){
	return this->getContentSize().width;
}

float NodeLichSuDoiThuong::getHeight(){
	return this->getContentSize().height;
}

void NodeLichSuDoiThuong::loadMoneyLogsHistory(vector<BINMoneyLog> lstMoneyLogs){
	if (!lstMoneyLogs.empty()){
		this->lstMoneyLogs.insert(this->lstMoneyLogs.end(), lstMoneyLogs.begin(), lstMoneyLogs.end());
		
		tableView->reloadData();

		if (this->lstMoneyLogs.size() > NUM_LOAD_MORE_ITEM){ //set lai selection
			int mod = (this->lstMoneyLogs.size() % NUM_LOAD_MORE_ITEM);
			int numPos = mod == 0 ? NUM_LOAD_MORE_ITEM : mod;
			tableView->getContainer()->setPosition(Vec2(0, -numPos * heightTable));
		}
	}
}

//========================= TableView

Size NodeLichSuDoiThuong::cellSizeForTable(TableView *table) {
	return Size(this->getContentSize().width, heightTable);
}

ssize_t NodeLichSuDoiThuong::numberOfCellsInTableView(TableView *table) {
	//CCLOG(" numberOfCellsInTableView %d ", lstMoneyLogs.size());
	return this->lstMoneyLogs.size();
}

void NodeLichSuDoiThuong::tableCellTouched(TableView *table, TableViewCell *cell) {
    CCLOG(" CEll %d ",cell->getIdx());
}

TableViewCell* NodeLichSuDoiThuong::tableCellAtIndex(TableView *table, ssize_t idx) {
	CCLOG("tableCellAtIndex");
    TableViewCell *cell = table->dequeueCell();
    if(!cell){
		cell = new TableViewCell();
		cell->autorelease();
    }

	cell->removeAllChildrenWithCleanup(true);
	auto item_money_log_his = ItemMoneyLog::createMoneyLog(this->lstMoneyLogs[idx], idx);
	item_money_log_his->setAnchorPoint(Vec2(0, 0));
	item_money_log_his->setPosition(Vec2(0, 0));
	cell->addChild(item_money_log_his);

	if (idx + 1 == this->lstMoneyLogs.size() && this->lstMoneyLogs.size() % NUM_LOAD_MORE_ITEM == 0){
		LoadingManager::getInstance()->showLoading();
        NetworkManager::getInstance()->getLookupMoneyHistoryMessage(idx + 1, NUM_LOAD_MORE_ITEM, 5);
	}

    return cell;
}

void NodeLichSuDoiThuong::onExit() {
    Node::onExit();
};