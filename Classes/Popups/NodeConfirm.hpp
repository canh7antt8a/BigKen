//  NodeConfirm.hpp

#ifndef NodeConfirm_hpp
#define NodeConfirm_hpp

#include "UI/MEditbox.hpp"
#include "cocos2d.h"
#include "UI/MLabel.hpp"
#include "Objects/OnEvenListener.hpp"

#include "UI/MButton.hpp"
#include "Utils/TLMNConfig.hpp"
//#include "Utils/NetworkManager.h"
#include "UI/MSprite.hpp"

using namespace cocos2d;

template <typename T>
class NodeConfirm : public Node {
public:
    CREATE_FUNC(NodeConfirm);
	static NodeConfirm *create(OnEvenListener<T> *onEvent, std::string titleDlg, std::string messageDlg);
    bool init();
	void setTitleDlg(std::string titleDlg);
	void setMessageDlg(std::string messageDlg);
	void showDlg();
    virtual void onExit();
	void setEvent(OnEvenListener<T> *onEvent);
	void menuPopupCallBack(Ref *sender, ui::Widget::TouchEventType type);

	void setSender(T sender);
	void setEventOk(int event_ok);
private:
	Label* title;
	MLabel* labelMessage;
	OnEvenListener<T> *_onEvent;
	T sender;
	int event_ok;
};

#define TAG_NODE_CONFIRM 9999

template <class T>
NodeConfirm<T> *NodeConfirm<T>::create(OnEvenListener<T> *onEvent, std::string titleDlg, std::string messageDlg){
	NodeConfirm<T>* popup = NodeConfirm<T>::create();
	popup->setAnchorPoint(Point::ZERO);
	popup->setTitleDlg(titleDlg);
	popup->setMessageDlg(messageDlg);
	popup->setEvent(onEvent);
	return popup;
}

template <class T>
void NodeConfirm<T>::setEvent(OnEvenListener<T> *onEvent){
	this->_onEvent = onEvent;
	event_ok = this->_onEvent->EVENT_CONFIRM_OK;
}

template <class T>
void NodeConfirm<T>::setEventOk(int event_ok){
	this->event_ok = event_ok;
}

template <class T>
bool NodeConfirm<T>::init() {
	if (!Node::init())
		return false;

	this->setTag(TAG_NODE_CONFIRM);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(Vec2(origin.x, origin.y));

	auto background = LayerColor::create(Color4B(0, 0, 0, 160));
	background->setContentSize(visibleSize);
	background->setPosition(Vec2(0, 0));
	background->setOpacity(200);
	this->addChild(background);

	auto backgroundPopup = MSprite::create("popup_xacnhan/bg_popup.png");
	backgroundPopup->setAnchorPoint(Point::ANCHOR_MIDDLE);
	backgroundPopup->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backgroundPopup);

	auto contenPopup = MSprite::create("popup_xacnhan/content_popup.png");
	contenPopup->setAnchorPoint(Point::ANCHOR_MIDDLE);
	contenPopup->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(contenPopup);

	auto bg_title_popup = MSprite::create(RS_TITLE_POPUP);
	bg_title_popup->setPosition(Vec2(backgroundPopup->getWidth() / 2 - bg_title_popup->getWidth() / 2,
		backgroundPopup->getHeight() - bg_title_popup->getHeight() / 2));
	backgroundPopup->addChild(bg_title_popup);

	title = Label::createWithTTF("", "fonts/font_title.otf", bg_title_popup->getHeight() / 2);
	title->setColor(Color3B::BLACK); //MLabel::create("", bg_title_popup->getHeight() / 2, Color3B::BLACK);
	title->setPosition(Vec2(bg_title_popup->getWidth() / 2 - title->getWidth() / 2,
		bg_title_popup->getHeight() / 2 - title->getHeight() / 2));
	bg_title_popup->addChild(title);

	auto ok = MButton::create("btn_danhbai.png", "Đồng ý", 30, TAG_POPUP_CONFIRM_OK);
	ok->setPosition(Vec2(contenPopup->getWidth() / 2 + ok->getWidth()*0.2f,
		contenPopup->getHeight()*0.25f - ok->getHeight() / 2));
	ok->addTouchEventListener(CC_CALLBACK_2(NodeConfirm::menuPopupCallBack, this));
	contenPopup->addChild(ok);

	auto exit = MButton::create("btn_boluot.png", "Hủy", 30, TAG_POPUP_CONFIRM_NOK);
	exit->setPosition(Vec2(contenPopup->getWidth() / 2 - exit->getWidth()*1.2f,
		contenPopup->getHeight()*0.25f - exit->getHeight() / 2));
	exit->addTouchEventListener(CC_CALLBACK_2(NodeConfirm::menuPopupCallBack, this));
	contenPopup->addChild(exit);

	auto close = MButton::create(IMAGE_CLOSE, TAG_POPUP_NODE_CONFIRM_EXIT);
	close->setPosition(Vec2(backgroundPopup->getWidth() - close->getWidth() / 2,
		backgroundPopup->getHeight() - close->getHeight() / 2));
	close->addTouchEventListener(CC_CALLBACK_2(NodeConfirm::menuPopupCallBack, this));
	backgroundPopup->addChild(close);

	labelMessage = MLabel::create("", 30);
	labelMessage->setHorizontalAlignment(TextHAlignment::CENTER);
	labelMessage->setVerticalAlignment(TextVAlignment::CENTER);
	labelMessage->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	//labelMessage->setContentSize(Size(contenPopup->getWidth() - 2 * 20, ok->getHeight()));
	labelMessage->setWidth(contenPopup->getWidth() - 2 * 20);
	labelMessage->setHeight(contenPopup->getHeight() / 2 - 20);
	labelMessage->setLineBreakWithoutSpace(true);
	labelMessage->enableWrap(true);
	labelMessage->setPosition(Vec2(contenPopup->getWidth() / 2 - labelMessage->getWidth() / 2,
		contenPopup->getHeight() / 2
		));
	contenPopup->addChild(labelMessage);

	return true;
}

template <class T>
void NodeConfirm<T>::setTitleDlg(std::string titleDlg){
	title->setString(titleDlg);
}

template <class T>
void NodeConfirm<T>::setMessageDlg(std::string messageDlg){
	labelMessage->setString(messageDlg);
}

template <class T>
void NodeConfirm<T>::setSender(T sender){
	this->sender = sender;
}

template <class T>
void NodeConfirm<T>::showDlg(){
	_eventDispatcher->pauseEventListenersForTarget(Director::getInstance()->getRunningScene(), true);
	Director::getInstance()->getRunningScene()->addChild(this, 2);
}

template <class T>
void NodeConfirm<T>::menuPopupCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type){
	if (type == ui::Widget::TouchEventType::ENDED) {
		MButton *button = (MButton*)sender;
		int tag = button->getTag();
		switch (tag) {
		case TAG_POPUP_CONFIRM_OK:
		{
			CCLOG("TAG_POPUP_CONFIRM_OK");
			_eventDispatcher->resumeEventListenersForTarget(Director::getInstance()->getRunningScene(), true);
			_onEvent->onEvent(event_ok, this->sender);
			this->removeFromParentAndCleanup(true);
		}
			break;
		case TAG_POPUP_CONFIRM_NOK:
			CCLOG("TAG_POPUP_CONFIRM_NOK");
			_eventDispatcher->resumeEventListenersForTarget(Director::getInstance()->getRunningScene(), true);
			_onEvent->onEvent(this->_onEvent->EVENT_CANCEL_CONFIRM, this->sender);
			this->removeFromParentAndCleanup(true);
			break;
		case TAG_POPUP_NODE_CONFIRM_EXIT:
			_eventDispatcher->resumeEventListenersForTarget(Director::getInstance()->getRunningScene(), true);
			this->removeFromParentAndCleanup(true);
		default:
			break;
		}
	}
}

template <class T>
void NodeConfirm<T>::onExit() {
	Node::onExit();
}

#endif /* NodeConfirm_hpp */
