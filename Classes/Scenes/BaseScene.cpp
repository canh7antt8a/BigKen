//
//  BaseScene.cpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/8/16.
//
//

#include "BaseScene.hpp"
#include "IntroScene.h"
#include "LoginScene.h"

using namespace cocos2d;
using namespace std;

bool BaseScene::init() {
    if(!Layer::init()) {
        return false;
    }

    Size _visibleSize = Director::getInstance()->getVisibleSize();
    visibleSize = _visibleSize;
    width = _visibleSize.width;
    height = _visibleSize.height;
    
    Vec2 _origin = Director::getInstance()->getVisibleOrigin();
    origin = _origin;
    originX = _origin.x;
    originY = _origin.y;

    this->scheduleUpdate();
    return true;
}

void BaseScene::showToast(const char *message, float duration) {
    MToast* mToast = MToast::create();
    mToast->setPosition(MVec2(width/2,height*0.5f));
	mToast->show(message, duration);
    mToast->setLocalZOrder(INDEX_TOAST);
    this->addChild(mToast);
}

//show tin nhan chat
void BaseScene::showMessageChat(const char* message, Avatar* avatar, float duration){
    MToast* mToast = MToast::create();
    mToast->getBackground()->setAnchorPoint(Vec2(0,0));
    Vec2 posMessageChat;
    int positionIndex = avatar->getPositionIndex();
	auto common = Common::getInstance();
	//ban choi 4 cho
	if (common->getZoneId() == Common::TIENLENMIENNAM_ZONE || common->getZoneId() == Common::PHOM_ZONE || common->getZoneId() == Common::MAUBINH_ZONE) {
		if (positionIndex == 3 || positionIndex == 2){
			mToast->getBackground()->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		}
		else if (positionIndex == 0) {
			mToast->getBackground()->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		}
		else {
			mToast->getBackground()->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		}
	}
	else { //ban choi 8 hoac 10 cho  
		if (positionIndex == 1 || positionIndex == 0){
			mToast->getBackground()->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		}
		else if (positionIndex == 9 || positionIndex == 8 || positionIndex == 7 || positionIndex == 6){
			mToast->getBackground()->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		}
		else {
			mToast->getBackground()->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		}
	}
	
	posMessageChat = Vec2(avatar->getPosition().x + avatar->avatar->getWidth() / 2, avatar->getPosition().y
		+ avatar->avatar->getHeight() / 2);

    mToast->setPosition(posMessageChat);
    mToast->initParams();
    mToast->showWithWrap(message, duration);
    this->addChild(mToast, INDEX_TOAST);
}

void BaseScene::removeOutTablePlay(Avatar* avatar){
    this->removeChild(avatar, true);
}

Vec2 BaseScene::MVec2(float x, float y) {
    return Vec2(originX + x, originY + y);
}

void BaseScene::onExit() {
    Layer::onExit();
}

void BaseScene::closeApp(){
    NetworkManager::getInstance()->closeConnection();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    cocos2d::MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void BaseScene::initialMessageResponseHandler() {
    BINInitializeResponse *init_response = (BINInitializeResponse*)
        Common::getInstance()->checkEvent(NetworkManager::INITIALIZE);

    if (init_response != 0) {
        CCLOG("init response: %s", init_response->DebugString().c_str());
        NetworkManager::setInitialize(init_response->responsecode());
        if (init_response->responsecode()) {
            Common::getInstance()->setEnablePurchaseCash(init_response->enablepurchasecash());
            Common::getInstance()->setEnableTopup(init_response->enabletopup());

            auto scene = LoginScene::createScene();
            REPLACESCENE(0.25f, scene);
        }
        else closeApp();
    }
}

void BaseScene::update(float delta) {
    initialMessageResponseHandler();

    BINPingResponse *pingresponse = (BINPingResponse*)Common::getInstance()->checkEvent(NetworkManager::PING);
    if (pingresponse != 0) {
        CCLOG("ping response: %s", pingresponse->DebugString().c_str());
        if (pingresponse->disconnect()) {
            cocos2d::UserDefault::getInstance()->deleteValueForKey(Common::getInstance()
                ->KEY_SESSION_ID);
            Common::getInstance()->setSessionId("-1");
            this->showToast(pingresponse->message().c_str(), 2);
            this->scheduleOnce(schedule_selector(BaseScene::goToIntroScene), 3.0f);
        }
        else {
            //TODO:SangLX
        }
    }
}

void BaseScene::goToIntroScene(float dt) {
    auto scene = IntroScene::createScene();
    REPLACESCENE(0.25f, scene);
}

void BaseScene::loadEmail(vector<Mail> lstEmail){
	CCLOG("BaseScene: loadEmail");
}

void BaseScene::readMail(Mail mail){

}

void BaseScene::deleteMail(vector<long> lstMailId){

}

void BaseScene::viewUserInfo(BINViewUserInfoResponse *viewUserInfo){

}

void BaseScene::loadMoneyLogHistory(vector<BINMoneyLog> lstMoneyLogs){

}

Mail BaseScene::parseFromBinMail(BINMail binMail){
    Mail mailResult = Mail();
    mailResult.setMailId(binMail.mailid());
    mailResult.setSenderUserId(binMail.senderuserid());
    mailResult.setSenderUserName(binMail.senderusername());
    mailResult.setRecipientUserId(binMail.recipientuserid());
    mailResult.setRecipientUserName(binMail.recipientusername());
    mailResult.setTitle(binMail.title());
    mailResult.setBody(binMail.body());

    string sentTime = Common::getInstance()->convertMillisecondToTime(binMail.senttime());
    mailResult.setSentTime(sentTime);
    mailResult.setReaded(binMail.readed());
    mailResult.setAttachItemId(binMail.attachitemid());
    mailResult.setAttachItemQuatity(binMail.attachitemquatity());

    string expiredTime = Common::getInstance()->convertMillisecondToTime(binMail.expiredtime());
    mailResult.setExpiredTime(expiredTime);
    return mailResult;
}

void BaseScene::filterEmailResponse(){
    BINFilterMailResponse *response = (BINFilterMailResponse*)Common::getInstance()->checkEvent(NetworkManager::FILTER_MAIL);
    if (response != 0){
        CCLOG("filter email response: %s", response->DebugString().c_str());
        if (response->responsecode()){
			vector<Mail> lstEmail;
            Mail binMail;
            for (int i = 0; i < response->mails_size(); i++) {
                binMail = parseFromBinMail(response->mails(i));
				lstEmail.push_back(binMail);
            }
			loadEmail(lstEmail);
        }
        else {
            showToast(response->message().c_str(), 2);
        }
    }
}

void BaseScene::sendMailResponse(){
    BINSendMailResponse *response = (BINSendMailResponse*)Common::getInstance()->checkEvent(NetworkManager::SEND_MAIL);
    if (response != 0){
        CCLOG("send email response: %s", response->DebugString().c_str());
        if (response->has_message()){
            showToast(response->message().c_str(), 2);
        }
    }
}

void BaseScene::readMailResponse(){
    BINReadedMailResponse *response = (BINReadedMailResponse*)Common::getInstance()->checkEvent(NetworkManager::READED_MAIL);
    if (response != 0){
        CCLOG("read email response: %s", response->DebugString().c_str());
        if (response->responsecode()){
            if (response->has_mail()){
                Mail binMail = parseFromBinMail(response->mail());
                //hien thi mail len giao dien
				readMail(binMail);
            }
        }

        if (response->has_message()){
            showToast(response->message().c_str(), 2);
        }
    }
}

void BaseScene::deleteMailResponse(){
    BINDeleteMailResponse *response = (BINDeleteMailResponse*) Common::getInstance()->checkEvent(NetworkManager::DELETE_MAIL);
    if (response != 0){
        CCLOG("delete email response: %s", response->DebugString().c_str());
        if (response->responsecode()){
            //xu li xoa id mail
            int delMailId;
			vector<long> lstMail; //cac mail can xoa
			
			//if (response->deletedmailids_size() > 0){
			//	for (int i = 0; i < response->deletedmailids_size(); i++){
			//		delMailId = response->deletedmailids(i);  //id mail can xoa
			//		lstMail.push_back(delMailId);
			//	}
			//	deleteMail(lstMail);
			//}

			deleteMail(lstMail);
        }
		if (response->has_message()){
			showToast(response->message().c_str(), 2);
		}
    }
}

void BaseScene::claimMailResponse(){
    BINClaimAttachItemResponse *response = (BINClaimAttachItemResponse*)Common::getInstance()->checkEvent(NetworkManager::CLAIM_ATTACH_ITEM);
    if (response != 0){
        CCLOG("claim email response: %s", response->DebugString().c_str());
		
        if (response->has_message()){
            showToast(response->message().c_str(), 2);
        }

		if (response->responsecode()){
			vector<long> lstMail;
			deleteMail(lstMail); //xoa mail
		}
    }
}

void BaseScene::viewUserInfoFromServer(){
	BINViewUserInfoResponse *response = (BINViewUserInfoResponse*) Common::getInstance()->checkEvent(NetworkManager::VIEW_USER_INFO);
	if (response != 0){
		CCLOG("view userinfo response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			if (response->has_userinfo()){
				//BINUserInfo userInfo = response->userinfo();
				viewUserInfo(response);
			}
		}
		if (response->has_message()){
			showToast(response->message().c_str(), 2);
		}
	}
}

//lich su doi thuong
void BaseScene::lookupMoneyHistoryResponse(){
	BINLookUpMoneyHistoryResponse *response = (BINLookUpMoneyHistoryResponse*)Common::getInstance()->checkEvent(NetworkManager::LOOKUP_MONEY_HISTORY);
	if (response != 0){
		CCLOG("lookup money history response: %s", response->DebugString().c_str());
		if (response->responsecode()){
			vector<BINMoneyLog> lstMoneyLogs;
			for (int i = 0; i < response->moneylogs_size(); i++) {
				lstMoneyLogs.push_back(response->moneylogs(i));
			}
			loadMoneyLogHistory(lstMoneyLogs);
		}
		if (response->has_message()){
			showToast(response->message().c_str(), 2);
		}
	}
}

//chup anh man hinh, chup xong thi lay path image share facebook
void BaseScene::captureScreenShareFace(){
    //hideLoading();
	LoadingManager::getInstance()->removeFromParentAndCleanup(true);
    cocos2d::Director::getInstance()->getEventDispatcher()->setEnabled(true);

    Size screenSize = Director::getInstance()->getWinSize();
    RenderTexture* renderTexture = RenderTexture::create(screenSize.width, screenSize.height, Texture2D::PixelFormat::RGBA8888);
    renderTexture->begin();
    this->getParent()->visit();
    renderTexture->end();
    if (renderTexture->saveToFile("snapshot.jpg", Image::Format::JPG)){
        const std::string fullpath = FileUtils::getInstance()->getWritablePath() + "snapshot.jpg";

        //showLoading();
        auto showloading = LoadingManager::getInstance();
        if(showloading->getParent()== NULL ){
            this->addChild(showloading);
            cocos2d::Director::getInstance()->getEventDispatcher()->setEnabled(false);
        }
        
        this->runAction(Sequence::create(DelayTime::create(1.0f),
            CallFunc::create(std::bind(&BaseScene::shareFaceBook, this, fullpath)),
            NULL));
    } else {
        this->showToast("Some Error, Please try again!", 2);
    }
}

//chuyen path screen shot de share face
void BaseScene::shareFaceBook(const std::string& outputFile)
{
    const char* joutputFile = Common::getInstance()->getScreenShotPath();
    cocos2d::Image* img = new Image;
    img->initWithImageFile(outputFile);
    img->saveToFile(joutputFile);
    CC_SAFE_DELETE(img);

    //hideLoading();
	LoadingManager::getInstance()->removeFromParentAndCleanup(true);
    cocos2d::Director::getInstance()->getEventDispatcher()->setEnabled(true);
    
    Common::getInstance()->shareContentFace(joutputFile);
}

//show ra vi tri cho ngoi cua player, dua vao capacity_size
//void BaseScene::showPositionPlayer(){
//    if (capacity_size > 0){
//        for (int i = 1; i < capacity_size; i++){
//            PositionPlayer* positionPlayer = PositionPlayer::create();
//            positionPlayer->setPositionPlayer(Common::getInstance()->getRoomIndex(), i, origin, visibleSize);
//            if (positionPlayer->getParent() == nullptr){
//                this->addChild(positionPlayer);
//            }
//        }
//    }
//}

////show danh sach nguoi cho
//void BaseScene::showWaitingPlayerOnScene(vector<TLMNPlayer> lstWaiting){
//    if (!lstWaiting.empty()){
//        lstDisplayWaitingPlayer.clear();
//
//        int size = (int)lstWaiting.size();
//        int init_distance = 10;
//        int distance = init_distance;
//        for (int i = 0; i < 3; i++){
//            if ((i + 1) > size){
//                break;
//            }
//            WaitingPlayer* waitingPlayer = WaitingPlayer::create();
//            waitingPlayer->setAvatar(lstWaiting[i].getName(), i);
//            waitingPlayer->setPositionAvatar(origin, distance);
//            distance += waitingPlayer->getAvatar()->getWidth()*0.5 + init_distance;
//            lstDisplayWaitingPlayer.push_back(waitingPlayer);
//            this->addChild(waitingPlayer);
//        }
//    }
//}
//
////xoa bo nguoi cho khoi ban choi
//void BaseScene::resetListWaiting(){
//    for (size_t i = 0; i < lstDisplayWaitingPlayer.size(); i++)
//    {
//        if (lstDisplayWaitingPlayer[i]->getParent() != nullptr){
//            lstDisplayWaitingPlayer[i]->removeFromParentAndCleanup(true);
//        }
//    }
//    lstDisplayWaitingPlayer.clear();
//}
//
////hidden card remaining count
//void BaseScene::hiddenCardRemainingCount(vector<Avatar*> &avatars){
//    for (int i = 0; i < avatars.size(); i++){
//        avatars[i]->hiddenNumberCard();
//    }
//}