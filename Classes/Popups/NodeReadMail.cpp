#include "NodeReadMail.hpp"
#include "UI/MSprite.hpp"
#include "Popups/NodeConfirm.hpp"
#include "Utils/Common.h"

using namespace std;

NodeReadMail* NodeReadMail::createReadMail(Mail mail, NodeHopThu* node){
	NodeReadMail* readMail = NodeReadMail::create();

	auto background = MSprite::create(MAIL_BG_DOC_MAIL);
	background->setPosition(Vec2(0, 0));
	readMail->setContentSize(background->getContentSize());
	readMail->addChild(background);

	std::string rs_mail = MAIL_ICON_MAIL;
	//attachment
	std::string rs_item_attachment;

	if (mail.getAttachItemId() > 0){  //neu co attachment
		rs_mail = "mail/sprite_vatpham.png";
		rs_item_attachment = StringUtils::format("mail/item_vatpham%ld.png", mail.getAttachItemId());
	}

	auto btn_mail = MSprite::create(rs_mail);
	float padding = btn_mail->getWidth() / 4;
	btn_mail->setPosition(Vec2(padding, background->getHeight() - btn_mail->getHeight() - padding));
	readMail->addChild(btn_mail);

	//content
	auto sprite_content = MSprite::create(MAIL_SPRITE_CONTENT);
	/*sprite_content->setTag(TAG_MAIL_CONTENT);
	sprite_content->setPosition(Vec2(btn_mail->getPosition().x + btn_mail->getWidth() + padding,
		btn_mail->getPosition().y - (sprite_content->getHeight() - btn_mail->getHeight()) / 2));
	readMail->addChild(sprite_content);*/

	auto labelTitleContent = MLabel::create(mail.getTitle(), sprite_content->getHeight() / 3, cocos2d::Color3B(201, 157, 51));
	labelTitleContent->setPosition(Vec2(btn_mail->getPosition().x + btn_mail->getWidth() + 1 * padding,
		btn_mail->getPosition().y + btn_mail->getHeight() / 2 + 1));
	readMail->addChild(labelTitleContent);

	std::string content = (mail.getSenderUserName().empty() ? mail.getTitle() : mail.getSenderUserName()) + MAIL_FOMAT + mail.getSentTime();
	auto labelContent = MLabel::create(content, sprite_content->getHeight() / 4, cocos2d::Color3B::WHITE);
	labelContent->setWidth(sprite_content->getWidth());
	labelContent->setPosition(Vec2(labelTitleContent->getPosition().x, btn_mail->getPosition().y + btn_mail->getHeight() / 2 - labelContent->getHeight() - 1));
	readMail->addChild(labelContent);
	//end content

	auto btn_del = MButton::create(MAIL_THUNG_RAC, TAG_MAIL_DEL);
	btn_del->setPosition(Vec2(labelTitleContent->getPosition().x + sprite_content->getWidth() - padding,
		background->getHeight() - btn_del->getHeight() - padding));
	readMail->addChild(btn_del);

	auto btn_doc = MButton::create(MAIL_DOC_NHAN, MAIL_TXT_HOME, 12, TAG_MAIL_HOME);
	btn_doc->setPosition(Vec2(btn_del->getPosition().x + btn_del->getWidth() + padding,
		background->getHeight() - btn_doc->getHeight() - padding));
	readMail->addChild(btn_doc);

	auto btn_nhan = MButton::create(MAIL_DOC_NHAN, MAIL_TXT_RECV, 12, TAG_MAIL_RECV);
	btn_nhan->setPosition(Vec2(btn_doc->getPosition().x + btn_doc->getWidth() + padding,
		background->getHeight() - btn_nhan->getHeight() - padding));
	readMail->addChild(btn_nhan);

	if (!rs_item_attachment.empty() && mail.getAttachItemId() > 0){
		auto sprite_item_attach = MSprite::create(rs_item_attachment);
		sprite_item_attach->setPosition(Vec2(btn_mail->getWidth() / 2 - sprite_item_attach->getWidth() / 2
			, btn_mail->getHeight() / 2 - sprite_item_attach->getHeight() / 2));
		btn_mail->addChild(sprite_item_attach);

		auto lb_quantity_attachment = MLabel::create(Common::getInstance()->numberFormatWithCommas(mail.getAttachItemQuatity())
			, btn_mail->getHeight() / 4);
		lb_quantity_attachment->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
		lb_quantity_attachment->setPosition(Vec2(btn_mail->getWidth(), 0));
		btn_mail->addChild(lb_quantity_attachment);

		btn_nhan->setEnabled(true);
	}
	else {
		btn_nhan->setEnabled(false);
	}

	auto sprite_line_title = MSprite::create(MAIL_LINE_TITLE);
	sprite_line_title->setPosition(Vec2(btn_mail->getPosition().x,
		btn_mail->getPosition().y - sprite_line_title->getHeight() - padding));
	readMail->addChild(sprite_line_title);

	MLabel* lbContent = MLabel::create(mail.getBody(), 20, cocos2d::Color3B::WHITE);
	lbContent->setWidth(background->getWidth() - 2 * padding);
	lbContent->setPosition(Vec2(sprite_line_title->getPosition().x,
		sprite_line_title->getPosition().y - lbContent->getContentSize().height - padding));
	readMail->addChild(lbContent);

	auto sprite_line_content = MSprite::create(MAIL_LINE_CONTENT);
	sprite_line_content->setPosition(Vec2(btn_mail->getPosition().x,
		lbContent->getPosition().y - sprite_line_content->getHeight() - padding));
	readMail->addChild(sprite_line_content);

	readMail->addEvents(btn_del, btn_doc, btn_nhan, mail, node);
	return readMail;
}

bool NodeReadMail::init() {
    if (!Node::init())
        return false;

    return true;
}

void NodeReadMail::onEvent(int enventType, Mail sender){
	if (enventType == OnEvenListener::EVENT_CONFIRM_OK){ //khi click xac nhan xoa email
		//goi network xac nhan
		vector<long> selectedMailIds;
		selectedMailIds.push_back(sender.getMailId());
		NetworkManager::getInstance()->deleteMail(selectedMailIds);
		//this->nodeHopThu->hiddenViewReadMail();
	}
}

void NodeReadMail::addEvents(MButton* btnDel, MButton* btnRead, MButton* btnRecv, Mail item, NodeHopThu* node){
	this->nodeHopThu = node;
	btnDel->addTouchEventListener(CC_CALLBACK_2(NodeReadMail::menuCallBack, this, item, node));
	btnRead->addTouchEventListener(CC_CALLBACK_2(NodeReadMail::menuCallBack, this, item, node));
	btnRecv->addTouchEventListener(CC_CALLBACK_2(NodeReadMail::menuCallBack, this, item, node));
}

void NodeReadMail::menuCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type, Mail item, NodeHopThu* node){
	if (type == ui::Widget::TouchEventType::ENDED) {
		MButton *button = (MButton*)sender;
		int tag = button->getTag();
		switch (tag) {
		case TAG_MAIL_HOME:
			node->hiddenViewReadMail();
			break;
		case TAG_MAIL_DEL:
		{
			node->setPosDel();  //ghi nho vi tri xoa
			node->setIdMailDel(item.getMailId());  //ghi nho id mail can xoa
			NodeConfirm<Mail> * nodeConfirm = NodeConfirm<Mail>::create(this, TITLE_POPUP_CONFIRM, TEXT_CONFIRM);
			nodeConfirm->setSender(item);
			nodeConfirm->showDlg();
		}
			break;
		case TAG_MAIL_RECV:
			node->setPosDel();  //ghi nho vi tri xoa
			node->setIdMailDel(item.getMailId());  //ghi nho id mail can xoa
			NetworkManager::getInstance()->claimAttachMail(item.getMailId());
			break;
		default:
			break;
		}
	}
}

float NodeReadMail::getWidth(){
	return getContentSize().width;
}

float NodeReadMail::getHeight(){
	return getContentSize().height;
}

void NodeReadMail::onExit() {
    Node::onExit();
};