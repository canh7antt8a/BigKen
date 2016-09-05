#include "PopupHotLine.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "Utils/TLMNConfig.hpp"
#include "UI/MButton.hpp"
#include "Utils/Common.h"

using namespace cocos2d;

#define PADDING 25

bool PopupHotLine::init() {
    if (!Popup::init())
        return false;
    
    backgroundPopup = MSprite::create("popup_hotline/bg_popup.png");
    backgroundPopup->setPosition(Vec2(visibleSize.width/2 - backgroundPopup->getWidth()/2,
                                      visibleSize.height/2 - backgroundPopup->getHeight()/2));
    m_popupLayer->addChild(backgroundPopup);

	auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
	bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
		backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
	backgroundPopup->addChild(bg_title_popup);

	backgroundContentSize = backgroundPopup->getContentSize();

	auto title = Label::createWithTTF("HOTLINE", "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
	title->setColor(Color3B::BLACK);
	title->setPosition(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
		bg_title_popup->getHeight() / 2 - title->getHeight() / 2);
	bg_title_popup->addChild(title);

	auto girl_hotline = MSprite::create("popup_hotline/girl_hotline.png");
	girl_hotline->setPosition(Vec2(girl_hotline->getWidth() / 5, backgroundPopup->getHeight() / 2 - girl_hotline->getHeight() / 2));
	backgroundPopup->addChild(girl_hotline);

	float width_content = backgroundPopup->getWidth() - (6 * girl_hotline->getWidth() / 5);

	auto btn_call1 = MButton::create("popup_hotline/btn_call.png", "01649709583", 30, TAG_POPUP_HOTLINE_CALL_SUPPORT1);
	btn_call1->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	btn_call1->setPosition(Vec2(backgroundPopup->getWidth() - width_content / 2 - 5, backgroundPopup->getHeight() / 2));
	btn_call1->addTouchEventListener(CC_CALLBACK_2(PopupHotLine::menuPopupCallBack, this));
	backgroundPopup->addChild(btn_call1);

	auto btn_call2 = MButton::create("popup_hotline/btn_call.png", "0985782776", 30, TAG_POPUP_HOTLINE_CALL_SUPPORT2);
	btn_call2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	btn_call2->setPosition(Vec2(backgroundPopup->getWidth() - width_content / 2 + 5, backgroundPopup->getHeight() / 2));
	btn_call2->addTouchEventListener(CC_CALLBACK_2(PopupHotLine::menuPopupCallBack, this));
	backgroundPopup->addChild(btn_call2);

	auto lb_notify = MLabel::create("Hỗ trợ chăm sóc khách hàng qua điện thoại viên", bg_title_popup->getHeight() / 3);
	lb_notify->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_notify->setPosition(Vec2(backgroundPopup->getWidth() - width_content / 2, 3.0f * backgroundPopup->getHeight() / 4));
	backgroundPopup->addChild(lb_notify);

	auto lb_facebook = MSprite::create("popup_hotline/bg_link_bigken.png");
	lb_facebook->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_facebook->setPosition(Vec2(backgroundPopup->getWidth() - width_content / 2, backgroundPopup->getHeight() / 4));
	backgroundPopup->addChild(lb_facebook);

	auto lb_info = MLabel::create("facebook.com/bigken", bg_title_popup->getHeight() / 3);
	lb_info->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lb_info->setPosition(Vec2(lb_facebook->getWidth() / 2, lb_facebook->getHeight() / 2));
	lb_facebook->addChild(lb_info);

    //btn close
	auto exit = MButton::create(IMAGE_CLOSE, TAG_POPUP_HOTLINE_EXIT);
	exit->setPosition(Vec2(backgroundPopup->getWidth() - exit->getWidth() / 2,
		backgroundPopup->getHeight() - exit->getHeight() / 2));
	exit->addTouchEventListener(CC_CALLBACK_2(PopupHotLine::menuPopupCallBack, this));
	backgroundPopup->addChild(exit);

	this->scheduleUpdate();

    return true;
}

void PopupHotLine::update(float){
	
}

void PopupHotLine::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
		case TAG_POPUP_HOTLINE_EXIT:
            this->disappear();
            break;
		case TAG_POPUP_HOTLINE_CALL_SUPPORT1:
			Common::getInstance()->callPhone("01649709583");
			break;
		case TAG_POPUP_HOTLINE_CALL_SUPPORT2:
			Common::getInstance()->callPhone("0985782776");
			break;
        default:
            break;
        }
    }
}

void PopupHotLine::onExit() {
    Popup::onExit();
}
