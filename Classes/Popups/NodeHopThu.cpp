#include "NodeHopThu.hpp"
#include "NodeReadMail.hpp"
#include "UI/MSprite.hpp"
#include "Utils/LoadingManager.hpp"

using namespace std;

bool NodeHopThu::init() {
    if (!Node::init())
        return false;

	auto backgroundPopup = MSprite::create("user_info/bg_popup/content_popup_right.png");

	this->setContentSize(backgroundPopup->getContentSize());

	this->addChild(backgroundPopup);

	auto backgroundContent = MSprite::create(MAIL_CELL_BACKGROUND);

	heightTable = backgroundContent->getHeight();

	tableView = TableView::create(this, Size(backgroundContent->getWidth(), backgroundPopup->getHeight())); //- backgroundPopup->getWidth() + backgroundContent->getWidth()
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDelegate(this);
	tableView->setBounceable(true);
	tableView->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	tableView->setPosition(Vec2((backgroundPopup->getWidth() - backgroundContent->getWidth()) / 2,
		(backgroundPopup->getWidth() - backgroundContent->getWidth()) / 2));
	this->addChild(tableView);
	
    return true;
}

void NodeHopThu::showViewReadMail(Mail mail){
	auto backgroundPopup = MSprite::create("user_info/bg_popup/content_popup_right.png");
	auto backgroundContent = MSprite::create(MAIL_CELL_BACKGROUND);

	Node* nodeReadMail = NodeReadMail::createReadMail(mail, this);
	nodeReadMail->setTag(TAG_MAIL_VIEW_READ);
	nodeReadMail->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	nodeReadMail->setPosition(Vec2((backgroundPopup->getWidth() - backgroundContent->getWidth()) / 2,
		backgroundPopup->getHeight() - 22));
	this->addChild(nodeReadMail);
}

void NodeHopThu::hiddenViewReadMail(){
	auto view_read_mail = this->getChildByTag(TAG_MAIL_VIEW_READ);
	if (view_read_mail != nullptr){
		view_read_mail->removeFromParentAndCleanup(true);
	}
}

void NodeHopThu::resetMail(){
	this->lstMail.clear();
}

float NodeHopThu::getWidth(){
	return getContentSize().width;
}

float NodeHopThu::getHeight(){
	return getContentSize().height;
}

void NodeHopThu::setPosDel(){
	this->posDel = tableView->getContainer()->getPosition();
}

Vec2 NodeHopThu::getPosDel(){
	return this->posDel;
}

int NodeHopThu::getTotalMailLoaded(){
	return this->lstMail.size();
}

void NodeHopThu::setIdMailDel(long idMailDel){
	this->idMailDel = idMailDel;
}

long NodeHopThu::getIdMailDel(){
	return this->idMailDel;
}

bool NodeHopThu::isMailReaded(){
	return this->mailReaded;
}

void NodeHopThu::loadMail(vector<Mail> lstMail){
	if (!lstMail.empty()){
		this->lstMail.insert(this->lstMail.end(), lstMail.begin(), lstMail.end());

		tableView->reloadData();

		if (this->lstMail.size() > NUM_LOAD_MORE_ITEM){ //set lai selection
			int mod = (this->lstMail.size() % NUM_LOAD_MORE_ITEM);
			int numPos = mod == 0 ? NUM_LOAD_MORE_ITEM : mod;
			tableView->getContainer()->setPosition(Vec2(0, -numPos * heightTable));
		}
	}
	/*else {
		tableView->reloadData();
	}*/
}

void NodeHopThu::setMailReaded(bool mailReaded){
	this->mailReaded = mailReaded;
}

void NodeHopThu::readMail(Mail mail){
	int k = -1;
	for (int i = 0; i < this->lstMail.size(); i++){
		if (this->lstMail[i].getMailId() == mail.getMailId()){
			lstMail[i] = mail;
			k = i;
			break;
		}
	}
	
	Vec2 posRead = tableView->getContainer()->getPosition();
	
	if (k != -1){
		tableView->updateCellAtIndex(k);
	}
	
	tableView->getContainer()->setPosition(posRead);

	showViewReadMail(mail); //hien thi len giao dien
}

void NodeHopThu::deleteMail(vector<long> lstMailId){
	if (!this->lstMail.empty() && idMailDel != -1){
		for (int i = 0; i < this->lstMail.size(); i++){
			if (this->lstMail[i].getMailId() == idMailDel){
				//auto cell = tableView->cellAtIndex(i);

				this->hiddenViewReadMail();

				this->lstMail.erase(this->lstMail.begin() + i);
				tableView->reloadData();
				/*if (i + 1 != this->lstMail.size()){
					float disPos = cell->getPosition().y - tableView->cellAtIndex(i + 1)->getPosition().y;
					for (int j = i + 1; j < this->lstMail.size(); j++){
						auto cellTb = tableView->cellAtIndex(j);
						cellTb->setIdx(j - 1);
						cellTb->setPositionY(cellTb->getPositionY() + disPos);
					}
				}


				this->lstMail.erase(this->lstMail.begin() + i);
				tableView->getContainer()->removeChild(cell, true);*/
				break;
			}
		}

		
		//tableView->getContainer()->runAction(MoveTo::create(1.0f, posDel));
		
	}
	/*resetMail();
	NetworkManager::getInstance()->getFilterMailFromServer(0, 10, -1);*/
}

//========================= TableView

Size NodeHopThu::cellSizeForTable(TableView *table) {
	return Size(this->getContentSize().width, this->getContentSize().height/4);
}

ssize_t NodeHopThu::numberOfCellsInTableView(TableView *table) {
    return this->lstMail.size();
}

void NodeHopThu::tableCellTouched(TableView *table, TableViewCell *cell) {
    CCLOG(" CEll %d ",cell->getIdx());
}

TableViewCell* NodeHopThu::tableCellAtIndex(TableView *table, ssize_t idx) {
    TableViewCell *cell = table->dequeueCell();
    if(!cell){
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);

	auto item_mail = ItemMail::create(lstMail[idx], idx, this);
	item_mail->setAnchorPoint(Vec2(0, 0));
	item_mail->setPosition(Vec2(0, 0));
	cell->addChild(item_mail);

	CCLOG("cellIndex: %d", idx);

	if (idx + 1 == this->lstMail.size() && this->lstMail.size() % NUM_LOAD_MORE_ITEM == 0){
		LoadingManager::getInstance()->showLoading();
		NetworkManager::getInstance()->getFilterMailFromServer(idx + 1, NUM_LOAD_MORE_ITEM, -1);
	}

    return cell;
}

void NodeHopThu::onExit() {
    Node::onExit();
}