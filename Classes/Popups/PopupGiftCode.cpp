#include "PopupGiftCode.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/TLMNConfig.hpp"
#include "UI/MButton.hpp"
#include "Utils/Common.h"
//#include "Utils/NetworkManager.h"
#include "UI/MEditBox.hpp"

using namespace cocos2d;

#define PADDING 25
#define MAX_REQUEST 20

bool PopupGiftCode::init() {
    if (!Popup::init())
        return false;
    
    backgroundPopup = MSprite::create("common_popup/bg_popup.png");
    backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
		visibleSize.height / 2 - backgroundPopup->getHeight() / 2));

	m_popupLayer->addChild(backgroundPopup);

	auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
	bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
		backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
	backgroundPopup->addChild(bg_title_popup);

	auto title = Label::createWithTTF("QUÀ TẶNG", "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
	title->setColor(Color3B::BLACK);
	title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
		bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
	bg_title_popup->addChild(title);
    
	auto sprite_arrow_right = MSprite::create("common_popup/icon_arrow_right.png");

	contentPopupLeft = MSprite::create("common_popup/content_popup_left.png");
	nodeInputGiftCode = getNodeInputGiftCode();
	nodeReceiveGiftCode = getNodeReceiveGiftCode();

	float padding_left = (backgroundPopup->getWidth() - (sprite_arrow_right->getWidth() + contentPopupLeft->getWidth() 
		+ nodeInputGiftCode->getContentSize().width)) / 2;

	contentPopupLeft->setPosition(Vec2(padding_left, backgroundPopup->getHeight() / 2 - contentPopupLeft->getHeight() / 2));
	
	nodeInputGiftCode->setPosition(Vec2(padding_left + contentPopupLeft->getWidth() + sprite_arrow_right->getWidth(),
		backgroundPopup->getHeight() / 2 - nodeInputGiftCode->getContentSize().height / 2));

	nodeReceiveGiftCode->setPosition(nodeInputGiftCode->getPosition());

	backgroundPopup->addChild(contentPopupLeft);
	backgroundPopup->addChild(nodeInputGiftCode);
	backgroundPopup->addChild(nodeReceiveGiftCode);

	nodeReceiveGiftCode->setVisible(false);
    
	addTab();

    //btn close
	auto exit = MButton::create(IMAGE_CLOSE, TAG_POPUP_GIFTCODE_EXIT);
	exit->setPosition(Vec2(backgroundPopup->getWidth() - exit->getWidth() / 2,
		backgroundPopup->getHeight() - exit->getHeight() / 2));
	exit->addTouchEventListener(CC_CALLBACK_2(PopupGiftCode::menuPopupCallBack, this));
	backgroundPopup->addChild(exit);

	this->scheduleUpdate();

    return true;
}

Node* PopupGiftCode::getNodeInputGiftCode(){
	Node* inputGiftCode = Node::create();

	auto contentPopupRight = MSprite::create("common_popup/content_popup_right.png");
	inputGiftCode->addChild(contentPopupRight);

	inputGiftCode->setContentSize(contentPopupRight->getContentSize());

	auto bg_editgiftcode = MSprite::create("qua_tang/edit_giftcode.png");

	edit_giftcode = MEditBox::create(bg_editgiftcode->getContentSize(), LOGIN_EDIT_PASSWORD, bg_editgiftcode->getHeight() / 3);
	edit_giftcode->setPosition(Vec2(contentPopupRight->getWidth() / 2 - edit_giftcode->getWidth() / 2,
		contentPopupRight->getHeight() / 2 + 10));
	edit_giftcode->setPlaceHolder("  Nhập giftcode");
	edit_giftcode->setMaxLength(15);

	auto lb_giftcode = MLabel::create("Nhập giftcode :" , 40);
	lb_giftcode->setPosition(Vec2(contentPopupRight->getWidth() / 2 - lb_giftcode->getWidth() / 2,
		edit_giftcode->getPosition().y + 2 * edit_giftcode->getHeight()));

	auto btn_confirm_giftcode = MButton::create("btn_dangnhap.png", "Xác nhận", 30, TAG_BTN_XACNHAN_GIFTCODE);
	btn_confirm_giftcode->setPosition(Vec2(contentPopupRight->getWidth() / 2 - btn_confirm_giftcode->getWidth() / 2,
		edit_giftcode->getPosition().y - 10 - edit_giftcode->getHeight() - btn_confirm_giftcode->getHeight()));
	btn_confirm_giftcode->addTouchEventListener(CC_CALLBACK_2(PopupGiftCode::menuPopupCallBack, this));

	contentPopupRight->addChild(edit_giftcode);
	contentPopupRight->addChild(lb_giftcode);
	contentPopupRight->addChild(btn_confirm_giftcode);

	return inputGiftCode;
}

Node* PopupGiftCode::getNodeReceiveGiftCode(){
	Node* receiveGiftCode = Node::create();

	auto contentPopupRight = MSprite::create("common_popup/content_popup_right.png");
	receiveGiftCode->addChild(contentPopupRight);

	receiveGiftCode->setContentSize(contentPopupRight->getContentSize());

	float height = contentPopupRight->getHeight() / 10;

	tableView = TableView::create(this, Size(contentPopupRight->getWidth(), contentPopupRight->getHeight() - height));
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDelegate(this);
	tableView->setBounceable(true);
	tableView->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	contentPopupRight->addChild(tableView);

	auto it_vertical1 = MSprite::create("qua_tang/item_vertical.png");
	it_vertical1->setPosition(Vec2(1.3f * contentPopupRight->getWidth() / 3.6, 0));
	contentPopupRight->addChild(it_vertical1);

	auto it_vertical2 = MSprite::create("qua_tang/item_vertical.png");
	it_vertical2->setPosition(Vec2(2.3f * contentPopupRight->getWidth() / 3.6, 0));
	contentPopupRight->addChild(it_vertical2);

	auto txt_giftcode = MLabel::create("Giftcode", height / 2);
	txt_giftcode->setAnchorPoint(Point::ANCHOR_MIDDLE);
	txt_giftcode->setPosition(Vec2(1.3f * contentPopupRight->getWidth() / (3.6 * 2), contentPopupRight->getHeight() - height / 2));
	contentPopupRight->addChild(txt_giftcode);

	auto txt_value = MLabel::create("Giá trị", height / 2);
	txt_value->setAnchorPoint(Point::ANCHOR_MIDDLE);
	txt_value->setPosition(Vec2(contentPopupRight->getWidth() / 2, txt_giftcode->getPosition().y));
	contentPopupRight->addChild(txt_value);

	auto txt_date_receive = MLabel::create("Ngày nhận", height / 2);
	txt_date_receive->setAnchorPoint(Point::ANCHOR_MIDDLE);
	txt_date_receive->setPosition(Vec2((2.3f / 3.6 + 1.3f / (3.6 * 2)) * contentPopupRight->getWidth(), txt_giftcode->getPosition().y));
	contentPopupRight->addChild(txt_date_receive);

	return receiveGiftCode;
}

void PopupGiftCode::update(float){
	getRedeemGiftCode();
	getRedeemGiftCodeHistory();
}

void PopupGiftCode::addTab(){
	auto spriteTab = MSprite::create("common_popup/tab_click.png");
	heightTab = spriteTab->getHeight();
	float posX = contentPopupLeft->getPosition().x + contentPopupLeft->getWidth() / 2 - spriteTab->getWidth() / 2;

	string rs_tab;
    for(int i=0;i<2;i++){
		if (i == 0){
			rs_tab = "common_popup/tab_click_round.png";
		}
		else {
			rs_tab = "common_popup/tab_click.png";
		}
		auto tabSprite = MSprite::create(rs_tab);
		tabSprite->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - (heightTab)*(i + 1)));
        backgroundPopup->addChild(tabSprite);
    }
    
    tab = MSprite::create("common_popup/tab_clicked_round.png");
	tab->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - heightTab));
	backgroundPopup->addChild(tab);
    
    vector<std::string> nameTabButton = {"Nhập giftcode","Giftcode đã nhận"};
	vector<int> tagTabButton = { 1, 2 };
    
    for(int i=0;i<2;i++){ ///sprite tab null
        auto tabButton = MButton::create("common_popup/tab_click_null.png",nameTabButton[i],tab->getWidth()/3,tagTabButton[i]);
		tabButton->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - (heightTab)*(i + 1)));
        tabButton->addTouchEventListener(CC_CALLBACK_2(PopupGiftCode::tabCallBack, this));
        backgroundPopup->addChild(tabButton);
    }
}

void PopupGiftCode::getRedeemGiftCode(){
	BINRedeemGiftCodeResponse *response = (BINRedeemGiftCodeResponse*)Common::getInstance()->checkEvent(NetworkManager::REDEEM_GIFT_CODE);
	if (response != 0){
		CCLOG("redeem gift code response: %s", response->DebugString().c_str());
		if (response->responsecode() && response->success()){
			string str_cash = "";
			string str_gold = "";
			string message = "Bạn đã nhận được giftcode giá trị ";
			for (int i = 0; i < response->args_size(); i++) {
				BINMapFieldEntry entry = response->args(i);
				if (entry.key() == "cash") {
					str_cash = entry.value() + " XU";
				}
				else if (entry.key() == "gold"){
					str_gold = entry.value() + " KEN";
				}
			}

			if (!str_gold.empty() && !str_cash.empty()){
				message += str_cash + " và " + str_gold;
				showGame->showToast(message.c_str(), 2);
			}
			else if (!str_gold.empty()){
				message += str_gold;
				showGame->showToast(message.c_str(), 2);
			}
			else if (!str_cash.empty()){
				message += str_cash;
				showGame->showToast(message.c_str(), 2);
			}
		}
		else {
			if (response->has_message()){
				//show toast
				showGame->showToast(response->message().c_str(), 2);
			}
		}
	}
}

void PopupGiftCode::getRedeemGiftCodeHistory(){
	BINRedeemGiftCodeHistoryResponse *response = (BINRedeemGiftCodeHistoryResponse*)
		Common::getInstance()->checkEvent(NetworkManager::REDEEM_GIFT_CODE_HISTORY);
	if (response != 0){
		CCLOG("redeem gift code history response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			lstGiftCodeHistory.clear();
			for (int i = 0; i < response->giftcodes_size(); i++){
				BINGiftCode giftCode = response->giftcodes(i);
				lstGiftCodeHistory.push_back(giftCode);
			}

			tableView->reloadData();
		}
		else {
			if (response->has_message()){
				//show toast
				showGame->showToast(response->message().c_str(), 2);
			}
		}
	}
}

void PopupGiftCode::requestRedeemGiftCode(){
	NetworkManager::getInstance()->getRedeemGiftCodeFromServer(edit_giftcode->getText());
}

void PopupGiftCode::requestRedeemGiftCodeHistory(){
	NetworkManager::getInstance()->getRedeemGiftCodeHistoryFromServer(0, MAX_REQUEST);
}

void PopupGiftCode::setContext(ShowGame* showGame){
	this->showGame = showGame;
}

void PopupGiftCode::tabCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
		case 1:
			{
				tab->setTexture("common_popup/tab_clicked_round.png");
				tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - heightTab);
				nodeInputGiftCode->setVisible(true);
				nodeReceiveGiftCode->setVisible(false);
			}
            break;
		case 2:
			{
				tab->setTexture("common_popup/tab_clicked.png");
				tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - 2 * heightTab);
				nodeInputGiftCode->setVisible(false);
				nodeReceiveGiftCode->setVisible(true);

				requestRedeemGiftCodeHistory();

				tableView->reloadData();
			}
			break;
        default:
            break;
        }
    }
}

void PopupGiftCode::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
		case TAG_BTN_XACNHAN_GIFTCODE:
			{
				string text_giftcode = edit_giftcode->getText();
				if (!text_giftcode.empty()){
					NetworkManager::getInstance()->getRedeemGiftCodeFromServer(edit_giftcode->getText());
					edit_giftcode->setText("");
				}
			}
			
			break;
		case TAG_POPUP_GIFTCODE_EXIT:
            this->disappear();
            break;
        default:
            break;
                
        }
    }
}

//========================= TableView
Size PopupGiftCode::cellSizeForTable(TableView *table) {
	return Size(nodeInputGiftCode->getContentSize().width, 0.9f * nodeInputGiftCode->getContentSize().height / 5);
}

ssize_t PopupGiftCode::numberOfCellsInTableView(TableView *table) {
	return lstGiftCodeHistory.size();
}

void PopupGiftCode::tableCellTouched(TableView *table, TableViewCell *cell) {
	CCLOG(" CEll %d ", cell->getIdx());
}

Node* PopupGiftCode::getItemRow(BINGiftCode binGiftCode){
	Node* node = Node::create();

	node->setContentSize(Size(nodeInputGiftCode->getContentSize().width, 0.9f * nodeInputGiftCode->getContentSize().height / 5));

	auto it_horizontal = MSprite::create("qua_tang/item_horizontal.png");
	node->addChild(it_horizontal);

	auto txt_giftcode = MLabel::create(binGiftCode.giftcode(), node->getContentSize().height / 3, Color3B::YELLOW);
	txt_giftcode->setAnchorPoint(Point::ANCHOR_MIDDLE);
	txt_giftcode->setPosition(Vec2(1.3f * node->getContentSize().width / (3.6 * 2), node->getContentSize().height / 2));
	node->addChild(txt_giftcode);

	auto text_gold = MLabel::create(Common::getInstance()->convertIntToMoneyView(binGiftCode.gold())
		, node->getContentSize().height / 3, Color3B::YELLOW);
	text_gold->setAnchorPoint(Point::ANCHOR_MIDDLE);

	auto text_cash = MLabel::create(Common::getInstance()->convertIntToMoneyView(binGiftCode.cash())
		, node->getContentSize().height / 3, Color3B::YELLOW);
	text_cash->setAnchorPoint(Point::ANCHOR_MIDDLE);

	auto ic_gold = MSprite::create("sprite_ken_mini.png");
	ic_gold->setAnchorPoint(Point::ANCHOR_MIDDLE);
	auto ic_cash = MSprite::create("sprite_xu_mini.png");
	ic_cash->setAnchorPoint(Point::ANCHOR_MIDDLE);

	if (binGiftCode.gold() > 0 && binGiftCode.cash() > 0){
		text_gold->setPosition(Vec2(node->getContentSize().width / 2 - 5 - text_gold->getWidth() / 2
			, 3 * node->getContentSize().height / 4));
		text_cash->setPosition(Vec2(node->getContentSize().width / 2 - 5 - text_cash->getWidth() / 2
			, node->getContentSize().height / 4));

		ic_gold->setPosition(Vec2(node->getContentSize().width / 2 + 5 + text_gold->getWidth() / 2
			, 3 * node->getContentSize().height / 4));
		ic_cash->setPosition(Vec2(node->getContentSize().width / 2 + 5 + text_gold->getWidth() / 2
			, node->getContentSize().height / 4));

		node->addChild(text_gold);
		node->addChild(text_cash);
		node->addChild(ic_gold);
		node->addChild(ic_cash);
	}
	else if (binGiftCode.gold() > 0){
		text_gold->setPosition(Vec2(node->getContentSize().width / 2 - 5 - text_gold->getWidth() / 2
			, txt_giftcode->getPosition().y));

		ic_gold->setPosition(Vec2(node->getContentSize().width / 2 + 5 + text_gold->getWidth() / 2
			, node->getContentSize().height / 2));

		node->addChild(text_gold);
		node->addChild(ic_gold);
	}
	else if (binGiftCode.cash() > 0){
		text_cash->setPosition(Vec2(node->getContentSize().width / 2 - 5 - text_cash->getWidth() / 2
			, txt_giftcode->getPosition().y));

		ic_cash->setPosition(Vec2(node->getContentSize().width / 2 + 5 + text_gold->getWidth() / 2
			, node->getContentSize().height / 2));

		node->addChild(text_cash);
		node->addChild(ic_cash);
	}

	auto lb_time = MLabel::create(Common::getInstance()->convertMillisecondToTime(binGiftCode.redeemtime(), "%d/%m/%Y")
		, node->getContentSize().height / 3, Color3B::YELLOW);
	lb_time->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_time->setPosition(Vec2((2.3f / 3.6 + 1.3f / (3.6 * 2))* node->getContentSize().width
		, node->getContentSize().height / 2));
	node->addChild(lb_time);

	return node;
}

TableViewCell* PopupGiftCode::tableCellAtIndex(TableView *table, ssize_t idx) {
	TableViewCell *cell = table->dequeueCell();
	if (!cell){
		cell = new TableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	auto itemCell = getItemRow(lstGiftCodeHistory[idx]);
	cell->addChild(itemCell);

	return cell;
}

void PopupGiftCode::onExit() {
    Popup::onExit();
}
