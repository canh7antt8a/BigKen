#include "PopupTopUser.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/TLMNConfig.hpp"
#include "UI/MButton.hpp"
#include "Utils/Common.h"
#include "Utils/NetworkManager.h"

using namespace cocos2d;

#define PADDING 25
#define MAX_REQUEST 20

bool PopupTopUser::init() {
    if (!Popup::init())
        return false;
    
    /*auto underBackground = MSprite::create("common_popup/bg_popup.png");
    underBackground->setPosition(Vec2(visibleSize.width/2 - underBackground->getWidth()/2,
                                      visibleSize.height/2 - underBackground->getHeight()/2));
    m_popupLayer->addChild(underBackground);*/
    
    backgroundPopup = MSprite::create("common_popup/bg_popup.png");
	backgroundPopup->setPosition(Vec2(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
		visibleSize.height / 2 - backgroundPopup->getHeight() / 2)));

	m_popupLayer->addChild(backgroundPopup);

    backgroundContentSize = background->getContentSize();

	auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
	bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
		backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
	backgroundPopup->addChild(bg_title_popup);

	auto title = Label::createWithTTF("BẢNG XẾP HẠNG", "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
	title->setColor(Color3B::BLACK);
	title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
		bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
	bg_title_popup->addChild(title);
    
	auto sprite_arrow_right = MSprite::create("common_popup/icon_arrow_right.png");
	contentPopupLeft = MSprite::create("common_popup/content_popup_left.png");
	contentPopupRight = MSprite::create("common_popup/content_popup_right.png");

	padding_left = (backgroundPopup->getWidth() - (sprite_arrow_right->getWidth() + contentPopupLeft->getWidth()
		+ contentPopupRight->getWidth())) / 2;

	contentPopupLeft->setPosition(Vec2(padding_left, backgroundPopup->getHeight() / 2 - contentPopupLeft->getHeight() / 2));
	backgroundPopup->addChild(contentPopupLeft);

	contentPopupRight->setPosition(Vec2(padding_left + contentPopupLeft->getWidth() + sprite_arrow_right->getWidth(),
		backgroundPopup->getHeight() / 2 - contentPopupRight->getHeight() / 2));
	backgroundPopup->addChild(contentPopupRight);

	addTab();

	tableView = TableView::create(this, Size(contentPopupRight->getWidth(), contentPopupRight->getHeight() - 10));
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDelegate(this);
	tableView->setBounceable(true);
	tableView->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	tableView->setPosition(contentPopupRight->getPosition());
	backgroundPopup->addChild(tableView);

    //btn close
	auto exit = MButton::create(IMAGE_CLOSE, TAG_POPUP_TOP_PLAYER_EXIT);
	exit->setPosition(Vec2(backgroundPopup->getWidth() - exit->getWidth() / 2,
		backgroundPopup->getHeight() - exit->getHeight() / 2));
	exit->addTouchEventListener(CC_CALLBACK_2(PopupTopUser::menuPopupCallBack, this));
	backgroundPopup->addChild(exit);

	this->scheduleUpdate();

    return true;
}

void PopupTopUser::update(float){
	getFilterTopUser();
}

void PopupTopUser::getFilterTopUser(){
	BINFilterTopUserResponse *response = (BINFilterTopUserResponse*) Common::getInstance()->checkEvent(NetworkManager::FILTER_TOP_USER);
	if (response != 0){
		CCLOG("filter top response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			if (response->topusers_size() > 0){
				lstTopUser.clear();
				for (int i = 0; i < response->topusers_size(); i ++){
					BINUserInfo userInfo = response->topusers(i);
					lstTopUser.push_back(userInfo);
				}
				tableView->reloadData();
			}
		}
	}
}

void PopupTopUser::addTab(){
    /*float height = backgroundPopup->getHeight();
    
    for(int i=0;i<3;i++){
        auto tabSprite = MSprite::create("popup_top_user/tab_1.png");
        tabSprite->setPosition(backgroundPopup->getPosition() + Vec2((5+tabSprite->getWidth())*i,height-10));
		m_popupLayer->addChild(tabSprite);
    }
    
    m_popupLayer->addChild(backgroundPopup);
    
    tab = MSprite::create("popup_top_user/tab_2.png");
    tab->setPosition(Vec2(0,height*(1-3.0f/418)));
    backgroundPopup->addChild(tab);
    
    vector<std::string> nameTabButton = {"TOP ĐỔI THƯỞNG","TOP ĐẠI GIA","TOP CAO THỦ"};
	vector<int> tagTabButton = { TAG_POPUP_TOP_PLAYER_TOP_DOI_THUONG, TAG_POPUP_TOP_PLAYER_TOP_DAI_GIA, TAG_POPUP_TOP_PLAYER_TOP_CAO_THU };
    
    for(int i=0;i<3;i++){ ///sprite tab null
        auto tabButton = MButton::create("popup_top_user/tab_1_null.png",nameTabButton[i],tab->getWidth()/3,tagTabButton[i]);
        tabButton->setPosition(Vec2((5+tabButton->getWidth())*i,height*(1-3.0f/418)));
        tabButton->addTouchEventListener(CC_CALLBACK_2(PopupTopUser::tabCallBack, this));
        backgroundPopup->addChild(tabButton);
    }*/

	auto spriteTab = MSprite::create("common_popup/tab_click.png");
	heightTab = spriteTab->getHeight();
	float posX = contentPopupLeft->getPosition().x + contentPopupLeft->getWidth() / 2 - spriteTab->getWidth() / 2;

	string rs_tab;
	for (int i = 0; i < 3; i++){
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

	vector<std::string> nameTabButton = { "TOP ĐỔI THƯỞNG", "TOP ĐẠI GIA", "TOP CAO THỦ" };
	vector<int> tagTabButton = { TAG_POPUP_TOP_PLAYER_TOP_DOI_THUONG, TAG_POPUP_TOP_PLAYER_TOP_DAI_GIA, TAG_POPUP_TOP_PLAYER_TOP_CAO_THU };

	for (int i = 0; i < 3; i++){ ///sprite tab null
		auto tabButton = MButton::create("common_popup/tab_click_null.png", nameTabButton[i], tab->getWidth() / 3, tagTabButton[i]);
		tabButton->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - (heightTab)*(i + 1)));
		tabButton->addTouchEventListener(CC_CALLBACK_2(PopupTopUser::tabCallBack, this));
		backgroundPopup->addChild(tabButton);
	}
}

void PopupTopUser::requestTopUser(){
	topUserType = ORDERBY_FIELD_TOP_USER::TOP_GOLD;
	NetworkManager::getInstance()->getFilterTopUserMessageFromServer(0, MAX_REQUEST, ORDERBY_FIELD_TOP_USER::TOP_GOLD);
}

void PopupTopUser::tabCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
		case TAG_POPUP_TOP_PLAYER_TOP_DOI_THUONG:
			topUserType = ORDERBY_FIELD_TOP_USER::TOP_GOLD;
			NetworkManager::getInstance()->getFilterTopUserMessageFromServer(0, MAX_REQUEST, ORDERBY_FIELD_TOP_USER::TOP_GOLD);
			tab->setTexture("common_popup/tab_clicked_round.png");
			tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - heightTab);
            break;
		case TAG_POPUP_TOP_PLAYER_TOP_DAI_GIA:
			topUserType = ORDERBY_FIELD_TOP_USER::TOP_CASH;
			NetworkManager::getInstance()->getFilterTopUserMessageFromServer(0, MAX_REQUEST, ORDERBY_FIELD_TOP_USER::TOP_CASH);
			tab->setTexture("common_popup/tab_clicked.png");
			tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - 2 * heightTab);
            break;
		case TAG_POPUP_TOP_PLAYER_TOP_CAO_THU:
			topUserType = ORDERBY_FIELD_TOP_USER::TOP_CAOTHU;
			NetworkManager::getInstance()->getFilterTopUserMessageFromServer(0, MAX_REQUEST, ORDERBY_FIELD_TOP_USER::TOP_CAOTHU);
			tab->setTexture("common_popup/tab_clicked.png");
			tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - 3 * heightTab);
            break;
        default:
            break;
        }
    }
}

void PopupTopUser::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
		case TAG_POPUP_TOP_PLAYER_EXIT:
            this->disappear();
            break;
        default:
            break;
                
        }
    }
}

//========================= TableView
Size PopupTopUser::cellSizeForTable(TableView *table) {
	return Size(contentPopupRight->getWidth(), (contentPopupRight->getHeight() - 10) / 5);
}

ssize_t PopupTopUser::numberOfCellsInTableView(TableView *table) {
	return lstTopUser.size();
}

void PopupTopUser::tableCellTouched(TableView *table, TableViewCell *cell) {
	CCLOG(" CEll %d ", cell->getIdx());
}

Node* PopupTopUser::getItemRow(BINUserInfo userInfo, int idx){
	Node* node = Node::create();

	auto background = MSprite::create("popup_top_user/bg_content_item_row.png");

	node->setContentSize(background->getContentSize());

	background->setPosition(Point::ZERO);

	if (idx % 2 == 0){
		node->addChild(background);
	}

	if (idx < 3){
		auto sp_stt = MSprite::create(StringUtils::format("popup_top_user/top%d.png", idx + 1));
		sp_stt->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		sp_stt->setPosition(Vec2(1.0f / 16 * background->getWidth(), background->getHeight() / 2));
		node->addChild(sp_stt);
	}
	else {
		auto label_stt = MLabel::create(StringUtils::format("%d", idx + 1), background->getHeight() / 3);
		label_stt->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label_stt->setColor(Color3B::BLACK);
		label_stt->setPosition(Vec2(1.0f / 16 * background->getWidth(), background->getHeight() / 2));
		node->addChild(label_stt);
	}

	string rs_bg_top_avatar;

	if (idx >= 3){
		rs_bg_top_avatar = "popup_top_user/bg_top_user_4.png";
	}
	else {
		rs_bg_top_avatar = StringUtils::format("popup_top_user/bg_top_user_%d.png", idx + 1);
	}

	auto bg_top_avatar = MSprite::create(rs_bg_top_avatar);
	bg_top_avatar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	bg_top_avatar->setPosition(Vec2(1.2f / 8 * background->getWidth(), background->getHeight() / 2));
	node->addChild(bg_top_avatar);

	int avatar_id = userInfo.avatarid();
	if (avatar_id < 100000){
		avatar_id = 0;
	}

	auto avatar = MSprite::create(StringUtils::format("avatar%d.png", avatar_id));
	avatar->setScale(0.7f*bg_top_avatar->getWidth() / avatar->getWidth());
	avatar->setContentSize(Size(0.7f*bg_top_avatar->getWidth(), 0.7f*bg_top_avatar->getHeight()));
	avatar->setPosition(Vec2(bg_top_avatar->getPosition().x + bg_top_avatar->getWidth()/2
		- avatar->getWidth() / 2, background->getHeight() / 2 - 0.7f*bg_top_avatar->getHeight() / 2));
	node->addChild(avatar);

	auto name_user = MLabel::create(userInfo.username(), bg_top_avatar->getHeight() / 3, Color3B::WHITE);
	name_user->setPosition(Vec2(bg_top_avatar->getPosition().x + bg_top_avatar->getWidth() + PADDING, 
		bg_top_avatar->getPosition().y + 1));
	node->addChild(name_user);

	auto level_user = MLabel::create(StringUtils::format("Level %d", userInfo.level().level()), bg_top_avatar->getHeight() / 4, Color3B(60, 185, 244));
	level_user->setPosition(Vec2(bg_top_avatar->getPosition().x + bg_top_avatar->getWidth() + PADDING, 
		bg_top_avatar->getPosition().y - 1 - level_user->getHeight()));
	node->addChild(level_user);

	string str_number;
	if (topUserType == ORDERBY_FIELD_TOP_USER::TOP_GOLD){
		str_number = Common::getInstance()->numberFormatWithCommas(userInfo.gold()) + " KEN";
	} else if (topUserType == ORDERBY_FIELD_TOP_USER::TOP_CASH){
		str_number = Common::getInstance()->numberFormatWithCommas(userInfo.cash()) + " XU";
	} if (topUserType == ORDERBY_FIELD_TOP_USER::TOP_CAOTHU){
		str_number = StringUtils::format("%d ván thắng", userInfo.totalwin());
	}

	auto label_number = MLabel::create(str_number, bg_top_avatar->getHeight() / 3, Color3B(254, 198, 54));
	label_number->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	label_number->setAlignment(TextHAlignment::RIGHT);
	label_number->setWidth(backgroundPopup->getWidth() * 3.0f / 8 );
	label_number->setLineBreakWithoutSpace(true);
	label_number->enableWrap(true);
	label_number->setPosition(Vec2(background->getWidth() - bg_top_avatar->getWidth()
		, background->getHeight() / 2));
	node->addChild(label_number);

	return node;
}

TableViewCell* PopupTopUser::tableCellAtIndex(TableView *table, ssize_t idx) {
	TableViewCell *cell = table->dequeueCell();
	if (!cell){
		cell = new TableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	auto itemCell = getItemRow(lstTopUser[idx], idx);
	cell->addChild(itemCell);

	return cell;
}

void PopupTopUser::onExit() {
    Popup::onExit();
}
