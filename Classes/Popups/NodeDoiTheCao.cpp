#include "NodeDoiTheCao.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/LoadingManager.hpp"
#include "Utils/Image.h"
#include "ItemDoiThe.hpp"

#define PADDING_ITEM 20
#define NUMBER_ITEM_ROW 3

using namespace std;

bool NodeDoiTheCao::init() {
    if (!Node::init())
        return false;

	backgroundContent = MSprite::create("common_popup/content_popup_right.png");
	this->setContentSize(backgroundContent->getContentSize());

	this->addChild(backgroundContent);

	addTab();

	tableView = TableView::create(this, Size(backgroundContent->getWidth(), heightTable));
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDelegate(this);
	tableView->setBounceable(true);
	tableView->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	tableView->setEventDispatcher(_eventDispatcher);
	
	backgroundContent->addChild(tableView);

    return true;
}

void NodeDoiTheCao::addTab(){
	btnViettel = MButton::create(LOGO_VIETTEL_ACTIVE);
	btnViettel->setAnchorPoint(Vec2(0, 1));
	btnViettel->setPosition(Vec2(backgroundContent->getWidth() / 2 - btnViettel->getWidth() * 2,
		backgroundContent->getHeight() - btnViettel->getHeight() / 4));
	btnViettel->addTouchEventListener(CC_CALLBACK_2(NodeDoiTheCao::menuPopupCallBack, this));
	btnViettel->setTag(TAG_POPUP_DOITHE_VIETTEL);
	backgroundContent->addChild(btnViettel);

	type_selected = "VTT";

	btnVinaphone = MButton::create(LOGO_VINAPHONE);
	btnVinaphone->setAnchorPoint(Vec2(0, 1));
	btnVinaphone->setPosition(Vec2(backgroundContent->getWidth() / 2 - btnVinaphone->getWidth() / 2,
		btnViettel->getPosition().y));
	btnVinaphone->addTouchEventListener(CC_CALLBACK_2(NodeDoiTheCao::menuPopupCallBack, this));
	btnVinaphone->setTag(TAG_POPUP_DOITHE_VINAPHONE);
	backgroundContent->addChild(btnVinaphone);

	btnMobiphone = MButton::create(LOGO_MOBIFONE);
	btnMobiphone->setAnchorPoint(Vec2(0, 1));
	btnMobiphone->setPosition(Vec2(backgroundContent->getWidth() / 2 + btnVinaphone->getWidth(),
		btnVinaphone->getPosition().y));
	btnMobiphone->addTouchEventListener(CC_CALLBACK_2(NodeDoiTheCao::menuPopupCallBack, this));
	btnMobiphone->setTag(TAG_POPUP_DOITHE_MOBIFONE);
	backgroundContent->addChild(btnMobiphone);

	heightTable = backgroundContent->getHeight() - 5 * btnViettel->getHeight() / 4;
}

void NodeDoiTheCao::menuPopupCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type){
	if (type == ui::Widget::TouchEventType::ENDED){
		MButton *button = (MButton*)sender;
		int tag = button->getTag();
		switch (tag) {
			case TAG_POPUP_DOITHE_VIETTEL:
				btnVinaphone->loadTextureNormal(LOGO_VINAPHONE);
				btnViettel->loadTextureNormal(LOGO_VIETTEL_ACTIVE);
				btnMobiphone->loadTextureNormal(LOGO_MOBIFONE);
				type_selected = "VTT";

				showTheCao();

				break;
			case TAG_POPUP_DOITHE_VINAPHONE:
				btnVinaphone->loadTextureNormal(LOGO_VINAPHONE_ACTIVE);
				btnViettel->loadTextureNormal(LOGO_VIETTEL);
				btnMobiphone->loadTextureNormal(LOGO_MOBIFONE);
				type_selected = "VNP";

				showTheCao();

				break;
			case TAG_POPUP_DOITHE_MOBIFONE:
				btnVinaphone->loadTextureNormal(LOGO_VINAPHONE);
				btnViettel->loadTextureNormal(LOGO_VIETTEL);
				btnMobiphone->loadTextureNormal(LOGO_MOBIFONE_ACTIVE);
				type_selected = "VMS";

				showTheCao();

				break;
			default:
				break;
		}
	}
}

float NodeDoiTheCao::getWidth(){
	return this->getContentSize().width;
}

float NodeDoiTheCao::getHeight(){
	return this->getContentSize().height;
}

//========================= TableView

Size NodeDoiTheCao::cellSizeForTable(TableView *table) {
	return Size(this->getContentSize().width, heightTable / 2);
}

ssize_t NodeDoiTheCao::numberOfCellsInTableView(TableView *table) {
	return (this->lstAssetConfig.size() / NUMBER_ITEM_ROW + this->lstAssetConfig.size() % NUMBER_ITEM_ROW);
}

void NodeDoiTheCao::tableCellTouched(TableView *table, TableViewCell *cell) {
    CCLOG(" CEll %d ",cell->getIdx());
}

void NodeDoiTheCao::setAssets(vector<BINAsset> assets){
	this->lstAsset = assets;
}

void NodeDoiTheCao::showTheCao(){
	this->lstAssetConfig.clear();

	for (int i = 0; i < this->lstAsset.size(); i++){
		if (this->lstAsset[i].provider() == type_selected){
			lstAssetConfig.push_back(this->lstAsset[i]);
		}
	}

	tableView->reloadData();
}

TableViewCell* NodeDoiTheCao::tableCellAtIndex(TableView *table, ssize_t idx) {
    TableViewCell *cell = table->dequeueCell();
    if(!cell){
		cell = new TableViewCell();
		cell->autorelease();
    }

	cell->removeAllChildrenWithCleanup(true);

	int column = idx % NUMBER_ITEM_ROW;
	int mod = lstAssetConfig.size() % NUMBER_ITEM_ROW;
	int sizeItem = mod > 0 ? mod : NUMBER_ITEM_ROW;

	for (int i = 0; i < sizeItem; i++){
		auto itemCell = ItemDoiThe::create(lstAssetConfig[NUMBER_ITEM_ROW * idx + i], backgroundContent->getWidth(), heightTable);//getItemRow();
		itemCell->setPosition(Vec2(i * backgroundContent->getWidth() / NUMBER_ITEM_ROW, 0));
		itemCell->setContentSize(Size(backgroundContent->getWidth() / NUMBER_ITEM_ROW, heightTable / 2));
		cell->addChild(itemCell);
	}

    return cell;
}

void NodeDoiTheCao::onExit() {
    Node::onExit();
};