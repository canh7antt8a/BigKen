//
//  ThreeCardsScene.cpp
//  MyCards
//
//  Created by hungle on 7/7/16.
//
//

#include "ThreeCardsScene.hpp"
#include "Utils/SoundManager.h"
#include <algorithm>

#define padding 20

using namespace cocos2d;
using namespace rapidjson;
using namespace std;

const int ThreeCardsScene::AVATARPOS[] = { 0, 1, 4, 5, 6, 7, 2, 3 };

Scene* ThreeCardsScene::createScene(BINRoomPlay roomPlay, std::vector<BINPlayer> playerList,
	vector<BINPlayer> waitingPlayerList, bool createRoom, bool isDisplayRoomList, BINEnterRoomResponse* reEnterRoomResponse) {
    auto scene = Scene::create();
    auto layer = ThreeCardsScene::create();
	layer->setRoomIndex(roomPlay.roomindex());
	layer->setVipRoom(roomPlay.viproom());
	layer->setPassWordRequired(roomPlay.passwordrequired());
	layer->setPlayerList(playerList);
	layer->setCreateRoom(createRoom);
	layer->setWaitingPlayerList(waitingPlayerList);
    layer->setEnterRoomResponse(reEnterRoomResponse);
	layer->setOwnerUserId(Common::getInstance()->getOwnerUserId());
	layer->setMinBet(roomPlay.minbet());
    layer->initMenu();
    layer->initGame();
    
    scene->addChild(layer);
    
    return scene;
}

void ThreeCardsScene::initMenu() {
	PlayScene::initMenu();
    
    auto bkgTable = MSprite::create("ba_cay/ba_cay_table.png");
    bkgTable->setScale(width*0.75f / bkgTable->getWidth());
    bkgTable->setContentSize(Size(width*0.75f, bkgTable->getHeight()*bkgTable->getScale()));
    bkgTable->setPosition(Point(origin.x + visibleSize.width / 2 - bkgTable->getWidth() / 2,
        origin.y + visibleSize.height / 2 - bkgTable->getHeight() / 2));
    this->addChild(bkgTable);

    auto girl = MSprite::create("ba_cay/ba_cay_girl.png");
    girl->setScale(bkgTable->getScale());
    girl->setContentSize(girl->getContentSize() * girl->getScale());
    girl->setPosition(Vec2(bkgTable->getPosition().x + bkgTable->getWidth() / 2 - girl->getWidth() / 2,
        bkgTable->getPosition().y + bkgTable->getHeight() - girl->getHeight() * 3 / 8));
    this->addChild(girl);
    
    btn_san_sang = MButton::create(BTN_BUTTON, "Sẵn sàng", 25, TAG_BACAY_BTN_SANSANG);
    btn_san_sang->setScale(0.8f);
    btn_san_sang->setPosition(Vec2(btn_message->getPosition().x - btn_san_sang->getWidth() - padding,
        btn_message->getPosition().y));
    
    btn_san_sang->addTouchEventListener(CC_CALLBACK_2(ThreeCardsScene::menuCallBack, this));
    btn_san_sang->setVisible(true);
    
    btn_lat_bai = MButton::create("btn_danhbai.png", "Lật bài", 25, TAG_BACAY_BTN_LATBAI);
    btn_lat_bai->setScale(0.8f);
    btn_lat_bai->setPosition(Vec2(originX + visibleSize.width / 2 - btn_lat_bai->getWidth() * btn_lat_bai->getScale(),
        btn_message->getPosition().y));
    btn_lat_bai->addTouchEventListener(CC_CALLBACK_2(ThreeCardsScene::cardCallBack, this));
    
    btn_lat_bai->setVisible(false);

    btn_so_bai = MButton::create(BTN_BUTTON, "So bài", 25, TAG_BACAY_BTN_SOBAI);
    btn_so_bai->setScale(0.8f);
    btn_so_bai->setPosition(Vec2(btn_lat_bai->getPosition().x + btn_lat_bai->getWidth() * btn_lat_bai->getScale(),
                                 btn_message->getPosition().y));
    btn_so_bai->addTouchEventListener(CC_CALLBACK_2(ThreeCardsScene::cardCallBack, this));
    btn_so_bai->setVisible(false);
    
    this->addChild(btn_san_sang);
    this->addChild(btn_lat_bai);
    this->addChild(btn_so_bai);

	sprite_muccuoc = MSprite::create("ba_cay/sprite_somuccuoc.png");
	sprite_muccuoc->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);

	auto label_muccuoc = MLabel::create("", sprite_muccuoc->getHeight() * 0.5f);
	label_muccuoc->setTag(TAG_BTN_LABEL_MUCCUOC);
	label_muccuoc->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	label_muccuoc->setPosition(Vec2(sprite_muccuoc->getWidth() / 2, sprite_muccuoc->getHeight()*0.375f));
	sprite_muccuoc->addChild(label_muccuoc);
	sprite_muccuoc->setVisible(false);

	this->addChild(sprite_muccuoc);

	btn_gopga = MButton::create(BTN_GOPGA,TAG_BTN_GOP_GA);
	btn_gopga->addTouchEventListener(CC_CALLBACK_2(ThreeCardsScene::menuCallBack, this));
	btn_gopga->setPosition(MVec2(width / 2 - btn_gopga->getWidth()/2, height/2 - btn_gopga->getHeight()/2));
	btn_gopga->setVisible(false);
	this->addChild(btn_gopga);
    
	money_sprite = MSprite::create("ba_cay/sprite_hienthi3.png");
	money_sprite->setScale(bkgTable->getScale());
	money_sprite->setContentSize(money_sprite->getContentSize() * money_sprite->getScale());
	money_sprite->setPosition(Vec2(bkgTable->getPosition().x + bkgTable->getWidth() / 2 - money_sprite->getWidth() / 2,
		btn_gopga->getPosition().y + btn_gopga->getHeight() + 10));
    this->addChild(money_sprite);

    txt_tien_ga = MLabel::create("", money_sprite->getHeight() * 0.5f);
    txt_tien_ga->setTextColor(Color4B::GRAY);
    txt_tien_ga->setPosition(Vec2(money_sprite->getWidth() / 2 - txt_tien_ga->getWidth() / 2,
        money_sprite->getHeight() / 2 - txt_tien_ga->getHeight() / 2));
    money_sprite->addChild(txt_tien_ga);
}

void ThreeCardsScene::onEvent(int enventType, BINBetResponse* sender){
	//if (enventType == OnEvenListener::EVENT_CONFIRM_OK){ //khi click xac nhan chap nhan danh bien
	//	//goi network xac nhan
	//	vector<std::pair<int, int>> lstBets;
	//	std::pair<int, int> pair_bet;
	//	pair_bet.first = (int)sender->sourceuserid();
	//	pair_bet.second = (int)sender->betmoney();

	//	lstBets.push_back(pair_bet);

	//	NetworkManager::getInstance()->getConfirmBetByBarier(roomIndex, lstBets);
	//}
	//else 
	if (enventType == OnEvenListener::EVENT_CONFIRM_SELL_CHUONG){  //xac nhan ban chuong
		NetworkManager::getInstance()->getConfirmChangeHostRequest(roomIndex, Common::getInstance()->getUserId(), true, 
			ThreeCard_RequestChangeHostType::CONFIRM_SELL_CHUONG);
	}
	else if (enventType == OnEvenListener::EVENT_CONFIRM_BUY_CHUONG){ //xac nhan mua chuong
		NetworkManager::getInstance()->getConfirmChangeHostRequest(roomIndex, Common::getInstance()->getUserId(), true,
			ThreeCard_RequestChangeHostType::CONFIRM_BUY_CHUONG);
	}
}

void ThreeCardsScene::menuCallBack(Ref *pSender, ui::Widget::TouchEventType eventType) {
    if (eventType == ui::Widget::TouchEventType::ENDED) {
        int tag = ((MButton*)pSender)->getTag();
        switch (tag) {
        case TAG_BACAY_BTN_SANSANG:
            CCLOG("san sang");
			NetworkManager::getInstance()->getReadyToPlayMessageFromServer(roomIndex, -1);
            break;
		case TAG_BTN_CUOC_XACNHAN:
		{
			NetworkManager::getInstance()->getBetByTable(roomIndex, betMoneyTable);
		}
			break;
		case TAG_BTN_GOP_GA:
			NetworkManager::getInstance()->getBetByUnion(roomIndex, minBet);
			break;
        default:
            break;
        }
    }
}

void ThreeCardsScene::cardCallBack(Ref *pSender, ui::Widget::TouchEventType eventType) {
    if (eventType == ui::Widget::TouchEventType::ENDED) {
        int tag = ((MButton*)pSender)->getTag();
        switch (tag) {
        case TAG_BACAY_BTN_LATBAI:
        {
            CCLOG("lat bai");
            //lat quan bai cua minh
			latBai();
        }
            break;
        case TAG_BACAY_BTN_SOBAI:
        {
            CCLOG("so bai");
            vector<BINMapFieldEntry> map_field_entries;
            NetworkManager::getInstance()->getTurnMessageFromServer(roomIndex, map_field_entries);
        }
            break;
        default:
            break;
        }
    }
}

bool ThreeCardsScene::init() {
    if (!PlayScene::init()) {
        return false;
    }

    capacity_size = 8;  
    totalUnionMoney = 0;
    this->scheduleUpdate();
    return true;
}

void ThreeCardsScene::initGame(){
    // TO DO
    if (is_create_room){
        int current_user_id = Common::getInstance()->getUserId();
        setOwnerUserId(current_user_id);
    }

   setListPlayerFromParams(player_list, waiting_player_list);

    if (enter_room_response != 0) {
        handleReEnterRoom(enter_room_response);
    }
}

ThreeCardPlayer ThreeCardsScene::convertFromBINPlayer(BINPlayer binplayer) {
    char buffer[20];
    sprintf(buffer, "%lld", binplayer.userid());
    std::string uid = std::string(buffer);

    int numberCard = 0;

    ThreeCardPlayer player = ThreeCardPlayer(binplayer.username(), uid, numberCard, binplayer.cash(),
        binplayer.gold(), 0, binplayer.tableindex(), binplayer.avatarid());
    return player;
}

void ThreeCardsScene::handleReEnterRoom(BINEnterRoomResponse *response) {
    //TODO: SangLX
    if (response->has_message()){
        showToast(response->message().c_str(), 2);
    }

    if (response->responsecode()){
        //handle current cards, flip cards
        if (response->args_size() > 0) {
            for (int i = 0; i < response->args_size(); i++) {
                BINMapFieldEntry entry = response->args(i);
                if (entry.key() == "currentCards") {
                    string json_val = entry.value();
                    for (int i = 0; i < avatars.size(); i++) {
                        ThreeCardAvatar* avatar = (ThreeCardAvatar*)avatars[i];
                        if (avatar != 0 && avatar->getPlayerId() != Common::getInstance()->getUserId())
                            avatar->showCardCover();
                    }

                    card_values = parseCardValue(json_val);
                    if (!card_values.empty()) {
                        for (int i = 0; i < card_values.size(); i++) {
                            if (Common::getInstance()->getUserId() != card_values[i].first) {
                                ThreeCardAvatar* avatar = (ThreeCardAvatar*)findAvatarOfPlayer(card_values[i].first);
								if (avatar != 0){
									avatar->setCards(card_values[i].second);
									avatar->flipCards();
								}
                            }
                            else {
                                sortCard(card_values[i].second);
                            }
                        }
                    }
                }
                else if (entry.key() == "chickenBet") {
                    if (!entry.value().empty()) {
                        totalUnionMoney = Common::getInstance()->convertStringToInt(entry.value());
                        txt_tien_ga->setString(totalUnionMoney != 0 ? StringUtils::format("%d", totalUnionMoney) : "");
                        txt_tien_ga->setPosition(Vec2(money_sprite->getWidth() / 2 - txt_tien_ga->getWidth() / 2,
                            money_sprite->getHeight() / 2 - txt_tien_ga->getHeight() / 2));
                    }
                }
                else if (entry.key() == "hostPlayer") {
                    if (!entry.value().empty()) {
                        int host_user_id = Common::getInstance()->convertStringToInt(entry.value());

						Common::getInstance()->setOwnerUserId(host_user_id);
						setOwnerUserId(host_user_id);
						is_create_room = Common::getInstance()->getUserId() == host_user_id;
						displayLockRoomForOwner(host_user_id);

                        ThreeCardAvatar *avatar = (ThreeCardAvatar *)findAvatarOfPlayer(host_user_id);
                        if (avatar != 0) {
                            avatar->showChuong(true);
                        }
                    }
                }
				else if (entry.key() == "isAlreadyFlipUpCard"){  //da lat bai chua
					if (!entry.value().empty()) {
						bool isAlreadyFlipUpCard = Common::getInstance()->to_bool(entry.value());
						if (isAlreadyFlipUpCard){
							latBai();
							if (btn_so_bai->isVisible())
								btn_so_bai->setVisible(false);
						}
						else {
							if (!btn_lat_bai->isVisible())
								btn_lat_bai->setVisible(true);
							if (!btn_so_bai->isVisible())
								btn_so_bai->setVisible(true);
						}
					}
				}
				else if (entry.key() == "startMatchCdRemaining"){ //thoi gian coutdown bat dau van
					if (!entry.value().empty()) {
						Avatar* avatar = findAvatarOfPlayer(getOwnerUserId());  //avatar chuong
						if (avatar != 0){
							avatar->updateProgressCircleBar(100, Common::getInstance()->convertStringToInt(entry.value()));
						}
					}
				}
				else if (entry.key() == "betNormalMoney"){  //tien dat cuoc voi chuong
					if (!entry.value().empty()) {
						vector<pair<int, int>> lstbetNormalMoney = parseKeyIntValue(entry.value());
						for (int i = 0; i < lstbetNormalMoney.size(); i++){
							ThreeCardAvatar* avatar = (ThreeCardAvatar*)findAvatarOfPlayer(lstbetNormalMoney[i].first);
							if (avatar != 0){
								if (lstbetNormalMoney[i].first == Common::getInstance()->getUserId()){
									if (lstbetNormalMoney[i].second > 0){
										hiddenBetTable(); //an cuoc ban
									}
									else if (card_tag.size() == 0){ //chua chia bai thi show cuoc ban
										showBetTable();
									}
								}
								avatar->setBetMoney(lstbetNormalMoney[i].second);
							}
						}
					}
				}
				else if (entry.key() == "betChickenMoney"){  //da dat cuoc ga
					if (!entry.value().empty()) {
						vector<pair<int, bool>> lstBetChicken = parseKeyBoolValue(entry.value());
						for (int i = 0; i < lstBetChicken.size(); i++){
							ThreeCardAvatar* avatar = (ThreeCardAvatar*)findAvatarOfPlayer(lstBetChicken[i].first);
							if (avatar != 0){
								avatar->showGa(lstBetChicken[i].second);
							}
						}
					}
				}
            }
        }
    }
}

void ThreeCardsScene::latBai(){
	for (int i = 0; i < card_tag.size(); i++) {
		auto moveTo = MoveTo::create(0.1f*i, MVec2(visibleSize.width / 2 + (i - ((int)card_tag.size() - 1)*0.5f) * cardWidth(),
			card_tag[i]->getPosition().y));
		card_tag[i]->runAction(moveTo);
		card_tag[i]->removeEvents();
	}

	if (btn_lat_bai->isVisible())
		btn_lat_bai->setVisible(false);
}

void ThreeCardsScene::setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list) {
    //TODO: SangLX
    if (!lst_player.empty()) lst_player.clear();
    if (!lst_waiting.empty()) lst_waiting.clear();

    for (BINPlayer player : player_list) {
        lst_player.push_back(convertFromBINPlayer(player));
    }

    for (BINPlayer player : waiting_player_list) {
        lst_waiting.push_back(convertFromBINPlayer(player));
    }

    if (is_create_room){
        btn_san_sang->setVisible(false);
    }
    else {
        if (isUserPlaying()){
			showInvitePlayer(lst_player.size());
            btn_san_sang->setVisible(false);
		}
		else {
			showBtnWithWatingPlayer(false);
		}
    }

    showWaitingPlayerOnScene(lst_waiting);

    sortListPlayer();

    displayInfoRemainCard(lst_player);
}

void ThreeCardsScene::sortListPlayer() {
    sort(lst_player.begin(), lst_player.end());
}

void ThreeCardsScene::displayInfoRemainCard(std::vector<ThreeCardPlayer>& remain_card_infos) {
    /*currentIndex = -1;
    currentTableIndex = -1;
    int user_id = Common::getInstance()->getUserId(); 
    for (int i = 0; i < remain_card_infos.size(); i++)  {
        int val;
        std::stringstream ss(remain_card_infos[i].getID());
        ss >> val;
        if (user_id == val) {
            currentIndex = i;
            currentTableIndex = remain_card_infos[i].getTableIndex();
            break;
        }
    }*/
    //end find current index

    //CCLOG("list player size: %lu", remain_card_infos.size());

    //int index = currentIndex;
    int len = (int)remain_card_infos.size();
    for (int i = 0; i < len; i++) {
        setPositionPlayer(remain_card_infos[i], i);
    }
}

void ThreeCardsScene::showWaitingPlayerOnScene(vector<ThreeCardPlayer> lstWaiting){
    if (!lstWaiting.empty()){
        lstDisplayWaitingPlayer.clear();

        int size = (int)lstWaiting.size();
        int init_distance = 10;
        int distance = init_distance;
        for (int i = 0; i < 3; i++){
            if ((i + 1) > size){
                break;
            }
            WaitingPlayer* waitingPlayer = WaitingPlayer::create();
            waitingPlayer->setAvatar(lstWaiting[i].getName(), lstWaiting[i].getAvatarId());
            waitingPlayer->setPositionAvatar(origin, distance);
            distance += waitingPlayer->getAvatar()->getWidth()*0.5 + init_distance;
            lstDisplayWaitingPlayer.push_back(waitingPlayer);
            this->addChild(waitingPlayer);
        }
    }
}

Player* ThreeCardsScene::findPlayer(long long player_id){
    char c_player_id[50];
    sprintf(c_player_id, "%lld", player_id);

    std::string s_player_id = std::string(c_player_id);

    for (int i = 0; i < lst_player.size(); i++){
        if (lst_player[i].getID() == s_player_id){
            return &lst_player[i];
        }
    }
    return NULL;
}

//tim nguoi cho
Player* ThreeCardsScene::findWaiting(long long player_id){
	char c_player_id[50];
	sprintf(c_player_id, "%lld", player_id);
	std::string s_player_id = std::string(c_player_id);

	for (int i = 0; i < lst_waiting.size(); i++){
		if (lst_waiting[i].getID() == s_player_id){
			return &lst_waiting[i];
		}
	}
	return NULL;
}

void ThreeCardsScene::deleteWaitingPlayer(string player_id){
	int k = -1;
	for (int i = 0; i < lst_waiting.size(); i++){
		if (lst_waiting[i].getID() == player_id){
			k = i;
		}
	}

	if (k != -1 && !lst_waiting.empty())
		lst_waiting.erase(lst_waiting.begin() + k);
}

void ThreeCardsScene::showBetTable(){
	if (this->getChildByTag(TAG_NODE_BACAY_BETTABLE) == nullptr){
		//_eventDispatcher->pauseEventListenersForTarget(this, true);

		Node *nodeBetTable = Node::create();
		nodeBetTable->setTag(TAG_NODE_BACAY_BETTABLE);

		auto bg_bet_table = MSprite::create(BG_CUOC_BAN);
		bg_bet_table->setScaleY(height / bg_bet_table->getHeight());
		bg_bet_table->setContentSize(Size(bg_bet_table->getWidth(), height / bg_bet_table->getHeight()));
		nodeBetTable->addChild(bg_bet_table);

		auto btn_xac_nhan = MButton::create(BTN_CUOC_XACNHAN, TXT_CUOC_XACNHAN, 30, TAG_BTN_CUOC_XACNHAN);
		btn_xac_nhan->addTouchEventListener(CC_CALLBACK_2(ThreeCardsScene::menuCallBack, this));
		btn_xac_nhan->setPosition(Vec2(bg_bet_table->getWidth() - 3 * btn_xac_nhan->getWidth() / 2, 20));
		nodeBetTable->addChild(btn_xac_nhan);

		auto tmp = MSprite::create(SPRITE_CUOC_BAN);
		float posX = btn_xac_nhan->getPosition().x + btn_xac_nhan->getWidth() / 2;

		auto slider_bet_table = Slider::create();
		slider_bet_table->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		slider_bet_table->loadBarTexture(SPRITE_CUOC_BAN);
		slider_bet_table->loadSlidBallTextureNormal(SPRITE_SLID_BALL);
		slider_bet_table->setPosition(Vec2(posX + tmp->getHeight() / 2,
			btn_xac_nhan->getPosition().y + 5 * btn_xac_nhan->getHeight() / 3));
		slider_bet_table->setMaxPercent(minBet);
		slider_bet_table->addEventListener(CC_CALLBACK_2(ThreeCardsScene::sliderEvent, this));
		slider_bet_table->setRotation(-90);

		int numIncrease = minBet > 1000 ? 1000 : 100;
		int countIncrease = minBet / numIncrease;
		float distance = tmp->getWidth() / countIncrease;
		int count = 0;
		int posY;
		for (int i = 0; i <= minBet; i += numIncrease){
			posY = slider_bet_table->getPosition().y + count*distance;

			auto labelMoneyBet = MLabel::create(StringUtils::format("%d", i + minBet), 20);
			labelMoneyBet->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			labelMoneyBet->setPosition(Vec2(posX + btn_xac_nhan->getWidth() / 4 + 5, posY));
			nodeBetTable->addChild(labelMoneyBet);

			auto spriteSplit = MSprite::create(SPRITE_MUCCUOC);
			spriteSplit->setAnchorPoint(Point::ANCHOR_MIDDLE);
			spriteSplit->setPosition(Vec2(posX, posY));
			nodeBetTable->addChild(spriteSplit);

			count++;
		}

		nodeBetTable->addChild(slider_bet_table);
		nodeBetTable->setPosition(MVec2(visibleSize.width - bg_bet_table->getWidth(), 0));
		this->addChild(nodeBetTable);

		posXcuoc = width - 3 * btn_xac_nhan->getWidth() / 2;

		sprite_muccuoc->setPosition(Vec2(originX + posXcuoc, slider_bet_table->getPosition().y));
		sprite_muccuoc->setVisible(true);

		betMoneyTable = minBet;
		setTextBetTable(betMoneyTable);
	}
}

void ThreeCardsScene::hiddenBetTable(){
	//_eventDispatcher->resumeEventListenersForTarget(this, true);

	if (this->getChildByTag(TAG_NODE_BACAY_BETTABLE) != nullptr){
		this->removeChildByTag(TAG_NODE_BACAY_BETTABLE);
	}

	sprite_muccuoc->setVisible(false);
}

//show cuoc bien
void ThreeCardsScene::showBetBarier(){
	for (int i = 0; i < avatars.size(); i++){
		if (avatars[i]->getPlayerId() != getOwnerUserId() 
				&& avatars[i]->getPlayerId() != Common::getInstance()->getUserId()){
			avatars[i]->showBetBarier();
		}
	}
}

//hidden cuoc bien
void ThreeCardsScene::hiddenBetBarier(){
	for (int i = 0; i < avatars.size(); i++){
		avatars[i]->hiddenBetBarier();
	}
}

//hidden ga
void ThreeCardsScene::hiddenBetUnion(){
	for (int i = 0; i < avatars.size(); i++){
		avatars[i]->showGa(false);
	}
}

void ThreeCardsScene::setTextBetTable(int moneyBetTable){
	MLabel *label_muccuoc = (MLabel*)sprite_muccuoc->getChildByTag(TAG_BTN_LABEL_MUCCUOC);
	label_muccuoc->setString(StringUtils::format("%d", moneyBetTable));
}

void ThreeCardsScene::sliderEvent(Ref *pSender, Slider::EventType eventType){
	if (eventType == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);

		Vec2 vv2 = slider->getTouchMovePosition();
		betMoneyTable = minBet + slider->getPercent();

		if (!sprite_muccuoc->isVisible()){
			sprite_muccuoc->setVisible(true);
		}

		setTextBetTable(betMoneyTable);

		sprite_muccuoc->setPosition(Vec2(originX + posXcuoc, vv2.y));
	}
}

void ThreeCardsScene::resetDisplayAvatar(){
	if (!avatars.empty()){
		for (int i = 0; i < avatars.size(); i++){
			if (avatars[i]->getParent() != nullptr){
				this->removeChild(avatars[i]);
			}
		}
		avatars.clear();
	}
}

bool ThreeCardsScene::isUserPlaying() {
    int user_id = Common::getInstance()->getUserId();
    Player* player = findPlayer(user_id);
    if (player != 0){
        return true;
    }
    return false;
}

void ThreeCardsScene::onExit() {
    PlayScene::onExit();
}

void ThreeCardsScene::setPositionPlayer(ThreeCardPlayer& player, int position) {
    //TODO: SangLX - HungLe
    auto avatar = ThreeCardAvatar::create();
    int position_index = ThreeCardsScene::AVATARPOS[position];

    string user_name = player.getName();
    string user_id = player.getID();
    long long gold = player.getGold();
    long long cash = player.getCash();

    std::string buffer = StringUtils::format("%lld $", is_vip_room ? cash : gold);
    int image_index = player.getAvatarId();
    CCLOG("image index: %d", image_index);

    avatar->loadAvatar(image_index, user_id, user_name, buffer, roomIndex, minBet);
    avatar->setAvatarPostion(position_index, origin, visibleSize, btn_san_sang->getHeight());

	avatar->addCardCover(cardWidth() * 0.8f);
	if (getOwnerUserId() == Common::getInstance()->convertStringToInt(user_id)){  //neu la chuong
		avatar->showChuong(true);
	}
	else {
		avatar->showChuong(false);
	}
	avatar->showGa(false);

    avatars.push_back(avatar);

    if (avatar->getParent() == nullptr)
        this->addChild(avatar);
}

//lay ra avatar cua nguoi choi
Avatar* ThreeCardsScene::findAvatarOfPlayer(long long player_id) {
	for (int i = 0; i < avatars.size(); i++){
		if (avatars[i]->getPlayerId() == player_id){
			return avatars[i];
		}
	}
	return NULL;
}

void ThreeCardsScene::update(float dt) {
    PlayScene::update(dt);

	roomOwnerChangedResponseHandler();
	playerExitRoomResponse();
	playerExitAfterMatchEndResponse();
	playerEnterRoomResponseHandler();

	preparenewMatchHandler();
    startMatchHandler(); 
    updateMoneyHandler();
    turnHandler();
    betHandler();
	matchEndResponseHandler();
	readyToPlayResponseHandler();

	cancelExitAfterMatchEndResponseHandler();
}

void ThreeCardsScene::dissmissPopupConfirm(){
	if (Director::getInstance()->getRunningScene()->getChildByTag(TAG_NODE_CONFIRM) != nullptr){ //an cac popup xac nhan di
		_eventDispatcher->resumeEventListenersForTarget(Director::getInstance()->getRunningScene(), true);
		Director::getInstance()->getRunningScene()->removeChildByTag(TAG_NODE_CONFIRM);
	}
}

void ThreeCardsScene::startMatchHandler() {
    BINStartMatchResponse *response = (BINStartMatchResponse *)
        Common::getInstance()->checkEvent(NetworkManager::START_MATCH);
    if (response != 0) {
        CCLOG("start match response: %s", response->DebugString().c_str());
		if (response->has_message()){
			this->showToast(response->message().c_str(), 2);
		}
        if (response->responsecode()) {
            if (this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr){
                this->removeChildByTag(TAG_TIME_COUNTDOWN);
            }

            if (response->has_countdowntimer() && response->countdowntimer() >= 0) {
                setMatchCountDownTime(response->countdowntimer());
            }

			//Avatar* avatar = findAvatarOfPlayer(getOwnerUserId());  //avatar chuong
			//if (avatar != 0){
			//	avatar->updateProgressCircleBar(100, getMatchCountDownTime());
			//}

			for (int i = 0; i < avatars.size(); i++){
				if (avatars[i]->getPlayerId() == getOwnerUserId()){
					avatars[i]->updateProgressCircleBar(100, getMatchCountDownTime());
				}
				else {
					avatars[i]->resetProcessCircleBar();
				}
			}

			if (findAvatarOfPlayer(Common::getInstance()->getUserId()) == 0){  //neu la nguoi cho thi chia bai se hien thi 3 cay up xuong
				for (int i = 0; i < avatars.size(); i++) {
					ThreeCardAvatar* avatar = (ThreeCardAvatar*)avatars[i];
					if (avatar != 0)
						avatar->showCardCover();
				}
			}

            if (response->args_size() > 0)  {  //truong hop da dat cuoc thi chia bai
				if (findAvatarOfPlayer(Common::getInstance()->getUserId()) != 0){ //nguoi cho khong nhin thay bai dc chia
					dissmissPopupConfirm(); //an cac popup xac nhan di

					hiddenBetTable();  //an cuoc ban
					hiddenBetBarier();  //an cuoc bien
					btn_gopga->setVisible(false);
					if (!btn_so_bai->isVisible())
						btn_so_bai->setVisible(true);
					if (!btn_lat_bai->isVisible())
						btn_lat_bai->setVisible(true);

					vector<int> current_card_values = Common::getInstance()
						->convertStringsToInt(Common::getInstance()->split(response->args(0).value(), ','));
					sortCard(current_card_values);
				}

                //show card cover
                for (int i = 0; i < lst_player.size(); i++) {
                    int user_id = Common::getInstance()->convertStringToInt(lst_player[i].getID());
                    auto avatar = (ThreeCardAvatar *)findAvatarOfPlayer(user_id);
                    if (avatar != 0 && user_id != Common::getInstance()->getUserId()) {
                        avatar->showCardCover();
                    }
                }
			}
			else {
				//truong hop dat cuoc
				if (findAvatarOfPlayer(Common::getInstance()->getUserId()) != 0){
					dissmissPopupConfirm(); //an cac popup xac nhan di

					//neu la nguoi choi va khong phai chu phong thi show dat cuoc
					if (Common::getInstance()->getUserId() != getOwnerUserId()){  //neu khong phai chuong
						showBetTable();
						showBetBarier();  //show cuoc bien
					}
					
					btn_gopga->setVisible(true); //show dat ga
				}
			}
        }
    }
}

void ThreeCardsScene::showInitCard() {
    for (int i = 0; i < cards.size(); i++){
        this->createCards(i);
        if (card_tag[i]->getParent() == nullptr)
            this->addChild(card_tag[i]);
    }

    SoundManager::getInstance()->playSound(soundTLMN[37]);
    CCLOG("card tag size: %d", (int)card_tag.size());
    for (int i = 0; i < card_tag.size(); i++){

        auto moveTo = MoveTo::create(0.2f + 0.06f*i, MVec2(visibleSize.width * 0.5f
                                                           + cardWidth()*(0.08f*i - ((int)card_tag.size()-1)*0.5f),
                                     5 + btn_message->getHeight()*1.5f + cardWidth() * CARD_RATIO * 0.5f));
        card_tag[i]->runAction(moveTo);
    }
}

void ThreeCardsScene::handleWinLose(BINMatchEndResponse *response) {
	//handle win
	for (int i = 0; i < response->winninguserids_size(); i++) {
		int val = (int)response->winninguserids(i);
		for (int j = 0; j < lst_player.size(); j++) {
			std::stringstream ss(lst_player[j].getID());
			int player_uid;
			ss >> player_uid;
			if (val == player_uid) {
				lst_player[j].setWin(true);
				break;
			}
		}
	}
	//handle lose
	for (int i = 0; i < response->losinguserids_size(); i++) {
		int val = (int)response->losinguserids(i);
		for (int j = 0; j < lst_player.size(); j++) {
			std::stringstream ss(lst_player[j].getID());
			int player_uid;
			ss >> player_uid;
			if (val == player_uid) {
				lst_player[j].setWin(false);
				break;
			}
		}
	}
	
	for (ThreeCardPlayer player : lst_player){
		if (player.isWin()){
			findAvatarOfPlayer(Common::getInstance()->convertStringToInt(player.getID()))->setWin(3.0f);
		}
		else{
			findAvatarOfPlayer(Common::getInstance()->convertStringToInt(player.getID()))->setLose(3.0f);
		}
	}

    if (response->args_size() > 0) {
        for (int i = 0; i < response->args_size(); i++) {
            BINMapFieldEntry entry = response->args(i);
            if (entry.key() == "winBetContributeChicken") {
                int user_id = Common::getInstance()->convertStringToInt(entry.value());
                receiveMoneyFromBetChicken(user_id);
            }
        }
    }
}

void ThreeCardsScene::receiveMoneyFromBetChicken(int user_id) {
    //TODO: HungLe - receive money from bet chicken
    auto avatar = (ThreeCardAvatar*)findAvatarOfPlayer(user_id);
    if(avatar==0){
        return;
    }
    for(int i = 0 ;i<sprites.size();i++){
        for(int j = 0 ;j<sprites[i].size();j++){
            auto pos = avatar->getPosition() + avatar->getContentSize()/2;
            sprites[i][j]->runAction(Sequence::create(MoveTo::create(0.75f+j*0.2f,pos),
                                                      FadeOut::create(0.5f),RemoveSelf::create(),NULL));
        }
    }
}

void ThreeCardsScene::createCards(int index){
    auto cardx = cards[index];
    auto cardSprite = BaCayCardSprite::createCard(cardx, cardWidth());

    cardSprite->setPosition(MVec2(visibleSize.width / 2,
        visibleSize.height / 2));
    this->card_tag.push_back(cardSprite);
}

void ThreeCardsScene::sortCard(vector<int> card_values) {
    std::sort(card_values.begin(), card_values.end());
    if (!cards.empty()) cards.clear();
    for (int i = 0; i<card_values.size(); i++){
        Card card;
        card.value = card_values[i]; // Số thẻ là 1-52
        cards.push_back(card);

    }
    this->showInitCard();
}

void ThreeCardsScene::cancelExitAfterMatchEndResponseHandler() {
	BINCancelExitAfterMatchEndResponse* cancel_exit_room_response =
		(BINCancelExitAfterMatchEndResponse *)Common::getInstance()->checkEvent(NetworkManager::CANCEL_EXIT_ROOM);
	if (cancel_exit_room_response != 0 && cancel_exit_room_response->cancelexituserid()) {
		CCLOG("cancel exit room response: %s", cancel_exit_room_response->DebugString().c_str());
		if (cancel_exit_room_response->responsecode()) {

			long cancelExitUserId = cancel_exit_room_response->cancelexituserid();
			Player* playCancelExitRoom = findPlayer(cancelExitUserId);

			if (playCancelExitRoom != 0){
				/*char message[60];
				sprintf(message, "Người chơi %s hủy đăng kí rời bàn chơi", playCancelExitRoom->getName().c_str());
				this->showToast(message, 2);*/

				Avatar* avatar = findAvatarOfPlayer(cancel_exit_room_response->cancelexituserid());
				if (avatar != 0){
					avatar->showRegisterExitRoom(false);
				}
			}

			// Hung code them phan hien thi hieu ung nguoi choi dang ky roi ban
			// Avatar* avatar = findAvatarOfPlayer(cancel_exit_room_response->cancelexituserid());
			//avatar->hideExitRoom();
		}
		else {
			this->showToast(cancel_exit_room_response->message().c_str(), 2);
		}
	}
}

void ThreeCardsScene::updateMoneyHandler() {
    BINUpdateMoneyResponse *response = (BINUpdateMoneyResponse *)
        Common::getInstance()->checkEvent(NetworkManager::UPDATE_MONEY);
    if (response != 0){ 
        CCLOG("update money response: %s", response->DebugString().c_str());

		if (response->moneyboxes_size() > 0) {
			BINMoneyBox moneyBox;
			long long origin_money; //so tien ma nguoi choi dang co
			Player* player;

			ThreeCardAvatar* avatar;
			std::string txt_money_type;
			int delay_time = 0;

			string reasonMoney[] = { "startMatch", "betWithHost", "betContributeChicken", "betSolo", "matchEnd"};

			for (int j = 0; j < 5; j++){
				for (int i = 0; i < response->moneyboxes_size(); i++) {
					moneyBox = response->moneyboxes(i); //money_boxe : userId , money, reason
					if (moneyBox.reason() == reasonMoney[j]){
						bool isCash = moneyBox.iscash();
						player = findPlayer(moneyBox.userid());

						if (player != 0){
							//lay ra tien cua nguoi choi dua vao cash hay gold
							origin_money = moneyBox.currentmoney();

							//set lai tien cho nguoi choi
							player->setMoney(isCash, origin_money);

							//neu la nguoi dang nhap thi cap nhat lai tien vao common
							if (moneyBox.userid() == Common::getInstance()->getUserId()){
								if (isCash){
									Common::getInstance()->setCash(origin_money);
								}
								else {
									Common::getInstance()->setGold(origin_money);
								}
							}

							avatar = (ThreeCardAvatar*)findAvatarOfPlayer(moneyBox.userid());
							if (avatar != 0){
								avatar->setMoney(origin_money);

								if (moneyBox.displaychangemoney() != 0){
									if (moneyBox.reason() == "betWithHost"){
										txt_money_type = " Cược bàn";
										delay_time = 0;
									}
									else if (moneyBox.reason() == "betContributeChicken"){
										txt_money_type = " Gà";
										delay_time = 1;                                        
									}
									else if (moneyBox.reason() == "betSolo"){
										txt_money_type = " Cược biên";
										delay_time = 2;
									}
									auto moneyText = MLabel::createUpdateMoney(moneyBox.displaychangemoney(), delay_time, 2.4f *
										avatar->name->getHeight(), txt_money_type);
									moneyText->setPosition(Vec2(avatar->getPosition().x + avatar->avatar->getWidth() / 2,
										avatar->getPosition().y + avatar->avatar->getHeight()));
									this->addChild(moneyText,INDEX_UPDATE_MONEY);
								}
							}
						}
					}
				}
			}
		}

		if (response->has_message()){
			showToast(response->message().c_str(), 2);
		}
    }
}

void ThreeCardsScene::setMatchCountDownTime(int _countDownTime) {
    this->_matchCountDownTime = _countDownTime;
}

int ThreeCardsScene::getMatchCountDownTime() {
    return this->_matchCountDownTime;
}

void ThreeCardsScene::betHandler() {
    BINBetResponse *response = (BINBetResponse *)Common::getInstance()
        ->checkEvent(NetworkManager::BET);
    if (response != 0) {
        CCLOG("bet response: %s", response->DebugString().c_str());

		if (response->has_message()){
			showToast(response->message().c_str(), 2);
		}

		if (response->responsecode()){
			if (response->bettype() == ThreeCard_BetType::BET_TABLE){
				if (Common::getInstance()->getUserId() == response->sourceuserid()){
					hiddenBetTable(); //an cuoc ban
				}
                //hien thi so tien dat
                if (response->has_betmoney()) {
                    ThreeCardAvatar* avatar = (ThreeCardAvatar*)findAvatarOfPlayer(response->sourceuserid());
                    if (avatar != 0) {
                        avatar->setBetMoney((int)response->betmoney());
                    }
                }

				//btn_gopga->setVisible(true); //show dat ga
			}
			else if (response->bettype() == ThreeCard_BetType::DANH_BIEN){
				if (response->targetuserid() == Common::getInstance()->getUserId()){  //neu la nguoi dc chon danh bien
					//show xac nhan danh bien
					ThreeCardAvatar* playerSource = (ThreeCardAvatar*)findAvatarOfPlayer(response->sourceuserid());
					if (playerSource != 0){
						/*std::string msg_confirm = "Người chơi " + playerSource->getName() + " muốn đánh biên số tiền " 
							+ StringUtils::format("%lld", response->betmoney()) 
							+ (is_vip_room ? " Xu" : " Ken") + ", bạn có muốn thử sức không ? ";
						
						NodeConfirm<BINBetResponse*> * nodeConfirm = NodeConfirm<BINBetResponse*>::create(this,
                                                                                                          TITLE_POPUP_CONFIRM, msg_confirm);
						nodeConfirm->setSender(response);
						nodeConfirm->showDlg();*/
						playerSource->showBetBarier(response->betmoney(), true);
					}
				}
			}
			else if (response->bettype() == ThreeCard_BetType::GOP_GA){
				if (response->sourceuserid() == Common::getInstance()->getUserId()){  //neu la nguoi dat ga
					btn_gopga->setVisible(false); //an nut dat ga di
				}

				//show dat ga cho avatar
				ThreeCardAvatar* avatar = (ThreeCardAvatar*) findAvatarOfPlayer(response->sourceuserid());
				if (avatar != 0){
					avatar->showGa(true);
				}
                // add animation gop ga
                int user_bet_money = (int)response->betmoney();
                //cong tien vao
                totalUnionMoney += user_bet_money;
                vector<pair<int, int>> bet_money_response = 
                    Common::getInstance()->parseBetMoney(totalUnionMoney);
                handleBetMoneyType((int)response->sourceuserid(), bet_money_response);
                txt_tien_ga->setString(totalUnionMoney != 0 ? StringUtils::format("%d", totalUnionMoney):  "");
                txt_tien_ga->setPosition(Vec2(money_sprite->getWidth() / 2 - txt_tien_ga->getWidth() / 2,
                    money_sprite->getHeight() / 2 - txt_tien_ga->getHeight() / 2));
                
			}
			else if (response->bettype() == ThreeCard_BetType::DONG_Y_DANH_BIEN) {
				Player* playerConfirm = findPlayer(response->sourceuserid());
				if (playerConfirm != 0){
					std::string msg = "Người chơi " + playerConfirm->getName() + " đã đồng ý đánh biên với bạn số tiền "
						+ StringUtils::format("%lld", response->betmoney())
						+ (is_vip_room ? " Xu" : " Ken");
					showToast(msg.c_str(), 2);
				}
			}
		}
    }
}

void ThreeCardsScene::handleBetMoneyType(int sourceuserid, vector<pair<int, int>> bet_money_response) {
	//TODO: HungLe
	auto sourceAvatar = findAvatarOfPlayer(sourceuserid);
	if (sourceAvatar == 0){
		return;
	}
	auto spriteXu = MSprite::create("ba_cay/icon_chip50.png");
	for (int i = 0; i<bet_money_response.size(); i++) {
		int value = bet_money_response[i].first; // gia tri
		int count = bet_money_response[i].second;  //so luong
		//==== hùng
		Vec2 fromPos = sourceAvatar->getPosition() + sourceAvatar->getContentSize() / 2;
		Vec2 toPos = money_sprite->getPosition() + Vec2(money_sprite->getWidth()*0.9F
			+ (i - (bet_money_response.size() - 1)*0.5f)*spriteXu->getWidth(), 0);
		addCoin(count, value, fromPos, toPos);
	}
}

void ThreeCardsScene::addCoin(int numberCard, int cardType, Vec2 point1, Vec2 point2){
	auto callFunc = CallFunc::create([=]{
		vector<MSprite*> sps;
		for (int i = 0; i<numberCard; i++){
			auto spriteXu = MSprite::create(StringUtils::format("ba_cay/icon_chip%d.png", cardType));
			spriteXu->setPosition(point2);
			auto move = MoveBy::create(0.05f, Vec2(0, 0.2f*spriteXu->getHeight()*i));
			spriteXu->runAction(Sequence::create(DelayTime::create(i*0.05f), move, NULL));
			sps.push_back(spriteXu);
		}
		sprites.push_back(sps);
		for (vector<MSprite*> sprite_xu : sprites){
			for (MSprite* sprite : sprite_xu){
				if (sprite->getParent() == nullptr){
					this->addChild(sprite);
				}
			}
		}
	});

	auto callFunc2 = CallFunc::create([&]{
		//TODO: HungLe
		for (vector<MSprite*> sps : sprites){
			for (MSprite* sprite : sps){
				sprite->removeFromParentAndCleanup(true);
			}
		}
		sprites.clear();
	});

	auto sprite_xu = MSprite::create(StringUtils::format("ba_cay/icon_chip%d.png", cardType));
	sprite_xu->setPosition(point1);
	sprite_xu->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprite_xu->runAction(Sequence::create(MoveTo::create(0.5f, point2), callFunc2, callFunc, RemoveSelf::create(), NULL));
	this->addChild(sprite_xu);
}

void ThreeCardsScene::preparenewMatchHandler() {
    BINPrepareNewMatchResponse *response = (BINPrepareNewMatchResponse*)
        Common::getInstance()->checkEvent(NetworkManager::PREPARE_NEW_MATCH);
    if (response != 0) {
        CCLOG("prepare new match response: %s", response->DebugString().c_str());

        if (response->responsecode()){
            
			sprites.clear();

			//clear carg_tag 
			for (int i = 0; i < card_tag.size(); i++) {
				if (card_tag[i]->getParent() != NULL)
					card_tag[i]->removeFromParentAndCleanup(true);
			}
			card_tag.clear();

			//clear card in avatar
			for (int i = 0; i < avatars.size(); i++) {
				avatars[i]->clear();
				avatars[i]->setBetMoney(0);
				avatars[i]->hideCard();
			}

			hiddenBetBarier();  //an cuoc bien

			totalUnionMoney = 0;

			txt_tien_ga->setString(totalUnionMoney != 0 ? StringUtils::format("%d", totalUnionMoney) : "");
			txt_tien_ga->setPosition(Vec2(money_sprite->getWidth() / 2 - txt_tien_ga->getWidth() / 2,
				money_sprite->getHeight() / 2 - txt_tien_ga->getHeight() / 2));

            Avatar* avatar = findAvatarOfPlayer(getOwnerUserId());  //avatar chuong
            if (avatar != 0 && response->countdowntimer() > 0){
                avatar->updateProgressCircleBar(100, response->countdowntimer());
            }
        }

        if (response->has_message()){
            showToast(response->message().c_str(), 2);
        }
    }
}

vector<pair<int, vector<int>>> ThreeCardsScene::parseCardValue(std::string
    json_value) {
    vector<pair<int, vector<int>>> result;
    try {
        Document document;
        document.Parse(json_value.c_str());
        for (rapidjson::Value::ConstMemberIterator itr = document.MemberBegin();
            itr != document.MemberEnd(); ++itr) {
            string val = itr->value.GetString();
            vector<int> card_values = Common::getInstance()->convertStringsToInt(Common::getInstance()
                ->split(val, ','));
            int user_id = Common::getInstance()->convertStringToInt(itr->name.GetString());
            result.push_back(make_pair(user_id, card_values));
        }
    }
    catch (...) {
        CCLOG("exception");
        result.clear();
    }

    return result;
}

//show chuong: userId la chuong moi
void ThreeCardsScene::showChuong(int userId){
	for (int i = 0; i < avatars.size(); i++){
		if (avatars[i]->getPlayerId() == userId){  //neu la chuong
			avatars[i]->showChuong(true);
			avatars[i]->setBetMoney(0);
		}
		else {
			avatars[i]->showChuong(false);
		}
	}
}

vector<pair<int, bool>> ThreeCardsScene::parseKeyBoolValue(std::string json_value){
	vector<pair<int, bool>> result;
	try {
		Document document;
		document.Parse(json_value.c_str());
		for (rapidjson::Value::ConstMemberIterator itr = document.MemberBegin();
			itr != document.MemberEnd(); ++itr) {
			bool val = itr->value.GetBool();
			int user_id = Common::getInstance()->convertStringToInt(itr->name.GetString());
			result.push_back(make_pair(user_id, val));
		}
	}
	catch (...) {
		CCLOG("exception");
		result.clear();
	}

	return result;
}

vector<pair<int, int>> ThreeCardsScene::parseKeyIntValue(std::string json_value){
	vector<pair<int, int>> result;
	try {
		Document document;
		document.Parse(json_value.c_str());
		for (rapidjson::Value::ConstMemberIterator itr = document.MemberBegin();
			itr != document.MemberEnd(); ++itr) {
			int val = itr->value.GetInt();
			int user_id = Common::getInstance()->convertStringToInt(itr->name.GetString());
			result.push_back(make_pair(user_id, val));
		}
	}
	catch (...) {
		CCLOG("exception");
		result.clear();
	}

	return result;
}

void ThreeCardsScene::turnHandler() {
    BINTurnResponse *response = (BINTurnResponse *)Common::getInstance()
        ->checkEvent(NetworkManager::TURN);
    if (response != 0) {
        CCLOG("turn response: %s", response->DebugString().c_str());
		if (response->has_message()){
			showToast(response->message().c_str(), 2);
		}

		if (response->responsecode()){
			//handle current cards, flip cards
			if (response->args_size() > 0) {
				BINMapFieldEntry entry = response->args(0);
				if (entry.key() == "currentCards") {
					string json_val = entry.value();
					card_values = parseCardValue(json_val);
					if (!card_values.empty()) {
						for (int i = 0; i < card_values.size(); i++) {
							if (Common::getInstance()->getUserId() != card_values[i].first) {
								ThreeCardAvatar* avatar = (ThreeCardAvatar*)findAvatarOfPlayer(card_values[i].first);
								avatar->setCards(card_values[i].second);
								avatar->flipCards();
							}
							else {
								if (findAvatarOfPlayer(Common::getInstance()->getUserId()) != 0){  //xu li show voi nguoi choi
									for (int i = 0; i < card_tag.size(); i++) {
										auto moveTo = MoveTo::create(0.1f*i, MVec2(visibleSize.width / 2 + (i - ((int)card_tag.size() - 1)*0.5f) * cardWidth(),
											5 + btn_message->getHeight()*1.5f + cardWidth() * CARD_RATIO * 0.5f));
										card_tag[i]->runAction(moveTo);
										card_tag[i]->removeEvents();
									}
									if (btn_so_bai->isVisible())
										btn_so_bai->setVisible(false);

									if (btn_lat_bai->isVisible())
										btn_lat_bai->setVisible(false);
								}
							}
						}
					}
				}
			}
		}
	}
}

void ThreeCardsScene::roomOwnerChangedResponseHandler() {
	BINChangeHostResponse* response =
        (BINChangeHostResponse *)Common::getInstance()->checkEvent(NetworkManager::CHANGE_HOST);
    if (response != 0) {
        CCLOG("change host response: %s", response->DebugString().c_str());
        if (response->responsecode()) {
			auto common = Common::getInstance();
			int newOwnerUserId = (int) response->hostid();
			int requestType = response->responsetype();
			if (requestType == ThreeCard_RequestChangeHostType::CHECK_CHANGE_CHUONG){
				//an chuong cu
				ThreeCardAvatar* oldOwner = (ThreeCardAvatar*) findAvatarOfPlayer(getOwnerUserId());
				if (oldOwner != 0){
					oldOwner->showChuong(false);
				}

				common->setOwnerUserId(newOwnerUserId);
				setOwnerUserId(newOwnerUserId);
				is_create_room = common->getUserId() == newOwnerUserId;

				displayLockRoomForOwner(newOwnerUserId);

				//show chuong moi
				ThreeCardAvatar* newOnwer = (ThreeCardAvatar*)findAvatarOfPlayer(newOwnerUserId);
				if (newOnwer != 0){
					newOnwer->showChuong(true);
					newOnwer->setBetMoney(0);
				}

				if (common->getUserId() == newOwnerUserId && lst_player.size() > 1){
					//show popup xac nhan ban chuong
					NodeConfirm<BINBetResponse*> * nodeConfirm = NodeConfirm<BINBetResponse*>::create(this, TITLE_POPUP_CONFIRM, response->message());
					nodeConfirm->setEventOk(OnEvenListener::EVENT_CONFIRM_SELL_CHUONG);
					nodeConfirm->showDlg();
				}
			}
			else if (requestType == ThreeCard_RequestChangeHostType::CONFIRM_SELL_CHUONG){
				if (common->getUserId() != newOwnerUserId){
					//show popup xac nhan mua chuong
					NodeConfirm<BINBetResponse*> * nodeConfirm = NodeConfirm<BINBetResponse*>::create(this, TITLE_POPUP_CONFIRM, response->message());
					nodeConfirm->setEventOk(OnEvenListener::EVENT_CONFIRM_BUY_CHUONG);
					nodeConfirm->showDlg();
				}
			}
			else if (requestType == ThreeCard_RequestChangeHostType::CONFIRM_BUY_CHUONG){
				ThreeCardAvatar* oldOwner = (ThreeCardAvatar*)findAvatarOfPlayer(getOwnerUserId());
				if (oldOwner != 0){
					oldOwner->showChuong(false);
				}

				common->setOwnerUserId(newOwnerUserId);
				setOwnerUserId(newOwnerUserId);
				is_create_room = common->getUserId() == newOwnerUserId;

				displayLockRoomForOwner(newOwnerUserId);

				//show chuong moi
				ThreeCardAvatar* newOnwer = (ThreeCardAvatar*) findAvatarOfPlayer(newOwnerUserId);
				if (newOnwer != 0){
					newOnwer->showChuong(true);
					newOnwer->setBetMoney(0);
				}

				if (common->getUserId() == newOwnerUserId){
					if (response->has_message()) {
						showToast(response->message().c_str(), 2);
					}
				}
			}
		}
	}
}

void ThreeCardsScene::playerExitRoomResponse() {
	BINPlayerExitRoomResponse* _player_exit_room_response =
		(BINPlayerExitRoomResponse *)Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_ROOM);
	if (_player_exit_room_response != 0) {
		CCLOG("exit room player response: %s", _player_exit_room_response->DebugString().c_str());
		if (_player_exit_room_response->responsecode()) {
            if (this->getChildByTag(TAG_TIME_COUNTDOWN) != nullptr){
                this->removeChildByTag(TAG_TIME_COUNTDOWN);
            }
			Player* playerWaiting = findWaiting(_player_exit_room_response->exituserid());
			//xoa nguoi cho di
			if (playerWaiting != 0){
				deleteWaitingPlayer(playerWaiting->getID());

				//hien thi lai danh sach cho len giao dien
				resetListWaiting();
				showWaitingPlayerOnScene(lst_waiting);
			} else {
				int leng = (int)lst_player.size();
				Avatar* avatar;
                
				int ownerUserId = (int)_player_exit_room_response->owneruserid();
				
				if (ownerUserId != 0){
					auto common = Common::getInstance();
					common->setOwnerUserId(ownerUserId);
					setOwnerUserId(ownerUserId);
					is_create_room = common->getUserId() == ownerUserId;
					displayLockRoomForOwner(ownerUserId);

					//show chuong moi
					ThreeCardAvatar* newOnwer = (ThreeCardAvatar*)findAvatarOfPlayer(ownerUserId);
					if (newOnwer != 0){
						newOnwer->showChuong(true);
						newOnwer->setBetMoney(0);
					}
				}
				
				for (int i = 0; i < leng; i++) {
					//xoa nguoi choi khoi ban choi
					string user_id = lst_player[i].getID();
					if (user_id == Common::getInstance()->convertIntToString((int)_player_exit_room_response->exituserid())){
						lst_player.erase(lst_player.begin() + i);

						showInvitePlayer(lst_player.size());  //show moi choi

						if (lst_player.size() == 1){ //tat popup xac nhan ban chuong khi khong con nguoi ban
							dissmissPopupConfirm(); //an cac popup xac nhan di
						}

						avatar = findAvatarOfPlayer(_player_exit_room_response->exituserid());
						//xoa avatar khoi ban choi (khong hien thi nua)
						removeOutTablePlay(avatar);
						//xoa khoi danh sach luu avatars
						avatars.erase(std::remove(avatars.begin(), avatars.end(), avatar), avatars.end());

						/*if (_player_exit_room_response->changeownerroomcd() > 0){
							CCLOG("player exit room time countdown %d", _player_exit_room_response->changeownerroomcd());
							int time_wait = _player_exit_room_response->changeownerroomcd() / 1000;
							auto timerCountDown = MLabel::createCountDown(time_wait);
							timerCountDown->setPosition(width / 2, height / 2);
							this->addChild(timerCountDown);
						}*/
						break;
					}
				}
			}
		}

		if (_player_exit_room_response->has_message()){
			showToast(_player_exit_room_response->message().c_str(), 2);
		}
	}
}

void ThreeCardsScene::playerExitAfterMatchEndResponse() {
	BINPlayerExitAfterMatchEndResponse* exit_room_player_response =
		(BINPlayerExitAfterMatchEndResponse *)Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_AFTER_MATCH_END);
	if (exit_room_player_response != 0) {
		CCLOG("exit room player response: %s", exit_room_player_response->DebugString().c_str());
		if (exit_room_player_response->responsecode()) {
			int leng = (int)lst_player.size();
			for (int i = 0; i < leng; i++) {
				//reset position
				string user_id = lst_player[i].getID();
				if (user_id == Common::getInstance()->convertIntToString((int)exit_room_player_response->exituserid())){
					/*char message[60];
					sprintf(message, "Người chơi %s đăng ký rời bàn chơi", lst_player[i].getName().c_str());
					this->showToast(message, 2);*/

					Avatar* avatar = findAvatarOfPlayer(exit_room_player_response->exituserid());
					if (avatar != 0){
						avatar->showRegisterExitRoom(true);
					}

					
					break;
				}
			}
		}
	}
}

void ThreeCardsScene::playerEnterRoomResponseHandler() {
	BINPlayerEnterRoomResponse *newplayerresponse = (BINPlayerEnterRoomResponse*)
		Common::getInstance()->checkEvent(NetworkManager::PLAYER_ENTER_ROOM);
	if (newplayerresponse != 0) {
		CCLOG("player enter room response: %s", newplayerresponse->DebugString().c_str());
		if (newplayerresponse->responsecode()) {
			ThreeCardPlayer player = convertFromBINPlayer(newplayerresponse->player());

			//neu la nguoi choi
			if (newplayerresponse->enterroomstatus() == PlayerState::PLAYING){
				player_list.push_back(newplayerresponse->player());
				lst_player.push_back(player);

				showInvitePlayer(lst_player.size());  //show moi choi

				int posIndex = -1;
				bool findPos = false;
				for (int i = 0; i < capacity_size; i++){
					findPos = false;
					for (int j = 0; j < avatars.size(); j++){
						if (ThreeCardsScene::AVATARPOS[i] == avatars[j]->getPositionIndex()) {
							findPos = true;
							break;
						}
					}
					if (!findPos) {
						posIndex = i;
						break;
					}
				}
				setPositionPlayer(player, posIndex);

				if (lst_player.size() == 2 && newplayerresponse->changeownerroomcd() > 0) {
					CCLOG("time start match countdown %d", newplayerresponse->changeownerroomcd());
					Avatar* avatar = findAvatarOfPlayer(getOwnerUserId());
					if (avatar != 0){
						avatar->updateProgressCircleBar(100, newplayerresponse->changeownerroomcd());
					}
				}
			}
			else {
				// xu ly voi nguoi cho
				if (newplayerresponse->enterroomstatus() == PlayerState::WAITING){
					lst_waiting.push_back(player);
					//hien thi danh sach nguoi cho len man hinh
					resetListWaiting();
					showWaitingPlayerOnScene(lst_waiting);
				}
			}

			
		}
		else {
			this->showToast(newplayerresponse->message().c_str(), 2);
		}
	}
}

void ThreeCardsScene::readyToPlayResponseHandler(){
	BINReadyToPlayResponse* ready_to_play_response =
		(BINReadyToPlayResponse *) Common::getInstance()->checkEvent(NetworkManager::READY_TO_PLAY);

	if (ready_to_play_response != 0){
		CCLOG("ready to play response: %s", ready_to_play_response->DebugString().c_str());
		if (ready_to_play_response->responsecode()){
			if (Common::getInstance()->getUserId() == ready_to_play_response->readyuserid()){
				btn_san_sang->setVisible(false);
				showBtnWithWatingPlayer(true);
			}

			long long ready_player_id = ready_to_play_response->readyuserid();
			int table_index = ready_to_play_response->tableindex();
			ThreeCardPlayer* player = (ThreeCardPlayer*) findWaiting(ready_player_id);

			if (player != 0){
				//day vao lst playing
				ThreeCardPlayer waiting_player = *player;
				waiting_player.setTableIndex(table_index);
				lst_player.push_back(waiting_player);

				showInvitePlayer(lst_player.size());  //show moi choi

				//remove avatar tren ban choi
				resetDisplayAvatar();
				//dat waiting player len ban choi
				sortListPlayer();
				displayInfoRemainCard(lst_player);

				//xoa khoi lst_waiting
				deleteWaitingPlayer(waiting_player.getID());

				//hien thi lai danh sach cho len giao dien
				resetListWaiting();
				showWaitingPlayerOnScene(lst_waiting);
			}
		}
		else {
			this->showToast(ready_to_play_response->message().c_str(), 2);
		}
	}
}

void ThreeCardsScene::matchEndResponseHandler() {
    BINMatchEndResponse* response = (BINMatchEndResponse*)Common::getInstance()
        ->checkEvent(NetworkManager::MATCH_END);
    if (response != 0) {
        CCLOG("match end response: %s", response->DebugString().c_str());
		if (response->responsecode()) {
			handleWinLose(response);

			for (int i = 0; i < avatars.size(); i++){
				avatars[i]->showGa(false);
			}

			if (response->textemoticons_size() > 0){
				this->showToast(response->textemoticons(0).message().c_str(), 2);
			}

            /*totalUnionMoney = 0;
            txt_tien_ga->setString(totalUnionMoney != 0 ? StringUtils::format("%d", totalUnionMoney) : "");
            txt_tien_ga->setPosition(Vec2(money_sprite->getWidth() / 2 - txt_tien_ga->getWidth() / 2,
                money_sprite->getHeight() / 2 - txt_tien_ga->getHeight() / 2));*/
		}

		if (response->has_message()){
			showToast(response->message().c_str(), 2);
		}
    }
}
