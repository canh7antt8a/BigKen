//
//  PopupChat.cpp
//
//
//

#include "Utils/Common.h"
#include "Utils/NetworkManager.h"
#include "PopupChat.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Utils/Image.h"
#include "Utils/Utility.h"
#include "protobufObject/exit_room.pb.h"

bool PopupChat::init() {
    if (!Popup::init())
        return false;
    this->setAnchorPoint(Point::ZERO);
    
    auto button = MSprite::create(BTN_MESSAGE);
    
    backgroundPopup = MSprite::create(IMAGE_POPUP_CHAT);
    // vi tri xuat hien
    backgroundPopup->setPosition(Vec2(visibleSize.width - backgroundPopup->getWidth() - 20,button->getHeight() + 40));
    backgroundPopup->setOpacity(200);
    
    m_popupLayer->setPosition(Vec2(visibleSize.width + backgroundPopup->getWidth() + 20,0));
    
    m_popupLayer->addChild(backgroundPopup);
    
    btn_send_message = MButton::create(IMAGE_SEND_MESSAGE, SEND_CHAT, 25, TAG_SEND_MESSAGE);
    btn_send_message->setPosition(Vec2(visibleSize.width - btn_send_message->getWidth() - 40,
                                       backgroundPopup->getPosition().y + 20));
    m_popupLayer->addChild(btn_send_message);
    btn_send_message->addTouchEventListener(CC_CALLBACK_2(PopupChat::menuPopupCallBack, this));
    
    Size size_edit_message = Size(backgroundPopup->getWidth() - btn_send_message->getWidth() - 60,
                                  btn_send_message->getContentSize().height);
    edit_message = MEditBox::create(size_edit_message, IMAGE_SOANTINNHAN, btn_send_message->getHeight() / 3);
    edit_message->setPosition(Vec2(visibleSize.width - backgroundPopup->getWidth(),btn_send_message->getPosition().y));
    edit_message->setPlaceHolder(CONTENT_MESSAGE_CHAT);
    edit_message->setTag(TAG_EDITBOX_MESSAGE);
    edit_message->setDelegate(this);
    m_popupLayer->addChild(edit_message);
    
    //template message chat
    //IMAGE_MESSAGE_TEMP
    std::vector<std::string> text_chat = {"Chào cả nhà ahihi","Bài xấu quá","Bài xấu vl",
        "Bài đẹp","Đánh nhanh lên","Chào nhé ! Mình out"};
    btn_txt_temp1 = MButton::create(imageMessageTemp(text_chat[0]), text_chat[0], 25, TAG_MSG_CHAT_TEMP1);
    btn_txt_temp1->setTitleFontSize(btn_txt_temp1->getHeight() / 2);
    btn_txt_temp1->setPosition(Vec2(edit_message->getPosition().x,
                                    btn_send_message->getPosition().y + btn_send_message->getHeight() + 20));
    btn_txt_temp1->addTouchEventListener(CC_CALLBACK_2(PopupChat::buttonTextCallBack, this));
    
    btn_txt_temp3 = MButton::create(imageMessageTemp(text_chat[2]), text_chat[2], 25, TAG_MSG_CHAT_TEMP3);
    btn_txt_temp3->setTitleFontSize(btn_txt_temp3->getHeight() / 2);
    btn_txt_temp3->setPosition(Vec2(btn_send_message->getPosition().x+btn_send_message->getWidth()
                                    - btn_txt_temp3->getWidth(),
                                    btn_txt_temp1->getPosition().y));
    btn_txt_temp3->addTouchEventListener(CC_CALLBACK_2(PopupChat::buttonTextCallBack, this));
    
    btn_txt_temp2 = MButton::create(imageMessageTemp(text_chat[1]), text_chat[1], 25, TAG_MSG_CHAT_TEMP2);
    btn_txt_temp2->setTitleFontSize(btn_txt_temp2->getHeight() / 2);
    btn_txt_temp2->setPosition(Vec2(btn_txt_temp1->getPosition().x/2+btn_txt_temp1->getWidth()/2
                                    + btn_txt_temp3->getPosition().x/2-btn_txt_temp2->getWidth()/2,
                                    btn_txt_temp1->getPosition().y));
    btn_txt_temp2->addTouchEventListener(CC_CALLBACK_2(PopupChat::buttonTextCallBack, this));
    
    btn_txt_temp4 = MButton::create(imageMessageTemp(text_chat[3]), text_chat[3], 25, TAG_MSG_CHAT_TEMP6);
    btn_txt_temp4->setTitleFontSize(btn_txt_temp4->getHeight() / 2);
    btn_txt_temp4->setPosition(Vec2(btn_txt_temp1->getPosition().x,
                                    btn_txt_temp3->getPosition().y + btn_txt_temp3->getHeight() + 20));
    btn_txt_temp4->addTouchEventListener(CC_CALLBACK_2(PopupChat::buttonTextCallBack, this));
    
    btn_txt_temp6 = MButton::create(imageMessageTemp(text_chat[5]), text_chat[5], 25, TAG_MSG_CHAT_TEMP4);
    btn_txt_temp6->setTitleFontSize(btn_txt_temp6->getHeight() / 2);
    btn_txt_temp6->setPosition(Vec2(btn_send_message->getPosition().x+btn_send_message->getWidth()
                                    - btn_txt_temp6->getWidth(),
                                    btn_txt_temp4->getPosition().y));
    btn_txt_temp6->addTouchEventListener(CC_CALLBACK_2(PopupChat::buttonTextCallBack, this));
    
    btn_txt_temp5 = MButton::create(imageMessageTemp(text_chat[4]), text_chat[4], 25, TAG_MSG_CHAT_TEMP5);
    btn_txt_temp5->setTitleFontSize(btn_txt_temp5->getHeight() / 2);
    btn_txt_temp5->setPosition(Vec2(btn_txt_temp4->getPosition().x/2+btn_txt_temp4->getWidth()/2
                                    + btn_txt_temp6->getPosition().x/2-btn_txt_temp5->getWidth()/2
                                    , btn_txt_temp4->getPosition().y));
    btn_txt_temp5->addTouchEventListener(CC_CALLBACK_2(PopupChat::buttonTextCallBack, this));
    
    //end template message chat
    
    //close popup
    auto btn_close = MButton::create(IMAGE_CLOSE, TAG_CLOSE);
    btn_close->setAnchorPoint(Point::ANCHOR_MIDDLE);
    btn_close->setPosition(Vec2(backgroundPopup->getPosition().x + backgroundPopup->getWidth() - 12,
                                backgroundPopup->getPosition().y + backgroundPopup->getHeight()));
    btn_close->addTouchEventListener(CC_CALLBACK_2(PopupChat::menuPopupCallBack, this));
    
    m_popupLayer->addChild(btn_txt_temp1);
    m_popupLayer->addChild(btn_txt_temp2);
    m_popupLayer->addChild(btn_txt_temp3);
    m_popupLayer->addChild(btn_txt_temp4);
    m_popupLayer->addChild(btn_txt_temp5);
    m_popupLayer->addChild(btn_txt_temp6);
    
    m_popupLayer->addChild(btn_close);
    CCLOG("init PopupChat !!!");
    
    return true;
}

void PopupChat::buttonTextCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED) {
        MButton *button = (MButton*)sender;
        setMessage(button->getTitleText());
    }
}

void PopupChat::menuPopupCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED) {
        MButton *button = (MButton*)sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_SEND_MESSAGE:
            {
                std::string edit_text_message = edit_message->getText();
                if (!edit_text_message.empty()){
                    NetworkManager::getInstance()->sendMessageToServer(scope, edit_message->getText());
                    edit_message->setText("");
                    this->disappear();
                }
                break;
            }
            case TAG_CLOSE:
                this->disappear();
                break;
            default:
                break;
        }
    }
}

std::string PopupChat::imageMessageTemp(std::string text){
    CCLOG("size: %lu",text.length());
    if(text.length() >=20){
        return IMAGE_MESSAGE_TEMP_4;
    }else if(text.length() >=15 && text.length() < 20){
        return IMAGE_MESSAGE_TEMP_3;
    }else{
        return IMAGE_MESSAGE_TEMP_2;
    }
}

#pragma mark - EditBoxDelegate

void PopupChat::editBoxEditingDidBegin(ui::EditBox *editBox) {
    CCLOG("%s","edit begin!");
}

void PopupChat::editBoxEditingDidEnd(ui::EditBox *editBox) {
    
}

void PopupChat::editBoxTextChanged(ui::EditBox *editBox, const std::string& text) {
    CCLOG("%s","edit changed!");
}

void PopupChat::editBoxReturn(ui::EditBox *editBox) {
    CCLOG("%s","edit return!");
}

void PopupChat::setMessage(std::string message){
    edit_message->setText(message.c_str());
}

PopupChat* PopupChat::createPopup(int scope) {
    auto popup = PopupChat::create();
    popup->setScope(scope);
    return popup;
}

void PopupChat::disappear() {
    
    auto callDisappear = CallFunc::create([this](){
        disablePopup = true;
        this->removeFromParentAndCleanup(true);
    });
    m_popupLayer->runAction(Sequence::create(MoveTo::create(0.15f,
                                                            Vec2(visibleSize.width+10,0)),callDisappear,NULL));
}

void PopupChat::appear() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto sprite = event->getCurrentTarget();
        Point pt = touch->getLocation();
        Rect recTemp = sprite->getBoundingBox();
        if (!recTemp.containsPoint(pt)) {
            this->disappear();
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, backgroundPopup);
    
    auto callAppear = CallFunc::create([this](){
        disablePopup = false;
    });
    
    m_popupLayer->runAction(Sequence::create(MoveTo::create(0.15f,Vec2(0,0)), callAppear, NULL));
    
}

void PopupChat::onExit() {
    Popup::onExit();
}
void PopupChat::setScope(int scope) {
    this->scope = scope;
}
int PopupChat::getScope() {
    return this->scope;
}

