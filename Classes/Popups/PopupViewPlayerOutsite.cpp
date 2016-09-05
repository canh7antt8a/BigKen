#include "PopupViewPlayerOutsite.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Utils/NetworkManager.h"

bool PopupViewPlayerOutsite::init() {
    if (!Popup::init())
        return false;
    this->setAnchorPoint(Point::ZERO);
    
    backgroundPopup = MSprite::create("popup_view_player_outsite/bg_view_player_outsite.png");
    backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
                                      visibleSize.height / 2 - backgroundPopup->getHeight() / 2));
    
    m_popupLayer->setPosition(Vec2(visibleSize.width + backgroundPopup->getWidth() + 20,0));
    
    m_popupLayer->addChild(backgroundPopup);
    
    //=====
    
	auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
	bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2, 
		backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
	backgroundPopup->addChild(bg_title_popup);

	auto title = MLabel::create("DANH SÁCH", bg_title_popup->getHeight()/2);
	title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
			bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
	bg_title_popup->addChild(title);
	
	content_bg_popup = MSprite::create(RS_CONTENT_POPUP_VIEW_PLAYER_OUTSITE);
	float posX_content_bg_popup = backgroundPopup->getWidth() / 2 - content_bg_popup->getWidth() / 2;
	content_bg_popup->setPosition(Vec2(posX_content_bg_popup, posX_content_bg_popup));
	backgroundPopup->addChild(content_bg_popup);

	auto exit = MButton::create(IMAGE_CLOSE, TAG_POPUP_VIEW_PLAYER_OUTSITE_EXIT);
	exit->setPosition(Vec2(backgroundPopup->getWidth() - exit->getWidth() / 2,
		backgroundPopup->getHeight() - exit->getHeight() / 2));
	exit->addTouchEventListener(CC_CALLBACK_2(PopupViewPlayerOutsite::menuPopupCallBack, this));
	backgroundPopup->addChild(exit);

	tableView = TableView::create(this, Size(content_bg_popup->getWidth(), content_bg_popup->getHeight()));
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDelegate(this);
	tableView->setBounceable(true);
	tableView->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	tableView->setPosition(content_bg_popup->getPosition());
	backgroundPopup->addChild(tableView);
    
    return true;
}

void PopupViewPlayerOutsite::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED) {
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
			case TAG_POPUP_VIEW_PLAYER_OUTSITE_EXIT:
                this->disappear();
                break;
            default:
                break;
        }
    }
}

void PopupViewPlayerOutsite::setLstUserOutsite(vector<XocDiaPlayer> lstUserOutsite){
	this->lstUserOutsite = lstUserOutsite;

	tableView->reloadData();
}

Node* PopupViewPlayerOutsite::getItemRow(XocDiaPlayer player){
	Node* node = Node::create();

	auto background = MSprite::create(TABLE_BK_AVATAR);
	background->setPosition(Point::ZERO);
	node->addChild(background);
	
	auto avatar = MSprite::create(StringUtils::format("avatar%d.png", player.getAvatarId())
		, cocos2d::Size(background->getWidth(), background->getWidth()));
	avatar->setPosition(Vec2(background->getWidth() / 2 - avatar->getWidth() / 2, background->getHeight() / 2 - avatar->getHeight() / 2));
	node->addChild(avatar);

	auto name = MLabel::create(player.getName(), background->getWidth() / 5, cocos2d::Color3B::YELLOW);
	name->setPosition(Vec2(background->getWidth() / 2 - name->getWidth() / 2,
		background->getHeight() + 5));
	name->setAlignment(TextHAlignment::CENTER);
	node->addChild(name);

	auto player_id = MLabel::create(player.getID(), background->getWidth() / 5, cocos2d::Color3B::WHITE);
	player_id->setPosition(Vec2(Vec2(background->getWidth() / 2 - player_id->getWidth() / 2,
		-5 - player_id->getHeight())));
	player_id->setAlignment(TextHAlignment::CENTER);
	node->addChild(player_id);

	return node;
}

//========================= TableView
Size PopupViewPlayerOutsite::cellSizeForTable(TableView *table) {
	return Size(content_bg_popup->getContentSize().width, content_bg_popup->getContentSize().height / 2);
}

ssize_t PopupViewPlayerOutsite::numberOfCellsInTableView(TableView *table) {
	return this->lstUserOutsite.size();
}

void PopupViewPlayerOutsite::tableCellTouched(TableView *table, TableViewCell *cell) {
	CCLOG(" CEll %d ", cell->getIdx());
}

TableViewCell* PopupViewPlayerOutsite::tableCellAtIndex(TableView *table, ssize_t idx) {
	TableViewCell *cell = table->dequeueCell();
	if (!cell){
		cell = new TableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	int row = idx / 4;
	int column = idx % 4;
	int mod = lstUserOutsite.size() % 4;
	int sizeItem = mod > 0 ? mod : 4;

	if (column == 0){
		for (int i = 0; i < sizeItem; i++){
			auto itemCell = getItemRow(lstUserOutsite[4 * row + i]);
			itemCell->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
			itemCell->setPosition(Vec2(i * content_bg_popup->getWidth() / 4, 0));
			itemCell->setContentSize(Size(content_bg_popup->getWidth() / 4, content_bg_popup->getHeight() / 2));
			cell->addChild(itemCell);
		}
	}

	return cell;
}

void PopupViewPlayerOutsite::onExit() {
    Popup::onExit();
}
