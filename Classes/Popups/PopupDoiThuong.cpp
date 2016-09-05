#include "PopupDoiThuong.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/TLMNConfig.hpp"
#include "UI/MButton.hpp"
#include "Utils/Common.h"
#include "UI/MEditBox.hpp"

using namespace cocos2d;

#define PADDING 25

bool PopupDoiThuong::init() {
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

	auto title = Label::createWithTTF("ĐỔI THƯỞNG", "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
	title->setColor(Color3B::BLACK);
	title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
		bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
	bg_title_popup->addChild(title);
    
	auto sprite_arrow_right = MSprite::create("common_popup/icon_arrow_right.png");

	contentPopupLeft = MSprite::create("common_popup/content_popup_left.png");
	auto contentPopupRight = MSprite::create("common_popup/content_popup_right.png");

	padding_left = (backgroundPopup->getWidth() - (sprite_arrow_right->getWidth() + contentPopupLeft->getWidth() 
		+ contentPopupRight->getWidth())) / 2;

	contentPopupLeft->setPosition(Vec2(padding_left, backgroundPopup->getHeight() / 2 - contentPopupLeft->getHeight() / 2));

	backgroundPopup->addChild(contentPopupLeft);
   
	nodeDoiTheCao = NodeDoiTheCao::create();
	nodeDoiTheCao->setPosition(Vec2(padding_left + contentPopupLeft->getWidth() + sprite_arrow_right->getWidth()
		, backgroundPopup->getHeight() / 2 - nodeDoiTheCao->getHeight() / 2));
	backgroundPopup->addChild(nodeDoiTheCao);

	addTab();

	//test();

    //btn close
	auto exit = MButton::create(IMAGE_CLOSE, TAG_POPUP_DOITHUONG_EXIT);
	exit->setPosition(Vec2(backgroundPopup->getWidth() - exit->getWidth() / 2,
		backgroundPopup->getHeight() - exit->getHeight() / 2));
	exit->addTouchEventListener(CC_CALLBACK_2(PopupDoiThuong::menuPopupCallBack, this));
	backgroundPopup->addChild(exit);

	this->scheduleUpdate();

	NetworkManager::getInstance()->getAssetConfigFromServer(AssetConfig::THE_CAO);

    return true;
}

void PopupDoiThuong::test(){
	vector<BINAsset> lstAsset;

	BINAsset a1 = BINAsset();
	a1.set_parvalue(10000);
	BINAsset a2 = BINAsset();
	a2.set_parvalue(20000);
	BINAsset a3 = BINAsset();
	a3.set_parvalue(50000);
	BINAsset a4 = BINAsset();
	a4.set_parvalue(200000);
	BINAsset a5 = BINAsset();
	a5.set_parvalue(500000);
	BINAsset a6 = BINAsset();
	a6.set_parvalue(100000);

	a1.set_provider("VTT");
	a2.set_provider("VTT");
	a3.set_provider("VTT");
	a4.set_provider("VTT");
	a5.set_provider("VTT");
	a6.set_provider("VTT");

	lstAsset.push_back(a1);
	lstAsset.push_back(a2);
	lstAsset.push_back(a3);
	lstAsset.push_back(a6);
	lstAsset.push_back(a4);
	lstAsset.push_back(a5);

	nodeDoiTheCao->setAssets(lstAsset);
	nodeDoiTheCao->showTheCao();
}

void PopupDoiThuong::update(float){
	handlerAssetConfigResponse();
	handlerExchangeAssetResponse();
}

void PopupDoiThuong::handlerExchangeAssetResponse(){
	BINExchangeAssetResponse* response = (BINExchangeAssetResponse*)Common
		::getInstance()->checkEvent(NetworkManager::EXCHANGE_ASSET);
	if (response != 0){
		CCLOG("exchange asset: %s", response->DebugString().c_str());
		if (response->has_message()){
			showGame->showToast(response->message().c_str(), 2);
		}
	}
}

void PopupDoiThuong::handlerAssetConfigResponse(){
	BINAssetConfigResponse* response = (BINAssetConfigResponse*)Common
		::getInstance()->checkEvent(NetworkManager::ASSET_CONFIG);
	if (response != 0){
		CCLOG("asset config: %s", response->DebugString().c_str());
		if (response->responsecode() && response->assets_size() > 0){
			vector<BINAsset> lstAsset;
			for (int i = 0; i < response->assets_size(); i++){
				lstAsset.push_back(response->assets(i));
			}

			nodeDoiTheCao->setAssets(lstAsset);
			nodeDoiTheCao->showTheCao();
		}
		else {
			showGame->showToast(response->message().c_str() , 2);
		}
	}
}

void PopupDoiThuong::addTab(){
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
    
    vector<std::string> nameTabButton = {"Đổi thẻ cào","Đổi vật phẩm"};
	vector<int> tagTabButton = { 1, 2 };
    
    for(int i=0;i<2;i++){ ///sprite tab null
        auto tabButton = MButton::create("common_popup/tab_click_null.png",nameTabButton[i],tab->getWidth()/3,tagTabButton[i]);
		tabButton->setPosition(Vec2(posX, contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - (heightTab)*(i + 1)));
        tabButton->addTouchEventListener(CC_CALLBACK_2(PopupDoiThuong::tabCallBack, this));
        backgroundPopup->addChild(tabButton);
    }
}

void PopupDoiThuong::setContext(ShowGame* showGame){
	this->showGame = showGame;
}

void PopupDoiThuong::tabCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
		case 1:
			{
				tab->setTexture("common_popup/tab_clicked_round.png");
				tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - heightTab);
				NetworkManager::getInstance()->getAssetConfigFromServer(AssetConfig::THE_CAO);
			}
            break;
		case 2:
			{
				tab->setTexture("common_popup/tab_clicked.png");
				tab->setPositionY(contentPopupLeft->getPosition().y + contentPopupLeft->getHeight() - 2 * heightTab);
				showGame->showToast(TEXT_NOTIFY_FUNCTION_FUTURE, 2);
				//NetworkManager::getInstance()->getAssetConfigFromServer(AssetConfig::HIEN_VAT);
			}
			break;
        default:
            break;
        }
    }
}

void PopupDoiThuong::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
		case TAG_POPUP_DOITHUONG_EXIT:
            this->disappear();
            break;
        default:
            break;  
        }
    }
}

void PopupDoiThuong::onExit() {
    Popup::onExit();
}
