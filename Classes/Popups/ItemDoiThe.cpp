#include "ItemDoiThe.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/Common.h"
#include "Utils/Image.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/NetworkManager.h"
#include "Popups/NodeConfirm.hpp"

#define NUMBER_ITEM_ROW 3

ItemDoiThe::ItemDoiThe(){}

ItemDoiThe::~ItemDoiThe(){}

ItemDoiThe* ItemDoiThe::create(BINAsset asset, float width, float height){
    ItemDoiThe *cell = new ItemDoiThe();
    if (cell && cell->init()){
        cell->autorelease();
    } else{
        CC_SAFE_DELETE(cell);
    }
	
	cell->setContentSize(Size(width / NUMBER_ITEM_ROW, height / 2));

	auto background = MSprite::create(StringUtils::format("mua_the/%d.png", asset.parvalue()));
	background->setAnchorPoint(Point::ANCHOR_MIDDLE);

	auto sprite_xu = MSprite::create("sprite_hienthidoixu.png");
	sprite_xu->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);

	background->setPosition(Vec2(cell->getContentSize().width / 2, cell->getContentSize().height / 2
		+ 3 * sprite_xu->getHeight() / 4)); //
	cell->addChild(background);

	sprite_xu->setScaleX((background->getWidth() * 0.75f) / (sprite_xu->getWidth()));
	sprite_xu->setPosition(Vec2(cell->getContentSize().width / 2, background->getPosition().y - background->getHeight() / 2 - sprite_xu->getHeight() / 2));
	cell->addChild(sprite_xu);

	auto lb_value_cash = MLabel::create(Common::getInstance()->convertIntToMoneyView100k(asset.cashvalue()), sprite_xu->getHeight() / 2);
	lb_value_cash->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_value_cash->setPosition(Vec2(sprite_xu->getPosition().x, sprite_xu->getPosition().y - sprite_xu->getHeight() / 2));
	cell->addChild(lb_value_cash);

	cell->addEvents(asset);
    
    return cell;
}

void ItemDoiThe::onEvent(int enventType, BINAsset sender){
	if (enventType == OnEvenListener::EVENT_CONFIRM_OK){
		NetworkManager::getInstance()->getExchangeAssetFromServer(sender.assetid(), 1);
	}
}

void ItemDoiThe::addEvents(BINAsset asset){
	string message = "Bạn có muốn dùng " + Common::getInstance()->numberFormatWithCommas(asset.cashvalue()) + " Xu đổi 1 thẻ ";

	if (asset.provider() == "VTT"){
		message += " Viettel ";
	}
	else if (asset.provider() == "VNP"){
		message += " Vinaphone ";
	}
	else if (asset.provider() == "VMS"){
		message += " Mobiphone ";
	}
	message += Common::getInstance()->numberFormatWithCommas(asset.parvalue());

    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        // get the location of the touch on screen
        auto location = touch->getLocation();
        // get the location of the touch relative to your button
        auto nodeSpaceLocation = this->getParent()->convertToNodeSpace(location);
        // check if touch is inside node's bounding box
        if (rect.containsPoint(nodeSpaceLocation)) {
            // node has been touched; add code here
            return true;
        }
        
        return false;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		//CCLOG("touch roomindex : %lld", asset.parvalue());
		
		NodeConfirm<BINAsset> * nodeConfirm = NodeConfirm<BINAsset>::create(this, TITLE_POPUP_CONFIRM, message);
		nodeConfirm->setSender(asset);
		nodeConfirm->showDlg();
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

float ItemDoiThe::getWidth(){
    return this->getContentSize().width;
}

float ItemDoiThe::getHeight(){
    return this->getContentSize().height;
}

bool ItemDoiThe::init() {
    if (!Node::init())
        return false;

    return true;
}

void ItemDoiThe::onExit() {
    Node::onExit();
}
