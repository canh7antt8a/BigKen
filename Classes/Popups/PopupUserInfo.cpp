
#include "PopupUserInfo.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "UI/MButton.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/LoadingManager.hpp"

void PopupUserInfo::setPositionTab(int positionTab){
	this->positionTab = positionTab;
}

int PopupUserInfo::getPositionTab(){
	return this->positionTab;
}

bool PopupUserInfo::init() {
    if (!Popup::init())
        return false;
    
	//new
	backgroundPopup = MSprite::create("user_info/bg_popup/bg_popup.png");
	backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
		visibleSize.height / 2 - backgroundPopup->getHeight() / 2));

	m_popupLayer->addChild(backgroundPopup);

	auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
	bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
		backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
	backgroundPopup->addChild(bg_title_popup);

	auto title = Label::createWithTTF("HỒ SƠ", "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
	title->setColor(Color3B::BLACK);
	title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
		bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
	bg_title_popup->addChild(title);

	auto sprite_arrow_right = MSprite::create("common_popup/icon_arrow_right.png");

	contentPopupLeft = MSprite::create("user_info/bg_popup/content_popup_left.png");
	auto contentPopupRight = MSprite::create("user_info/bg_popup/content_popup_right.png");
	padding_left = (backgroundPopup->getWidth() - (sprite_arrow_right->getWidth() + contentPopupLeft->getWidth()
		+ contentPopupRight->getWidth())) / 2;

	contentPopupLeft->setPosition(Vec2(padding_left, backgroundPopup->getHeight() / 2 - contentPopupLeft->getHeight() / 2));

	backgroundPopup->addChild(contentPopupLeft);

	addTab();

	addMenu();

	auto exit = MButton::create(IMAGE_CLOSE, TAG_CLOSE);
	exit->setPosition(Vec2(backgroundPopup->getWidth() - exit->getWidth() / 2,
		backgroundPopup->getHeight() - exit->getHeight() / 2));
	exit->addTouchEventListener(CC_CALLBACK_2(PopupUserInfo::menuPopupCallBack, this));
	backgroundPopup->addChild(exit);

	//end new

    /*auto underBackground = MSprite::create("user_info/sprite_background_user.png");
    underBackground->setPosition(Vec2(visibleSize.width/2 - underBackground->getWidth()/2,
                                      visibleSize.height/2 - underBackground->getHeight()/2));
    m_popupLayer->addChild(underBackground);
    
    backgroundPopup = MSprite::create("user_info/sprite_layer_user.png");
    backgroundPopup->setPosition(Vec2(visibleSize.width / 2 - backgroundPopup->getWidth() / 2,
        underBackground->getPosition().y + underBackground->getWidth()/2 - backgroundPopup->getWidth()/2 ));

    backgroundContentSize = background->getContentSize();

	m_popupLayer->addChild(backgroundPopup);

	addTab();

	addMenu();*/

    //btn close
    /*auto btn_close = MButton::create(IMAGE_CLOSE, TAG_CLOSE);
    btn_close->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	btn_close->setPosition(Vec2(underBackground->getPosition().x + underBackground->getWidth() - btn_close->getWidth() - 10,
		underBackground->getPosition().y + underBackground->getHeight() - btn_close->getHeight() - 10));
    btn_close->addTouchEventListener(CC_CALLBACK_2(PopupUserInfo::menuPopupCallBack, this));
	m_popupLayer->addChild(btn_close);*/

    return true;
}

void PopupUserInfo::addMenu(){
	auto sprite_arrow_right = MSprite::create("common_popup/icon_arrow_right.png");

	tab_user = NodeHoSo::create();
	tab_user->setPosition(backgroundPopup->getPosition()+  Vec2(padding_left + contentPopupLeft->getWidth() + sprite_arrow_right->getWidth()
		, backgroundPopup->getHeight() / 2 - tab_user->getContentSize().height / 2));

	tab_email = NodeHopThu::create();
	//tab_email->setContentSize(Size(backgroundPopup->getContentSize().width - 10, backgroundPopup->getContentSize().height - 10));
	tab_email->setPosition(tab_user->getPosition());

	tab_ls_doithuong = NodeLichSuDoiThuong::create();
	tab_ls_doithuong->setPosition(tab_user->getPosition());

	m_popupLayer->addChild(tab_user);
	m_popupLayer->addChild(tab_email);
	m_popupLayer->addChild(tab_ls_doithuong);
}

void PopupUserInfo::showPositionTab(int positionTab){
	if (positionTab == 1){  //hien thi tab thong tin nguoi dung
		tab_user->setVisible(true);
		tab_email->setVisible(false);
		tab_ls_doithuong->setVisible(false);

		targetUserId = Common::getInstance()->getUserId();

		if (targetUserId > 0){
			NetworkManager::getInstance()->getViewUserInfoFromServer(targetUserId);
		}

		tab->setTexture("user_info/bg_popup/tab_clicked_round.png");
		tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - heightTab);
	}
	else if (positionTab == 2) { //hien thi tab email 
		tab_user->setVisible(false);
		tab_email->setVisible(true);
		tab_ls_doithuong->setVisible(false);

		LoadingManager::getInstance()->showLoading();
		tab_email->resetMail();
		NetworkManager::getInstance()->getFilterMailFromServer(0, 10, -1);

		tab->setTexture("user_info/bg_popup/tab_clicked.png");
		tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - 2 * heightTab);
	}
	else { //hien thi tab lich su doi thuong
		tab_user->setVisible(false);
		tab_email->setVisible(false);
		tab_ls_doithuong->setVisible(true);

		LoadingManager::getInstance()->showLoading();
		tab_ls_doithuong->resetMoneyLog();
		NetworkManager::getInstance()->getLookupMoneyHistoryMessage(0, 10, 5);

		tab->setTexture("user_info/bg_popup/tab_clicked.png");
		tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - 3 * heightTab);
	}
}

NodeHoSo* PopupUserInfo::getNodeHoSo(){
	return this->tab_user;
}

NodeHopThu* PopupUserInfo::getNodeHopThu(){
	return this->tab_email;
}

NodeLichSuDoiThuong* PopupUserInfo::getNodeLsDoiThuong(){
	return this->tab_ls_doithuong;
}

void PopupUserInfo::setTargetUserId(int targetUserId){
	this->targetUserId = targetUserId;
}

void PopupUserInfo::addTab(){
 //   float height = backgroundPopup->getHeight();
 //   
 //   for(int i=0;i<3;i++){
 //       auto tabSprite = MSprite::create("user_info/sprite_tab1.png");
 //       tabSprite->setPosition(Vec2(backgroundPopup->getPosition().x + (2+tabSprite->getWidth())*i,
 //                                   backgroundPopup->getPosition().y + height-10));
 //       m_popupLayer->addChild(tabSprite , -1);
 //   }
 //   
 //   tab = MSprite::create("user_info/sprite_tab_selected1.png");  //sprite_tab_selected
	//tab->setPosition(Vec2(backgroundPopup->getPosition().x, backgroundPopup->getPosition().y + height - 10));
	//m_popupLayer->addChild(tab);
 //   
 //   vector<std::string> nameTabButton = {"Hồ Sơ","Hòm Thư","Lịch Sử Đổi Thưởng"};
 //   vector<int> tagTabButton = {TAG_TABLE_BTN_HOSO,TAG_TABLE_BTN_HOMTHU,TAG_TABLE_BTN_LICHSUDOITHUONG};
 //   
 //   for(int i=0;i<3;i++){
 //       auto tabButton = MButton::create("user_info/sprite_tab_null.png",nameTabButton[i],tab->getWidth()/3,tagTabButton[i]);
	//	tabButton->setPosition(Vec2(backgroundPopup->getPosition().x + (2 + tabButton->getWidth())*i, 
	//		backgroundPopup->getPosition().y + height - 10));
 //       tabButton->addTouchEventListener(CC_CALLBACK_2(PopupUserInfo::tabCallBack, this));
	//	m_popupLayer->addChild(tabButton);
 //   }

	auto spriteTab = MSprite::create("user_info/bg_popup/tab_click.png");
	heightTab = spriteTab->getHeight();
	float posX = contentPopupLeft->getPosition().x + contentPopupLeft->getWidth() / 2 - spriteTab->getWidth() / 2;

	string rs_tab;
	for (int i = 0; i < 3; i++){
		if (i == 0){
			rs_tab = "user_info/bg_popup/tab_click_round.png";
		}
		else {
			rs_tab = "user_info/bg_popup/tab_click.png";
		}
		auto tabSprite = MSprite::create(rs_tab);
		tabSprite->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - (heightTab)*(i + 1)));
		backgroundPopup->addChild(tabSprite);
	}

	tab = MSprite::create("user_info/bg_popup/tab_clicked_round.png");
	tab->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - heightTab));
	backgroundPopup->addChild(tab);

	vector<std::string> nameTabButton = { "Hồ sơ", "Hòm thư", "Lịch Sử Đổi Thưởng" };
	vector<int> tagTabButton = { TAG_TABLE_BTN_HOSO, TAG_TABLE_BTN_HOMTHU, TAG_TABLE_BTN_LICHSUDOITHUONG };

	for (int i = 0; i < 3; i++){ ///sprite tab null
		auto tabButton = MButton::create("user_info/bg_popup/tab_click_null.png", nameTabButton[i], tab->getWidth() / 3, tagTabButton[i]);
		tabButton->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - (heightTab)*(i + 1)));
		tabButton->addTouchEventListener(CC_CALLBACK_2(PopupUserInfo::tabCallBack, this));
		backgroundPopup->addChild(tabButton);
	}
}

void PopupUserInfo::tabCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
        case TAG_TABLE_BTN_HOSO:
            tab_user->setVisible(true);
            tab_email->setVisible(false);
            tab_ls_doithuong->setVisible(false);

			tab->setTexture("user_info/bg_popup/tab_clicked_round.png");
			tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - heightTab);

			targetUserId = Common::getInstance()->getUserId();

			if (targetUserId > 0){
				NetworkManager::getInstance()->getViewUserInfoFromServer(targetUserId);
			}
            break;
        case TAG_TABLE_BTN_HOMTHU:
            tab_user->setVisible(false);
            tab_email->setVisible(true);
            tab_ls_doithuong->setVisible(false);

			tab->setTexture("user_info/bg_popup/tab_clicked.png");
			tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - 2 * heightTab);

			LoadingManager::getInstance()->showLoading();
			tab_email->resetMail();
			NetworkManager::getInstance()->getFilterMailFromServer(0, 10, -1);

            break;
        case TAG_TABLE_BTN_LICHSUDOITHUONG:
            tab_user->setVisible(false);
            tab_email->setVisible(false);
            tab_ls_doithuong->setVisible(true);
            
			tab->setTexture("user_info/bg_popup/tab_clicked.png");
			tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - 3 * heightTab);

			LoadingManager::getInstance()->showLoading();

			tab_ls_doithuong->resetMoneyLog();
			NetworkManager::getInstance()->getLookupMoneyHistoryMessage(0, 10, 5);
            break;
        default:
            break;
                
        }
    }
}

void PopupUserInfo::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
        case TAG_CLOSE:
            this->disappear();
            break;
        default:
            break;
                
        }
    }
}

#pragma mark - EditBoxDelegate

void PopupUserInfo::editBoxEditingDidBegin(ui::EditBox *editBox) {
    CCLOG("%s","edit begin!");
}

void PopupUserInfo::editBoxEditingDidEnd(ui::EditBox *editBox) {
    
    switch (editBox->getTag()) {
        default:
            break;
    }
}

void PopupUserInfo::editBoxTextChanged(ui::EditBox *editBox, const std::string& text) {
    CCLOG("%s","edit changed!");
}

void PopupUserInfo::editBoxReturn(ui::EditBox *editBox) {
    
}

void PopupUserInfo::onExit() {
    Popup::onExit();
}
