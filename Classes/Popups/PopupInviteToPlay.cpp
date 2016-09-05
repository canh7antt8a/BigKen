#include "PopupInviteToPlay.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/TLMNConfig.hpp"
#include "UI/MButton.hpp"
#include "Utils/Common.h"
#include "Utils/NetworkManager.h"

using namespace cocos2d;

#define PADDING 25
#define MAX_REQUEST 20

bool PopupInviteToPlay::init() {
    if (!Popup::init())
        return false;
    
    backgroundPopup = MSprite::create("popup_moichoi/bg_popup.png");
    backgroundPopup->setPosition(Vec2(visibleSize.width/2 - backgroundPopup->getWidth()/2,
                                      visibleSize.height/2 - backgroundPopup->getHeight()/2));
    m_popupLayer->addChild(backgroundPopup);

	auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
	bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
		backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
	backgroundPopup->addChild(bg_title_popup);

	contentPopup = MSprite::create("popup_moichoi/content_popup.png");
	contentPopup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - contentPopup->getWidth() / 2,
		bg_title_popup->getPosition().y - 10 - contentPopup->getHeight()));
	backgroundPopup->addChild(contentPopup);

	backgroundContentSize = contentPopup->getContentSize();

	auto title = Label::createWithTTF("MỜI BẠN BÈ CHƠI", "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
	title->setColor(Color3B::BLACK);
	title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
		bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
	bg_title_popup->addChild(title);

	auto btn_invite_all = MButton::create("btn_boluot.png", "Chọn tất cả", 30, TAG_POPUP_INVITE_ALL);
	btn_invite_all->setPosition(Vec2(backgroundPopup->getWidth() / 2 - 20 - btn_invite_all->getWidth()
		, contentPopup->getPosition().y / 2 - btn_invite_all->getHeight() / 2));
	btn_invite_all->addTouchEventListener(CC_CALLBACK_2(PopupInviteToPlay::menuPopupCallBack, this));

	auto btn_invite_select = MButton::create("btn_danhbai.png", "Mời", 30, TAG_POPUP_INVITE_SELECT);
	btn_invite_select->setPosition(Vec2(backgroundPopup->getWidth() / 2 + 20
		, contentPopup->getPosition().y / 2 - btn_invite_select->getHeight() / 2));
	btn_invite_select->addTouchEventListener(CC_CALLBACK_2(PopupInviteToPlay::menuPopupCallBack, this));

	backgroundPopup->addChild(btn_invite_all);
	backgroundPopup->addChild(btn_invite_select);

	tableView = TableView::create(this, Size(contentPopup->getWidth(), contentPopup->getHeight()));
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDelegate(this);
	tableView->setBounceable(true);
	tableView->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	contentPopup->addChild(tableView);

    //btn close
	auto exit = MButton::create(IMAGE_CLOSE, TAG_POPUP_INVITE_TO_PLAY_EXIT);
	exit->setPosition(Vec2(backgroundPopup->getWidth() - exit->getWidth() / 2,
		backgroundPopup->getHeight() - exit->getHeight() / 2));
	exit->addTouchEventListener(CC_CALLBACK_2(PopupInviteToPlay::menuPopupCallBack, this));
	backgroundPopup->addChild(exit);

	this->scheduleUpdate();

    return true;
}

void PopupInviteToPlay::setRoomIndex(int roomIndex){
	this->roomIndex = roomIndex;
}

void PopupInviteToPlay::setVipRoom(bool isVipRoom){
	this->isVipRoom = isVipRoom;
}

void PopupInviteToPlay::removeItemSelected(long userId){
	for (int i = 0; i < lstIdFriendChecked.size(); i++){
		if (lstIdFriendChecked[i] == userId){
			lstIdFriendChecked.erase(lstIdFriendChecked.begin() + i);
			break;
		}
	}

	/*CCLOG("remove item selected ----------------------");
	for (int i = 0; i < lstIdFriendChecked.size(); i++){
		CCLOG("%d", lstIdFriendChecked[i]);
	}*/
}

void PopupInviteToPlay::addItemSelected(long userId){
	lstIdFriendChecked.push_back(userId);

	/*CCLOG("add item selected ----------------------");
	for (int i = 0; i < lstIdFriendChecked.size(); i++){
		CCLOG("%d", lstIdFriendChecked[i]);
	}*/
}

void PopupInviteToPlay::update(float){
	lookupUserToInviteResponse();
	inviteToRoomResponse();
}

void PopupInviteToPlay::lookupUserToInviteResponse(){
	BINLookUpUserToInviteResponse *response = (BINLookUpUserToInviteResponse*) Common::getInstance()->checkEvent(NetworkManager::LOOKUP_USER_TO_INVITE);
	if (response != 0){
		CCLOG("lookup user to invite response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			lstFriend.clear();
			for (int i = 0; i < response->suggestusers_size(); i++){
				BINUserInfo userInfo = response->suggestusers(i);
				lstFriend.push_back(userInfo);
			}

			tableView->reloadData();
		}
	}
}

void PopupInviteToPlay::inviteToRoomResponse(){
	BINInviteToRoomResponse *response = (BINInviteToRoomResponse*)Common::getInstance()->checkEvent(NetworkManager::INVITE_TO_ROOM);
	if (response != 0){
		CCLOG("invite to room response: %s", response->DebugString().c_str());
	}
}

void PopupInviteToPlay::getLookupUserToInviteFromServer(){
	NetworkManager::getInstance()->getLookupUserToInviteFromServer(roomIndex, MAX_REQUEST);
}

void PopupInviteToPlay::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
		case TAG_POPUP_INVITE_TO_PLAY_EXIT:
			checkAll = false;
            this->disappear();
            break;
		case TAG_POPUP_INVITE_ALL:
			if (!lstFriend.empty()){
				lstIdFriendChecked.clear();
				if (!checkAll){
					checkAll = true;
					for (int i = 0; i < lstFriend.size(); i++){
						lstIdFriendChecked.push_back(lstFriend[i].userid());
					}
					((MButton*)backgroundPopup->getChildByTag(TAG_POPUP_INVITE_ALL))->setTitleText("Bỏ chọn tất cả");
				}
				else {
					checkAll = false;
					((MButton*)backgroundPopup->getChildByTag(TAG_POPUP_INVITE_ALL))->setTitleText("Chọn tất cả");
				}

				tableView->reloadData();
			}
			break;
		case TAG_POPUP_INVITE_SELECT:
			if (!lstIdFriendChecked.empty()){
				NetworkManager::getInstance()->getInviteToRoomFromServer(roomIndex, lstIdFriendChecked);
			}
			this->disappear();
			break;
        default:
            break;
                
        }
    }
}

//========================= TableView
Size PopupInviteToPlay::cellSizeForTable(TableView *table) {
	return Size(contentPopup->getContentSize().width, contentPopup->getContentSize().height / 5);
}

ssize_t PopupInviteToPlay::numberOfCellsInTableView(TableView *table) {
	return lstFriend.size();
}

void PopupInviteToPlay::tableCellTouched(TableView *table, TableViewCell *cell) {
	CCLOG(" CEll %d ", cell->getIdx());
}

TableViewCell* PopupInviteToPlay::tableCellAtIndex(TableView *table, ssize_t idx) {
	TableViewCell *cell = table->dequeueCell();
	if (!cell){
		cell = new TableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	auto item = ItemInviteToPlay::create(Size(backgroundContentSize.width, backgroundContentSize.height / 5),
		lstFriend[idx], isVipRoom, checkAll, this);
	cell->addChild(item);

	return cell;
}

void PopupInviteToPlay::onExit() {
    Popup::onExit();
}
