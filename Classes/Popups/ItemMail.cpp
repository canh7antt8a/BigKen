//
//  ItemCell.cpp
//  MyCards
//
//  Created by hungle on 5/25/16.
//
//

#include "ItemMail.hpp"
#include "UI/MLabel.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"
#include "Popups/NodeConfirm.hpp"

ItemMail::ItemMail(){}

ItemMail::~ItemMail(){}

ItemMail* ItemMail::create(Mail mail, int idx, NodeHopThu* nodeMail){
    ItemMail *cell = new ItemMail();
    if (cell && cell->init()){
        cell->autorelease();
    }else{
        CC_SAFE_DELETE(cell);
    }

	std::string rs_mail;
	std::string rs_content;
	std::string rs_thung_rac;
	std::string rs_doc_nhan;
	//attachment
	std::string rs_item_attachment;

	if (mail.getReaded()){
		rs_mail = MAIL_RD_ICON_MAIL;
		rs_content = "mail/sprite_background_dadoc.png";
		rs_thung_rac = MAIL_RD_THUNG_RAC;
		rs_doc_nhan = MAIL_RD_DOC_NHAN;
		if (mail.getAttachItemId() > 0){  //neu co attachment
			rs_mail = "mail/sprite_dadoc_vatpham.png";
			//rs_item_attachment = "mail/vatpham_ken_dadoc.png";
			rs_item_attachment = StringUtils::format("mail/item_vatpham_dadoc%ld.png", mail.getAttachItemId());
		}
	}
	else {
		rs_mail = MAIL_ICON_MAIL;
		rs_content = MAIL_CELL_BACKGROUND;
		rs_thung_rac = MAIL_THUNG_RAC;
		rs_doc_nhan = MAIL_DOC_NHAN;
		if (mail.getAttachItemId() > 0){  //neu co attachment
			rs_mail = "mail/sprite_vatpham.png";
			//rs_item_attachment = "mail/vatpham_ken.png";
			rs_item_attachment = StringUtils::format("mail/item_vatpham%ld.png", mail.getAttachItemId());
		}
	}

	auto background = MSprite::create(rs_content);
	background->setPosition(Vec2(0, 0));

	cell->setContentSize(background->getContentSize());
	cell->addChild(background);

	auto btn_mail = MSprite::create(rs_mail);
	float padding = btn_mail->getWidth() / 4;
	
	btn_mail->setPosition(Vec2(padding , (background->getHeight() - btn_mail->getHeight()) / 2));
	cell->addChild(btn_mail);

	auto sprite_content = MSprite::create("mail/sprite_noidung.png");

	auto labelTitleContent = MLabel::create(mail.getTitle(), btn_mail->getHeight() / 2, cocos2d::Color3B(201, 157, 51));
	labelTitleContent->setPosition(Vec2(btn_mail->getPosition().x + btn_mail->getWidth() + 1 * padding, background->getHeight() / 2 + 1));
	cell->addChild(labelTitleContent);

	std::string content = (mail.getSenderUserName().empty() ? mail.getTitle() : mail.getSenderUserName()) + MAIL_FOMAT + mail.getSentTime();
	auto labelContent = MLabel::create(content, btn_mail->getHeight() / 3, cocos2d::Color3B::WHITE);
	labelContent->setWidth(sprite_content->getWidth());
	labelContent->setPosition(Vec2(labelTitleContent->getPosition().x, background->getHeight() / 2 - labelContent->getHeight() - 1));
	cell->addChild(labelContent);
	//end content

	auto btn_del = MButton::create(rs_thung_rac, TAG_MAIL_DEL);
	btn_del->setPosition(Vec2(labelTitleContent->getPosition().x + sprite_content->getWidth() - padding,
		(background->getHeight() - btn_del->getHeight()) / 2));
	cell->addChild(btn_del);

	auto btn_doc = MButton::create(rs_doc_nhan, MAIL_TXT_READ, 12, TAG_MAIL_READ);
	btn_doc->setPosition(Vec2(btn_del->getPosition().x + btn_del->getWidth() + padding,
		(background->getHeight() - btn_doc->getHeight()) / 2));
	cell->addChild(btn_doc);

	auto btn_nhan = MButton::create(rs_doc_nhan, MAIL_TXT_RECV, 12, TAG_MAIL_RECV);
	btn_nhan->setPosition(Vec2(btn_doc->getPosition().x + btn_doc->getWidth() + padding,
		(background->getHeight() - btn_nhan->getHeight()) / 2));
	cell->addChild(btn_nhan);

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

	cell->setNodeMail(nodeMail);
	cell->addEvents(btn_del, btn_doc, btn_nhan, mail);
    
    return cell;
}

void ItemMail::setNodeMail(NodeHopThu *nodeMail){
	this->nodeMail = nodeMail;
}

void ItemMail::onEvent(int enventType, Mail sender){
	if (enventType == OnEvenListener::EVENT_CONFIRM_OK){ //khi click xac nhan xoa email
		//goi network xac nhan
		vector<long> selectedMailIds;
		selectedMailIds.push_back(sender.getMailId());
		NetworkManager::getInstance()->deleteMail(selectedMailIds);
	}
}

void ItemMail::menuCallBack(cocos2d::Ref *sender, ui::Widget::TouchEventType type, Mail item){
	if (type == ui::Widget::TouchEventType::ENDED) {
		MButton *button = (MButton*) sender;
		int tag = button->getTag();
		this->nodeMail->setMailReaded(item.getReaded());
		switch (tag) {
		case TAG_MAIL_READ:
			NetworkManager::getInstance()->readMail(item.getMailId(), true);
			break;
		case TAG_MAIL_DEL:
		{
			this->nodeMail->setPosDel();  //ghi nho vi tri xoa
			this->nodeMail->setIdMailDel(item.getMailId());  //ghi nho id mail can xoa
			NodeConfirm<Mail> * nodeConfirm = NodeConfirm<Mail>::create(this, TITLE_POPUP_CONFIRM, TEXT_CONFIRM);
			nodeConfirm->setSender(item);
			nodeConfirm->showDlg();
		}
			break;
		case TAG_MAIL_RECV:
			this->nodeMail->setPosDel();  //ghi nho vi tri xoa
			this->nodeMail->setIdMailDel(item.getMailId());  //ghi nho id mail can xoa
			NetworkManager::getInstance()->claimAttachMail(item.getMailId());
			break;
		default:
			break;
		}
	}
}

void ItemMail::addEvents(MButton* btnDel, MButton* btnRead, MButton* btnRecv, Mail item){
	btnDel->addTouchEventListener(CC_CALLBACK_2(ItemMail::menuCallBack, this, item));
	btnRead->addTouchEventListener(CC_CALLBACK_2(ItemMail::menuCallBack, this, item));
	btnRecv->addTouchEventListener(CC_CALLBACK_2(ItemMail::menuCallBack, this, item));
}

float ItemMail::getWidth(){
    return this->getContentSize().width;
}

float ItemMail::getHeight(){
    return this->getContentSize().height;
}

bool ItemMail::init() {
    if (!Node::init())
        return false;

    return true;
}

void ItemMail::onExit() {
    Node::onExit();
}
