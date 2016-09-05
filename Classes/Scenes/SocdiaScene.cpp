//
//  SocdiaScene.cpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 8/1/16.
//
//

#include <algorithm>

#include "SocdiaScene.hpp"

using namespace cocos2d;
using namespace rapidjson;
using namespace std;

#define CLOCK 1

Scene* SocdiaScene::createScene(int roomIndex, vector<BINPlayer> playerList, vector<BINPlayer> waitingPlayerList,
                                bool isCreateRoom, int gameTag, bool isDisplayRoomList, bool passwordRequired,
                                bool isVipRoom, int minBet, BINEnterRoomResponse *reEnterRoomRS, string roomConfig) {
    auto scene = Scene::create();
    auto layer = SocdiaScene::create();
    layer->setRoomIndex(roomIndex);
    layer->setVipRoom(isVipRoom);
    layer->setPassWordRequired(passwordRequired);
    layer->setPlayerList(playerList);
    layer->setWaitingPlayerList(waitingPlayerList);
    layer->setCreateRoom(isCreateRoom);
    layer->setMinBet(minBet);
    layer->setEnterRoomResponse(reEnterRoomRS);
    layer->setOwnerUserId(Common::getInstance()->getOwnerUserId());
    layer->setBetsRatio(roomConfig);
    layer->layoutInit();
    layer->initGame();

    scene->addChild(layer);
    return scene;
}

bool SocdiaScene::init() {
    if (!PlayScene::init()) {
        return false;
    }
    capacity_size = 30;
    this->scheduleUpdate();
    return true;
}

void SocdiaScene::initGame() {
	avatar_position = { 0, 8, 4, 2, 9, 7, 5, 6, 3, 1 };

	if (is_create_room){
		int current_user_id = Common::getInstance()->getUserId();
		setOwnerUserId(current_user_id);
	}

	setListPlayerFromParams(player_list, waiting_player_list);

	showNumberPlayerOutsite();
	/*if (enter_room_response != 0) {
		handleReEnterRoom(enter_room_response);
	}*/
}

bool SocdiaScene::isUserPlaying() {
	int user_id = Common::getInstance()->getUserId();
	Player* player = findPlayer(user_id);
	if (player != 0){
		return true;
	}
	return false;
}

XocDiaPlayer SocdiaScene::convertFromBINPlayer(BINPlayer binplayer) {
	char buffer[20];
	sprintf(buffer, "%lld", binplayer.userid());
	std::string uid = std::string(buffer);

	int numberCard = 0;

	XocDiaPlayer player = XocDiaPlayer(binplayer.username(), uid, numberCard, binplayer.cash(),
		binplayer.gold(), 0, binplayer.tableindex(), binplayer.avatarid());
	return player;
}

void SocdiaScene::setListPlayerFromParams(std::vector<BINPlayer> player_list, std::vector<BINPlayer> waiting_player_list) {
	if (!lst_player.empty()) lst_player.clear();
	if (!lst_waiting.empty()) lst_waiting.clear();

	//test
	/*BINPlayer player1 = BINPlayer();
	player1.set_userid(10001);
	player1.set_username("cuongdk");
	player1.set_avatarid(100002);
	player1.set_gold(1000);
	player1.set_cash(2000);

	BINPlayer player2 = BINPlayer();
	player2.set_userid(10001);
	player2.set_username("cuongdk1");
	player2.set_avatarid(100001);
	player2.set_gold(1500);
	player2.set_cash(2500);

	BINPlayer player3 = BINPlayer();
	player3.set_userid(10001);
	player3.set_username("cuongdk2");
	player3.set_avatarid(100000);
	player3.set_gold(2000);
	player3.set_cash(3000);

	BINPlayer player4 = BINPlayer();
	player4.set_userid(10001);
	player4.set_username("cuongdk3");
	player4.set_avatarid(100003);
	player4.set_gold(2500);
	player4.set_cash(3500);

	BINPlayer player5 = BINPlayer();
	player5.set_userid(10001);
	player5.set_username("cuongdk4");
	player5.set_avatarid(100001);
	player5.set_gold(3000);
	player5.set_cash(4000);

	BINPlayer player6 = BINPlayer();
	player6.set_userid(10001);
	player6.set_username("cuongdk5");
	player6.set_avatarid(100002);
	player6.set_gold(3500);
	player6.set_cash(4500);

	BINPlayer player7 = BINPlayer();
	player7.set_userid(10001);
	player7.set_username("cuongdk6");
	player7.set_avatarid(100000);
	player7.set_gold(5500);
	player7.set_cash(6500);

	BINPlayer player8 = BINPlayer();
	player8.set_userid(10001);
	player8.set_username("cuongdk7");
	player8.set_avatarid(100002);
	player8.set_gold(6000);
	player8.set_cash(7000);

	BINPlayer player9 = BINPlayer();
	player9.set_userid(10001);
	player9.set_username("cuongdk9");
	player9.set_avatarid(100002);
	player9.set_gold(6500);
	player9.set_cash(7500);

	BINPlayer player10 = BINPlayer();
	player10.set_userid(10004);
	player10.set_username("cuongdk10");
	player10.set_avatarid(100002);
	player10.set_gold(8000);
	player10.set_cash(9000);

	player_list.push_back(player1);
	player_list.push_back(player2);
	player_list.push_back(player3);
	player_list.push_back(player4);
	player_list.push_back(player5);
	player_list.push_back(player6);
	player_list.push_back(player7);
	player_list.push_back(player8);
	player_list.push_back(player9);
	player_list.push_back(player10);*/
	
	//end

	for (BINPlayer player : player_list) {
		lst_player.push_back(convertFromBINPlayer(player));
	}

	for (BINPlayer player : waiting_player_list) {
		lst_waiting.push_back(convertFromBINPlayer(player));
	}

	if (isUserPlaying()){
		showInvitePlayer(lst_player.size());
		btn_san_sang->setVisible(false);
	}
	else {
		showBtnWithWatingPlayer(false);
	}

	//showWaitingPlayerOnScene(lst_waiting);

	CCLOG("-------------------------truoc sort");
	for (int i = 0; i < lst_player.size(); i ++){
		CCLOG("%s - %lld",lst_player[i].getName().c_str(), lst_player[i].getGold());
	}

	sortListPlayer();

	CCLOG("-------------------------sau sort");
	for (int i = 0; i < lst_player.size(); i++){
		CCLOG("%s - %lld", lst_player[i].getName().c_str(), lst_player[i].getGold());
	}

	displayInfoPlayer(lst_player);
}

void SocdiaScene::sortListPlayer() {
	std::string current_user_id = StringUtils::format("%d", Common::getInstance()->getUserId());
	XocDiaPlayer tmp;
	if (lst_player.size() > 1){
		if (is_vip_room){
			for (int i = 0; i < lst_player.size(); i++){
				for (int j = i + 1; j < lst_player.size(); j++){
					if (lst_player[j].getCash() > lst_player[i].getCash()){
						tmp = lst_player[i];
						lst_player[i] = lst_player[j];
						lst_player[j] = tmp;
					}
				}
			}
		}
		else {
			for (int i = 0; i < lst_player.size(); i++){
				for (int j = i + 1; j < lst_player.size(); j++){
					if (lst_player[j].getGold() > lst_player[i].getGold()){
						tmp = lst_player[i];
						lst_player[i] = lst_player[j];
						lst_player[j] = tmp;
					}
				}
			}
		}
		for (int i = 1; i < lst_player.size(); i++){
			if (lst_player[i].getID() == current_user_id){
				tmp = lst_player[0];
				lst_player[0] = lst_player[i];
				lst_player[i] = tmp;
				break;
			}
		}
	}
}

void SocdiaScene::displayInfoPlayer(std::vector<XocDiaPlayer>& lst_player) {
	int len = (int) lst_player.size();
	len = (len > NUMBER_PLAYER_ON_TABLE) ? NUMBER_PLAYER_ON_TABLE : len;
	for (int i = 0; i < len; i++) {
		setPositionPlayer(lst_player[i], i);
	}
}

void SocdiaScene::layoutInit() {
	PlayScene::initMenu();

    setBetRatio(1);
	auto common = Common::getInstance();
	_totalMoney = is_vip_room ? common->getCash() : common->getGold();

	_canBet = false;
	int padding = 15;
	std::string formatText = "%d:%d";
	tag_chip = { TAG_XOCDIA_BTN_X1, TAG_XOCDIA_BTN_X5, TAG_XOCDIA_BTN_X25, TAG_XOCDIA_BTN_X50 };

	auto bkgTable = MSprite::create("ba_cay/ba_cay_table.png");
	bkgTable->setScale(width*0.75f / bkgTable->getWidth());
	bkgTable->setContentSize(Size(width*0.75f, bkgTable->getHeight()*bkgTable->getScale()));
	bkgTable->setPosition(Point(origin.x + visibleSize.width / 2 - bkgTable->getWidth() / 2,
		origin.y + visibleSize.height / 2 - bkgTable->getHeight() / 2));
	this->addChild(bkgTable);

	girl = MSprite::create("ba_cay/ba_cay_girl.png");
    girl->setAnchorPoint(Point::ANCHOR_MIDDLE);
	girl->setScale(bkgTable->getScale());
	girl->setPosition(Vec2(bkgTable->getPosition().x + bkgTable->getWidth() / 2,
		bkgTable->getPosition().y + bkgTable->getHeight() - girl->getHeight() * 3 / 8 + girl->getHeight()/2));
	this->addChild(girl);

	_btnXinlamcai = MButton::create(XOCDIA_BTN_XINCAI, TXT_XOCDIA_XINCAI, 30, TAG_XOCDIA_BTN_XINCAI);
	_btnXinlamcai->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	_btnXinlamcai->setPosition(Vec2(originX + width / 2,
                                    bkgTable->getPosition().y + bkgTable->getHeight() - girl->getHeight() * 3 / 8));
	_btnXinlamcai->setTitleFontSize(_btnXinlamcai->getHeight() / 2);
	_btnXinlamcai->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
	this->addChild(_btnXinlamcai);
    
    _btnHuylamcai = MButton::create(XOCDIA_BTN_XINCAI, TXT_XOCDIA_HUYCAI, 30, TAG_XOCDIA_BTN_HUYCAI);
    _btnHuylamcai->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    _btnHuylamcai->setPosition(_btnXinlamcai->getPosition());
    _btnHuylamcai->setTitleFontSize(_btnHuylamcai->getHeight() / 2);
    _btnHuylamcai->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    this->addChild(_btnHuylamcai);
    _btnHuylamcai->setVisible(false);

	_btnCuaChan = MButton::create(XOCDIA_BTN_CUOC, TAG_XOCDIA_CUA_CHAN);
	_btnCuaChan->setPosition(MVec2(width / 2 - _btnCuaChan->getWidth(), height / 2));
    _btnCuaChan->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    
    _cuaChantotalBet = MLabel::create("0", 12);
    _cuaChantotalBet->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _cuaChantotalBet->setPosition(Vec2(_btnCuaChan->getPosition().x + _btnCuaChan->getContentSize().width / 2,
                                       _btnCuaChan->getPosition().y + _btnCuaChan->getContentSize().height));
    
    _cuaChanPlayBet = MLabel::create("0", 12);
    _cuaChanPlayBet->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    _cuaChanPlayBet->setPosition(Vec2(_btnCuaChan->getPositionX() + _btnCuaChan->getContentSize().width / 2,
                                      _btnCuaChan->getPositionY()));
    
	_btnCuaLe = MButton::create(XOCDIA_BTN_CUOC, TAG_XOCDIA_CUA_LE);
	_btnCuaLe->setPosition(MVec2(width / 2 + _btnCuaLe->getWidth(), height / 2));
    _btnCuaLe->setFlippedX(true);
    _btnCuaLe->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    
    _cuaLeTotalBet = MLabel::create("0", 12);
    _cuaLeTotalBet->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _cuaLeTotalBet->setPosition(Vec2(_btnCuaLe->getPositionX() - _btnCuaLe->getContentSize().width / 2,
                                     _btnCuaLe->getPositionY() + _btnCuaLe->getContentSize().height));
    
    _cuaLePlayBet = MLabel::create("0", 12);
    _cuaLePlayBet->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    _cuaLePlayBet->setPosition(Vec2(_btnCuaLe->getPositionX() - _btnCuaLe->getContentSize().width / 2,
                                    _btnCuaLe->getPositionY()));
    
    dia = MSprite::create(XOCDIA_DIA);
    dia->setPosition(MVec2(width / 2, height / 2));
    dia->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    
    bat = MSprite::create(XOCDIA_BAT);
    bat->setPosition(Vec2(dia->getPosition().x, dia->getPosition().y + dia->getContentSize().height / 2));
    bat->setAnchorPoint(Point::ANCHOR_MIDDLE);
    batPos = bat->getPosition();
    
    auto firstchip = MSprite::create(XOCDIA_NUT_DO);
    firstchip->setPosition(Vec2(dia->getPosition().x - dia->getContentSize().width / 6,
                                 dia->getPosition().y + dia->getContentSize().height * 2 / 3));
    _lstResult.push_back(firstchip);
    
    auto secondchip = MSprite::create(XOCDIA_NUT_DO);
    secondchip->setPosition(Vec2(dia->getPosition().x + dia->getContentSize().width / 6,
                                 dia->getPosition().y + dia->getContentSize().height * 2 / 3));
    _lstResult.push_back(secondchip);
    
    auto thirdchip = MSprite::create(XOCDIA_NUT_DO);
    thirdchip->setPosition(Vec2(dia->getPosition().x - dia->getContentSize().width / 6,
                                dia->getPosition().y + dia->getContentSize().height / 3));
    _lstResult.push_back(thirdchip);
    
    auto fourthchip = MSprite::create(XOCDIA_NUT_DO);
    fourthchip->setPosition(Vec2(dia->getPosition().x + dia->getContentSize().width / 6,
                                 dia->getPosition().y + dia->getContentSize().height / 3));
    _lstResult.push_back(fourthchip);
    
    float sizeBtnCuoc = (_btnCuaChan->getWidth() * 2 - 3 * padding) / 4;
    
    _btnCua4Trang = MButton::create(XOCDIA_BTN_KHUNGCUOC, TAG_XOCDIA_CUA_4_TRANG);
	_btnCua4Trang->setScaleX(sizeBtnCuoc / _btnCua4Trang->getWidth());
	_btnCua4Trang->setContentSize(Size(sizeBtnCuoc / _btnCua4Trang->getWidth(), _btnCua4Trang->getHeight()));
	_btnCua4Trang->setPosition(Vec2(_btnCuaChan->getPosition().x,
                                    originY + height / 2 - 5.0f * _btnCua4Trang->getHeight() / 4));
    _btnCua4Trang->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    
    _cua4TrangTotalBet = MLabel::create("0", 12);
    _cua4TrangTotalBet->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _cua4TrangTotalBet->setPosition(Vec2(_btnCua4Trang->getPositionX() + _btnCua4Trang->getContentSize().width / 2,
                                         _btnCua4Trang->getPositionY() + _btnCua4Trang->getContentSize().height));
    _cua4TrangPlayBet = MLabel::create("0", 12);
    _cua4TrangPlayBet->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    _cua4TrangPlayBet->setPosition(_btnCua4Trang->getPositionX() + _btnCua4Trang->getContentSize().width / 2,
                                   _btnCua4Trang->getPositionY());
    
	_btnCua0Trang = MButton::create(XOCDIA_BTN_KHUNGCUOC, TAG_XOCDIA_CUA_0_TRANG);
	_btnCua0Trang->setScaleX(_btnCua4Trang->getScaleX());
	_btnCua0Trang->setContentSize(_btnCua4Trang->getContentSize());
	_btnCua0Trang->setPosition(Vec2(_btnCua4Trang->getPosition().x + sizeBtnCuoc + padding,
                                    _btnCua4Trang->getPosition().y));
	_btnCua0Trang->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    
    _cua0TrangTotalBet = MLabel::create("0", 12);
    _cua0TrangTotalBet->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _cua0TrangTotalBet->setPosition(Vec2(_btnCua0Trang->getPositionX() + _btnCua0Trang->getContentSize().width /2,
                                         _btnCua0Trang->getPositionY() + _btnCua0Trang->getContentSize().height));
    
    _cua0TrangPlayBet = MLabel::create("0", 12);
    _cua0TrangPlayBet->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    _cua0TrangPlayBet->setPosition(_btnCua0Trang->getPositionX() + _btnCua0Trang->getContentSize().width / 2,
                                   _btnCua0Trang->getPositionY());

	_btnCua1Trang = MButton::create(XOCDIA_BTN_KHUNGCUOC, TAG_XOCDIA_CUA_1_TRANG);
	_btnCua1Trang->setScaleX(_btnCua4Trang->getScaleX());
	_btnCua1Trang->setContentSize(_btnCua4Trang->getContentSize());
	_btnCua1Trang->setPosition(Vec2(_btnCua0Trang->getPosition().x + sizeBtnCuoc + padding,
                                    _btnCua4Trang->getPosition().y));
	_btnCua1Trang->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    
    _cua1TrangTotalBet = MLabel::create("0", 12);
    _cua1TrangTotalBet->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _cua1TrangTotalBet->setPosition(Vec2(_btnCua1Trang->getPositionX() + _btnCua1Trang->getContentSize().width / 2,
                                         _btnCua1Trang->getPositionY() + _btnCua1Trang->getContentSize().height));
    
    _cua1TrangPlayBet = MLabel::create("0", 12);
    _cua1TrangPlayBet->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    _cua1TrangPlayBet->setPosition(Vec2(_btnCua1Trang->getPositionX() + _btnCua1Trang->getContentSize().width /2,
                                        _btnCua1Trang->getPositionY()));

	_btnCua3Trang = MButton::create(XOCDIA_BTN_KHUNGCUOC, TAG_XOCDIA_CUA_3_TRANG);
	_btnCua3Trang->setScaleX(_btnCua4Trang->getScaleX());
	_btnCua3Trang->setContentSize(_btnCua4Trang->getContentSize());
	_btnCua3Trang->setPosition(Vec2(_btnCua1Trang->getPosition().x + sizeBtnCuoc + padding,
                                    _btnCua4Trang->getPosition().y));
    _btnCua3Trang->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    
    _cua3TrangTotalBet = MLabel::create("0", 12);
    _cua3TrangTotalBet->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _cua3TrangTotalBet->setPosition(Vec2(_btnCua3Trang->getPositionX() + _btnCua3Trang->getContentSize().width / 2,
                                         _btnCua3Trang->getPositionY() + _btnCua3Trang->getContentSize().height));
    
    _cua3TrangPlayBet = MLabel::create("0", 12);
    _cua3TrangPlayBet->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    _cua3TrangPlayBet->setPosition(Vec2(_btnCua3Trang->getPositionX() + _btnCua3Trang->getContentSize().width / 2,
                                        _btnCua3Trang->getPositionY()));
    
	_labelCuaChan = MLabel::create(XOCDIA_TEXT_CHAN, _btnCuaChan->getHeight() / 3, Color3B::WHITE);
	_labelCuaChan->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_labelCuaChan->setPosition(Vec2(_btnCuaChan->getPosition().x + _btnCuaChan->getWidth() / 2,
                                   _btnCuaChan->getPosition().y + _btnCuaChan->getHeight() / 2));

	_labelCuaLe = MLabel::create(XOCDIA_TEXT_LE, _btnCuaLe->getHeight() / 3, Color3B::WHITE);
	_labelCuaLe->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_labelCuaLe->setPosition(Vec2(_btnCuaLe->getPosition().x - _btnCuaLe->getWidth() / 2,
                                 _btnCuaLe->getPosition().y + _btnCuaLe->getHeight() / 2));

	_labelCua4Trang = MLabel::create(StringUtils::format(formatText.c_str(), 1, getTypeBetRatio(0)),
                                     _btnCua4Trang->getHeight() / 5, Color3B::WHITE);
	_labelCua4Trang->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_labelCua4Trang->setPosition(Vec2(_btnCua4Trang->getPosition().x + _btnCua4Trang->getWidth() / 2,
                                     _btnCua4Trang->getPosition().y + _btnCua4Trang->getHeight() / 2));
	
	_labelCua0Trang = MLabel::create(StringUtils::format(formatText.c_str(), 1, getTypeBetRatio(4)),
		_btnCua0Trang->getHeight() / 5, Color3B::WHITE);
	_labelCua0Trang->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_labelCua0Trang->setPosition(Vec2(_btnCua0Trang->getPosition().x + _btnCua0Trang->getWidth() / 2,
		_btnCua0Trang->getPosition().y + _btnCua0Trang->getHeight() / 2));

	_labelCua3Trang = MLabel::create(StringUtils::format(formatText.c_str(), 1, getTypeBetRatio(1)),
                                     _btnCua3Trang->getHeight() / 5, Color3B::WHITE);
	_labelCua3Trang->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_labelCua3Trang->setPosition(Vec2(_btnCua3Trang->getPosition().x + _btnCua3Trang->getWidth() / 2,
		_btnCua3Trang->getPosition().y + _btnCua3Trang->getHeight() / 2));

	_labelCua1Trang = MLabel::create(StringUtils::format(formatText.c_str(), 1, getTypeBetRatio(3)),
                                     _btnCua1Trang->getHeight() / 5, Color3B::WHITE);
	_labelCua1Trang->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_labelCua1Trang->setPosition(Vec2(_btnCua1Trang->getPosition().x + _btnCua1Trang->getWidth() / 2,
                                     _btnCua1Trang->getPosition().y + _btnCua1Trang->getHeight() / 2));

	auto bg4Trang = MSprite::create(XOCDIA_BG_4TRANG);
	bg4Trang->setPosition(Vec2(_btnCua4Trang->getPosition().x - bg4Trang->getWidth() / 2,
		_btnCua4Trang->getPosition().y + _btnCua4Trang->getHeight() / 2 - bg4Trang->getHeight() / 2));

	auto bg3Trang = MSprite::create(XOCDIA_BG_3TRANG);
	bg3Trang->setPosition(Vec2(_btnCua3Trang->getPosition().x - bg3Trang->getWidth() / 2,
		_btnCua3Trang->getPosition().y + _btnCua3Trang->getHeight() / 2 - bg3Trang->getHeight() / 2));

	auto bg1Trang = MSprite::create(XOCDIA_BG_1TRANG);
	bg1Trang->setPosition(Vec2(_btnCua1Trang->getPosition().x - bg1Trang->getWidth() / 2,
		_btnCua1Trang->getPosition().y + _btnCua1Trang->getHeight() / 2 - bg1Trang->getHeight() / 2));

	auto bg0Trang = MSprite::create(XOCDIA_BG_0TRANG);
	bg0Trang->setPosition(Vec2(_btnCua0Trang->getPosition().x - bg0Trang->getWidth() / 2,
		_btnCua0Trang->getPosition().y + _btnCua0Trang->getHeight() / 2 - bg0Trang->getHeight() / 2));
	//end dat cua

	float widthBtnHandler = ( originX + width / 2 - btn_message->getPosition().x - 4 * padding ) / 3;

	_btnDatlai = MButton::create(XOCDIA_BTN_HANDLER, "Đặt Lại", 15, TAG_XOCDIA_BTN_DATLAI);
	_btnDatlai->setPosition(Vec2(btn_message->getPosition().x - _btnDatlai->getWidth() - padding,
                                 btn_message->getPosition().y + btn_message->getHeight() / 2 - _btnDatlai->getHeight()/2));
    _btnDatlai->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    
	_btnHuyCuoc = MButton::create(XOCDIA_BTN_HANDLER, "Huỷ Cược", 15, TAG_XOCDIA_BTN_HUYCUOC);
	_btnHuyCuoc->setPosition(Vec2(_btnDatlai->getPosition().x - _btnHuyCuoc->getWidth() - padding,
                                  _btnDatlai->getPosition().y));
    _btnHuyCuoc->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    
	_btnGapDoi = MButton::create(XOCDIA_BTN_HANDLER, "Gấp Đôi", 15, TAG_XOCDIA_BTN_GAPDOI);
	_btnGapDoi->setPosition(Vec2(_btnHuyCuoc->getPosition().x - _btnGapDoi->getWidth() - padding,
                                 _btnDatlai->getPosition().y));
    _btnGapDoi->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
    
	//chip
	bg_chip = MSprite::create(XOCDIA_DATCHIP);
	bg_chip->setPosition(Vec2(originX + width / 2, _btnDatlai->getPosition().y + _btnDatlai->getHeight() + 10));

	_btnX1 = MButton::create(XOCDIA_CHIP1, TAG_XOCDIA_BTN_X1);
	_btnX1->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_btnX1->setPosition(Vec2(bg_chip->getWidth() / 8, bg_chip->getHeight()/2));
	_btnX1->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::chipCallBack, this));
    
	_btnX5 = MButton::create(XOCDIA_CHIP5, TAG_XOCDIA_BTN_X5);
	_btnX5->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_btnX5->setPosition(Vec2(3 * bg_chip->getWidth() / 8, bg_chip->getHeight() / 2));
	_btnX5->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::chipCallBack, this));
    
	_btnX25 = MButton::create(XOCDIA_CHIP25, TAG_XOCDIA_BTN_X25);
	_btnX25->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_btnX25->setPosition(Vec2(5 * bg_chip->getWidth() / 8, bg_chip->getHeight() / 2));
	_btnX25->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::chipCallBack, this));
    
	_btnX50 = MButton::create(XOCDIA_CHIP50, TAG_XOCDIA_BTN_X50);
	_btnX50->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_btnX50->setPosition(Vec2(7 * bg_chip->getWidth() / 8, bg_chip->getHeight() / 2));
	_btnX50->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::chipCallBack, this));

	//end chip

	//so nguoi choi
	auto bg_songuoixem = MButton::create(IC_SONGUOIXEM, TAG_XOCDIA_OUTSITE_PLAYER);
	bg_songuoixem->setPosition(Vec2(btn_caidat->getPosition().x, btn_caidat->getPosition().y - bg_songuoixem->getHeight() - 5));
	bg_songuoixem->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));
	this->addChild(bg_songuoixem);

	ic_songuoixem = MSprite::create(BG_SONGUOIXEM);
	ic_songuoixem->setPosition(Vec2(bg_songuoixem->getPosition().x - ic_songuoixem->getWidth() / 2,
		bg_songuoixem->getPosition().y + bg_songuoixem->getHeight() - ic_songuoixem->getHeight()));
	this->addChild(ic_songuoixem);

	numberPlayerOutsite = MLabel::create("0", ic_songuoixem->getHeight()/2, Color3B::WHITE);
	numberPlayerOutsite->setAnchorPoint(Point::ANCHOR_MIDDLE);
	numberPlayerOutsite->setPosition(Vec2(ic_songuoixem->getWidth() / 2, ic_songuoixem->getHeight()/2));
	ic_songuoixem->addChild(numberPlayerOutsite);
    
    //clock
    sprite_clock = MSprite::createwithFrameName("clock_2.png");
    sprite_clock->setAnchorPoint(Point::ANCHOR_MIDDLE);
    sprite_clock->setPosition(Vec2(originX + width - 15*2 - sprite_clock->getWidth()/2,
                                   15 + btn_message->getHeight() + sprite_clock->getHeight()/2));
    this->addChild(sprite_clock);
    
    //timerCountDown = MLabel::create(StringUtils::format("%d",5),
    //                                     sprite_clock->getWidth()*0.25f);
    timerCountDown = MLabel::createClockCountDown(5);
    timerCountDown->setPosition(sprite_clock->getWidth()/2,
                                sprite_clock->getHeight()/2 + timerCountDown->getHeight()*0.25f);
    sprite_clock->addChild(timerCountDown);
    sprite_clock->setVisible(false);
    
	//end so nguoi choi

	//thong ke chan le
	auto bg_total_chanle = MSprite::create(XOCDIA_TOTAL_CHANLE);
	bg_total_chanle->setPosition(MVec2(5,5));

	bg_thongke_chanle = MSprite::create(XOCDIA_THONGKE_CHANLE);
	bg_thongke_chanle->setPosition(Vec2(bg_total_chanle->getPosition().x + bg_total_chanle->getWidth(), originY + 5));

	auto lb_chan = MLabel::create("Chẵn", bg_total_chanle->getHeight()/6, Color3B::RED);
	lb_chan->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	lb_chan->setPosition(Vec2(bg_total_chanle->getWidth() / 2, 3 * bg_total_chanle->getHeight() / 4 + 1));

	auto lb_le = MLabel::create("Lẻ", bg_total_chanle->getHeight() / 6, Color3B::WHITE);
	lb_le->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	lb_le->setPosition(Vec2(bg_total_chanle->getWidth() / 2, bg_total_chanle->getHeight() / 4 + 1));

	lb_value_chan = MLabel::create("0", bg_total_chanle->getHeight() / 6, Color3B::RED);
	lb_value_chan->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	lb_value_chan->setPosition(Vec2(bg_total_chanle->getWidth() / 2, 3 * bg_total_chanle->getHeight() / 4 - 1));

	lb_value_le = MLabel::create("0", bg_total_chanle->getHeight() / 6, Color3B::WHITE);
	lb_value_le->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	lb_value_le->setPosition(Vec2(bg_total_chanle->getWidth() / 2, bg_total_chanle->getHeight() / 4 - 1));

	bg_total_chanle->addChild(lb_chan);
	bg_total_chanle->addChild(lb_le);
	bg_total_chanle->addChild(lb_value_chan);
	bg_total_chanle->addChild(lb_value_le);

	btn_san_sang = MButton::create(BTN_BUTTON, "Sẵn sàng", 25, TAG_BTN_SANSANG);
	btn_san_sang->setPosition(Vec2(btn_message->getPosition().x - btn_san_sang->getWidth() - padding,
		btn_message->getPosition().y));
	btn_san_sang->addTouchEventListener(CC_CALLBACK_2(SocdiaScene::menuCallBack, this));

	//end thong ke chan le

	this->addChild(bg_total_chanle);
	this->addChild(bg_thongke_chanle);

	this->addChild(_btnCuaChan);
	this->addChild(_btnCuaLe);
	this->addChild(_btnCua0Trang);
	this->addChild(_btnCua1Trang);
	this->addChild(_btnCua3Trang);
	this->addChild(_btnCua4Trang);
    this->addChild(_cuaChantotalBet);
    this->addChild(_cuaChanPlayBet);
    this->addChild(_cuaLeTotalBet);
	this->addChild(_cuaLePlayBet);
    this->addChild(_cua0TrangTotalBet);
    this->addChild(_cua0TrangPlayBet);
    this->addChild(_cua1TrangTotalBet);
    this->addChild(_cua1TrangPlayBet);
    this->addChild(_cua3TrangTotalBet);
    this->addChild(_cua3TrangPlayBet);
    this->addChild(_cua4TrangTotalBet);
    this->addChild(_cua4TrangPlayBet);
    this->addChild(_btnDatlai);
	this->addChild(_btnHuyCuoc);
	this->addChild(_btnGapDoi);
	this->addChild(dia);
    for (int i = 0; i < _lstResult.size(); i++) {
        this->addChild(_lstResult[i]);
        _lstResult[i]->setAnchorPoint(Point::ANCHOR_MIDDLE);
    }
    this->addChild(bat);

	this->addChild(bg_chip);
	bg_chip->addChild(_btnX1);
	bg_chip->addChild(_btnX5);
	bg_chip->addChild(_btnX25);
	bg_chip->addChild(_btnX50);

	this->addChild(_labelCuaChan);
	this->addChild(_labelCuaLe);
	this->addChild(_labelCua4Trang);
	this->addChild(_labelCua3Trang);
	this->addChild(_labelCua1Trang);
	this->addChild(_labelCua0Trang);

	this->addChild(bg0Trang);
	this->addChild(bg1Trang);
	this->addChild(bg3Trang);
	this->addChild(bg4Trang);

    this->enableBetButton(_totalMoney);
    this->invisibleBetLable();
    _batZorder = bat->getGlobalZOrder();
	showChipClicked(TAG_XOCDIA_BTN_X1);
}

//show so nguoi choi ngoai nhung nguoi tren ban choi
void SocdiaScene::showNumberPlayerOutsite(){
	int numberPlayer = lst_player.size();
	int numberWaiting = lst_waiting.size();
	numberPlayer = numberPlayer > NUMBER_PLAYER_ON_TABLE ? (numberPlayer + numberWaiting - NUMBER_PLAYER_ON_TABLE) : numberWaiting;
	if (numberPlayer == 0){
		ic_songuoixem->setVisible(false);
	}
	else {
		numberPlayerOutsite->setString(StringUtils::format("%d", numberPlayer));
		numberPlayerOutsite->setPosition(Vec2(ic_songuoixem->getWidth() / 2, ic_songuoixem->getHeight() / 2));
		ic_songuoixem->setVisible(true);
	}
}

//show hieu ung chip khi click x1 x5 x25 x50
void SocdiaScene::showChipClicked(int tagChip){
	int array_chip[4] = {1,5,25,50};
	std::string rs_chip_clicked;
	std::string rs_chip_rotated;
	std::string fomat_rs = "xocdia/btn_chipx%d.png";

	if (tagChip == TAG_XOCDIA_BTN_X1){
		rs_chip_clicked = XOCDIA_CHIP1_CLICK;
		rs_chip_rotated = XOCDIA_CHIP1_ROTATE;
	}
	else if (tagChip  == TAG_XOCDIA_BTN_X5) {
		rs_chip_clicked = XOCDIA_CHIP5_CLICK;
		rs_chip_rotated = XOCDIA_CHIP5_ROTATE;
	}
	else if (tagChip == TAG_XOCDIA_BTN_X25) {
		rs_chip_clicked = XOCDIA_CHIP25_CLICK;
		rs_chip_rotated = XOCDIA_CHIP25_ROTATE;
	}
	else if (tagChip == TAG_XOCDIA_BTN_X50) {
		rs_chip_clicked = XOCDIA_CHIP50_CLICK;
		rs_chip_rotated = XOCDIA_CHIP50_ROTATE;
	}

	auto sprite_chip_rotated = MSprite::create(rs_chip_rotated);
	sprite_chip_rotated->setTag(0);
	sprite_chip_rotated->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprite_chip_rotated->runAction(RepeatForever::create(RotateBy::create(0.25f, 30)));

	for (int i = 0; i < tag_chip.size(); i++){
		auto btn_clicked = ((MButton*) bg_chip->getChildByTag(tag_chip[i]));
		if (btn_clicked->getChildByTag(0) != nullptr){
			btn_clicked->removeChildByTag(0);
			btn_clicked->loadTextureNormal(StringUtils::format(fomat_rs.c_str(), array_chip[i]));
		}

		if (tag_chip[i] == tagChip){
			btn_clicked->loadTextureNormal(rs_chip_clicked);
			sprite_chip_rotated->setPosition(Vec2(btn_clicked->getWidth() / 2, btn_clicked->getHeight()/2));
			btn_clicked->addChild(sprite_chip_rotated);
		}
	}
}

void SocdiaScene::setPositionPlayer(XocDiaPlayer& player, int position) {
	auto avatar = XocDiaAvatar::create();
	int position_index = avatar_position[position];

	string user_name = player.getName();
	string user_id = player.getID();
	long long gold = player.getGold();
	long long cash = player.getCash();

	std::string buffer = StringUtils::format("%lld $", is_vip_room ? cash : gold);
	int image_index = player.getAvatarId();
	CCLOG("image index: %d", image_index);

	avatar->loadAvatar(image_index, user_id, user_name, buffer, roomIndex, minBet);
	avatar->setAvatarPostion(position_index, origin, visibleSize);

	avatars.push_back(avatar);

	if (avatar->getParent() == nullptr)
		this->addChild(avatar);
}

void SocdiaScene::deleteWaitingPlayer(string player_id){
	int k = -1;
	for (int i = 0; i < lst_waiting.size(); i++) {
		if (lst_waiting[i].getID() == player_id) {
			k = i;
		}
	}

	if (k != -1 && !lst_waiting.empty())
		lst_waiting.erase(lst_waiting.begin() + k);
}

void SocdiaScene::resetDisplayAvatar(){
	if (!avatars.empty()){
		for (int i = 0; i < avatars.size(); i++){
			if (avatars[i]->getParent() != nullptr){
				this->removeChild(avatars[i]);
			}
		}
		avatars.clear();
	}
}

//lay ra avatar cua nguoi choi
Avatar* SocdiaScene::findAvatarOfPlayer(long long player_id) {
	for (int i = 0; i < avatars.size(); i++){
		if (avatars[i]->getPlayerId() == player_id){
			return avatars[i];
		}
	}
	return NULL;
}

void SocdiaScene::update(float dt) {
    PlayScene::update(dt);
    
    betHandler();
    
    updateMoneyResponseHandler();
    
    turnResponse();
    
    startMatchResponse();
    
    matchBeginResponse();
    
    prepareNewMatchResponse();

    playerExitRoomAfterMatchResponse();
    
    playerEnterRoomResponse();
    
    playerExitRoomResponse();
    
    matchEndResponseHandler();
    
    hostRegistration();
    
    extraBetHandler();
}

void SocdiaScene::onExit() {
    PlayScene::onExit();
}

Player* SocdiaScene::findPlayer(long long playerID) {
    char c_player_id[50];
    sprintf(c_player_id, "%lld", playerID);
    string s_player_id = string(c_player_id);
    for (int i = 0; i < lst_player.size(); i++) {
		if (lst_player[i].getID() == s_player_id) {
			return &lst_player[i];
        }
    }
    return NULL;
}

void SocdiaScene::updateListMatchResult(int result) {
    if (_lstMatch.size() == 32) {
        _lstMatch.clear();
    }
    _lstMatch.push_back(result);
    int evenCount = 0, oddCount = 0;

	//reset table
	this->removeChildByTag(TAG_XOCDIA_NUT_TRANG_DO);

	//TODO: set lại giá trị của số trận chẵn số trận lẻ
	//TODO: dựa vào vector _lstMatch để reset lại bảng kết quả, màu đỏ là lẻ, trắng là chẵn
	//sắp xếp theo thứ tự từ trên xuống dưới, từ trái qua phải, chưa đủ 32 trận thì để trống

	float widthItemCell = bg_thongke_chanle->getWidth() / 8;
	float heightItemCell = bg_thongke_chanle->getHeight() / 4;
	std::string rs_item;
	for (int i = 0; i < _lstMatch.size(); i++) {
		if (_lstMatch[i] == 0) {
            evenCount++;
			rs_item = XOCDIA_NUT_TRANG;
        } else {
            oddCount++;
			rs_item = XOCDIA_NUT_DO;
        }

		MSprite* item = MSprite::create(rs_item);
		item->setTag(TAG_XOCDIA_NUT_TRANG_DO);
		item->setAnchorPoint(Point::ANCHOR_MIDDLE);
		item->setPosition(Vec2(widthItemCell / 2 + (i / 4) * widthItemCell, (3 - i % 4) * heightItemCell + heightItemCell / 2));
		bg_thongke_chanle->addChild(item);
    }

	lb_value_chan->setString(StringUtils::format("%d", evenCount));
	lb_value_le->setString(StringUtils::format("%d", oddCount));
}

int SocdiaScene::getBetRatio() {
    return this->_betRatio;
}

void SocdiaScene::setBetRatio(int ratio) {
    this->_betRatio = ratio;
}

//tim nguoi cho
Player* SocdiaScene::findWaiting(long long player_id){
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

void SocdiaScene::betHandler() {
    BINBetResponse *response = (BINBetResponse *)Common::getInstance()
    ->checkEvent(NetworkManager::BET);
    if (response != 0) {
        CCLOG("bet response: %s", response->DebugString().c_str());
        if (response->responsecode()) {
            int typeID = response->has_bettype() ? (int)response->bettype() : -1;
            long long sourceUserId = response->has_sourceuserid() ? response->sourceuserid() : 0;
            long long betMoney = response->has_betmoney() ? response->betmoney() : 0;
            Avatar* ava = findAvatarOfPlayer(sourceUserId);
			if (ava != 0 && betMoney != 0) {
                //TODO:vứt đồng tiền gia tri ratio tương ứng từ phía player có id = sourceUserId về phía cửa typeID
                int ratio = (int) betMoney / getMinBet();
				Player* player = findPlayer(sourceUserId);
				if (player != 0){
					if (is_vip_room){
						player->setCash(player->getCash() - betMoney);
					}
					else {
						player->setGold(player->getGold() - betMoney);
					}
				}

				updateMoneyLabel(sourceUserId, -betMoney, is_vip_room ? player->getCash() : player->getGold());
                string a;
                switch (ratio) {
                    case 1:
                        a = XOCDIA_CHIP1_ONBOARD;
                        break;
                    case 5:
                        a = XOCDIA_CHIP5_ONBOARD;
                        break;
                    case 25:
                        a = XOCDIA_CHIP25_ONBOARD;
                        break;
                    case 50:
                        a = XOCDIA_CHIP50_ONBOARD;
                        break;
                    default:
                        break;
                }
                addChipWhenBet(typeID, a, sourceUserId);
            }

            if (response->args_size() != 0) {
                //TODO: set lại tổng tiền của tất cả các user đã đặt vào cửa có giá trị typeID
                string totalAllPlayerBetMoney = response->args(0).value();
                
                string totalBetMoney = " ";
                if (sourceUserId == Common::getInstance()->getUserId()) {
                    totalBetMoney = response->args(1).value();
                    //TODO: set lại tổng tiền của người chơi đã đặt vào cửa có giá trị typeID
                }
                switch (typeID) {
                    case 10:
                        updateBetLabel(_cuaChantotalBet, _cuaChanPlayBet, totalAllPlayerBetMoney, totalBetMoney);
                        break;
                        
                    case 11:
                        updateBetLabel(_cuaLeTotalBet, _cuaLePlayBet, totalAllPlayerBetMoney, totalBetMoney);
                        break;
                        
                    case 0:
                        updateBetLabel(_cua4TrangTotalBet, _cua4TrangPlayBet, totalAllPlayerBetMoney, totalBetMoney);
                        break;
                        
                    case 1:
                        updateBetLabel(_cua3TrangTotalBet, _cua3TrangPlayBet, totalAllPlayerBetMoney, totalBetMoney);
                        break;
                        
                    case 3:
                        updateBetLabel(_cua1TrangTotalBet, _cua1TrangPlayBet, totalAllPlayerBetMoney, totalBetMoney);
                        break;
                    
                    case 4:
                        updateBetLabel(_cua0TrangTotalBet, _cua0TrangPlayBet, totalAllPlayerBetMoney, totalBetMoney);
                        break;

                    default:
                        break;
                }
            }
        } else {
            this->showToast(response->DebugString().c_str(), 2);
        }
    }
}

void SocdiaScene::updateMoneyResponseHandler() {
    BINUpdateMoneyResponse *updatemoneyresponse =
    (BINUpdateMoneyResponse*)Common::getInstance()->checkEvent(NetworkManager::UPDATE_MONEY);
    
    if (updatemoneyresponse != 0) {
        CCLOG("update money response: %s", updatemoneyresponse->DebugString().c_str());
        if (updatemoneyresponse->responsecode()) {
            if (updatemoneyresponse->moneyboxes_size() > 0) {
                BINMoneyBox monneyBox;
                long long originMoney;
                Player* player;
                for (int i = 0; i < updatemoneyresponse->moneyboxes_size(); i++) {
                    bool isCash = monneyBox.iscash();
                    monneyBox = updatemoneyresponse->moneyboxes(i);
                    player = findPlayer(monneyBox.userid());
                    if (player != 0) {
                        originMoney = monneyBox.currentmoney();
						
						player->setMoney(isCash, originMoney);

						updateMoneyLabel(monneyBox.userid(), monneyBox.displaychangemoney(), originMoney);

                        //TODO: animation tiền bay về phía nhà cái thằng thắng
                        Avatar* ava = findAvatarOfPlayer(monneyBox.userid());
                        auto move = MoveTo::create(1, ava->getPosition());
                        int money = monneyBox.displaychangemoney();
                        int count = 0;
                        while (money > getMinBet() * 50) {
                            auto chip50 = MSprite::create(XOCDIA_CHIP50_ONBOARD);
                            chip50->setPosition(girl->getPosition());
                            this->addChild(chip50);
                            chip50->runAction(Sequence::create( DelayTime::create(count * 0.05),move, RemoveSelf::create(), NULL));
                            money = money - getMinBet() * 50;
                            count++;
                        }
                        
                        while (money > getMinBet() * 25) {
                            auto chip25 = MSprite::create(XOCDIA_CHIP25_ONBOARD);
                            chip25->setPosition(girl->getPosition());
                            this->addChild(chip25);
                            chip25->runAction(Sequence::create(DelayTime::create(count * 0.05), move, RemoveSelf::create(), NULL));
                            money = money - getMinBet() * 25;
                            count++;
                        }
                        
                        while (money > getMinBet() * 5) {
                            auto chip5 = MSprite::create(XOCDIA_CHIP5_ONBOARD);
                            chip5->setPosition(girl->getPosition());
                            this->addChild(chip5);
                            chip5->runAction(Sequence::create(DelayTime::create(count * 0.05), move, RemoveSelf::create(), NULL));
                            money = money - getMinBet() * 5;
                            count++;
                        }
                        
                        while (money >getMinBet()) {
                            auto chip1 = MSprite::create(XOCDIA_CHIP1_ONBOARD);
                            chip1->setPosition(girl->getPosition());
                            this->addChild(chip1);
                            chip1->runAction(Sequence::create(DelayTime::create(count * 0.05), move, RemoveSelf::create(), NULL));
                            money = money - getMinBet();
                            count++;
                        }
                        switch (_result) {
                            case 0:
                                removeChip(_lstChipCuaChan);
                                removeChip(_lstChipCua4trang);
                                break;
                                
                            case 1:
                                removeChip(_lstChipCuaLe);
                                removeChip(_lstChipCua3trang);
                                break;
                            
                            case 2:
                                removeChip(_lstChipCuaChan);
                                break;
                                
                            case 3:
                                removeChip(_lstChipCuaLe);
                                removeChip(_lstChipCua1trang);
                                break;
                                
                            case 4:
                                removeChip(_lstChipCuaChan);
                                removeChip(_lstChipCua0trang);
                                break;
                        
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }
}

void SocdiaScene::turnResponse() {
    BINTurnResponse *turnresponse =
    (BINTurnResponse*)Common::getInstance()->checkEvent(NetworkManager::TURN);
    if (turnresponse != 0) {
        log("turn response: %s", turnresponse->DebugString().c_str());
        if (turnresponse->responsecode()) {
            int countdown = turnresponse->has_countdowntimer() ? (int)(turnresponse->countdowntimer()) / 1000 : 0;
            string msg = StringUtils::format("nhà cái ngừng nhận cửa, sau %d giây sẽ mở bát", countdown);
            //TODO: hiệu ứng đồng hồ lắc với số giây là countdown
            auto frames = getFrameAnimation("clock_%d.png",3);
            auto animation = Animation::createWithSpriteFrames(frames,1.0f/9);
            auto repeat = Repeat::create(Animate::create(animation),countdown*3);
            sprite_clock->runAction(Sequence::create(repeat,NULL));
            Vector<FiniteTimeAction*> countDownTime;
            auto delayin = DelayTime::create(1.0f);
            for (int i = 0; i<countdown; i++) {
                auto callAppear = CallFunc::create([=]() {
                    timerCountDown->setString(StringUtils::format("%d", countdown - i - 1));
                    timerCountDown->setPosition(sprite_clock->getWidth()/2 - timerCountDown->getWidth()/2,
                                                sprite_clock->getHeight()/2 - timerCountDown->getHeight()*0.8f);
                });
                auto sequence = Sequence::create(delayin->clone(), callAppear, NULL);
                countDownTime.pushBack(sequence);
            }
            auto callFunc = CallFunc::create([=]{
                sprite_clock->setSpriteFrame("clock_2.png");
                sprite_clock->setVisible(false);
             });
            timerCountDown->runAction(Sequence::create(Sequence::create(countDownTime),callFunc,NULL));
            
            this->showToast(msg.c_str(), 2);
            setVisibleBetButton(_canBet = false);
            if (turnresponse->args_size() > 0) {
                _result = Common::getInstance()->convertStringToInt(turnresponse->args(0).value());
            }
        } else {
            this->showToast(turnresponse->message().c_str(), 2);
        }
    }
}

void SocdiaScene::startMatchResponse() {
    BINStartMatchResponse *rs =
    (BINStartMatchResponse*)Common::getInstance()->checkEvent(NetworkManager::START_MATCH);
    if (rs != 0) {
        log("start match response: %s", rs->DebugString().c_str());
        if (rs->responsecode()) {
            int countdown = rs->has_countdowntimer() ? rs->countdowntimer() : 0;
            countdown = 3;
            //TODO: hiệu ứng xóc đĩa trong countdown - 3 giây
            
            girl->runAction(Sequence::create(ScaleTo::create(0.1f,1.2f),CallFunc::create([&]{
                girl->setVisible(false);
            }),NULL));
            
            auto darkSprite = LayerColor::create(Color4B(0, 0, 0, 180));
            darkSprite->setContentSize(visibleSize);
            darkSprite->setPosition(origin);
            this->addChild(darkSprite);
            
            auto an_animation = getFrameAnimation("cogai_%02d.png", 4);
            auto sprite = Sprite::createWithSpriteFrame(an_animation.front());
            sprite->setAnchorPoint(Point::ZERO);
            sprite->setPosition(MVec2(width/2-sprite->getContentSize().width/2,
                                      height/2 - sprite->getContentSize().height/2));
            auto animation = Animation::createWithSpriteFrames(an_animation, countdown/(8*3.0f));
            auto repeat = Repeat::create(Animate::create(animation), 6);
            auto callFunc = CallFunc::create([=]{
                darkSprite->removeFromParentAndCleanup(true);
                girl->setVisible(true);
                girl->runAction(ScaleTo::create(0.2f,1.0));
            });
            sprite->runAction(Sequence::create(repeat,callFunc,RemoveSelf::create(),NULL));
            this->addChild(sprite);
        } else {
            this->showToast(rs->message().c_str(), 2);
        }
    }
}

void SocdiaScene::matchBeginResponse() {
    BINMatchBeginResponse* response =
    (BINMatchBeginResponse*)Common::getInstance()->checkEvent(NetworkManager::MATCH_BEGIN);
    if (response != 0) {
        log("match begin response:\n %s\n", response->DebugString().c_str());
        if (response->responsecode()) {
            if (response->has_countdowntimer()) {
                int timeCountDown = (int)response->countdowntimer() / 1000;
                string msg = StringUtils::format("Bạn có %d giây để đặt cửa", timeCountDown);
                this->showToast(msg.c_str(), 2);
                setVisibleBetButton(_canBet = true);
                
                //TODO: coutn down
                /*auto timerCountDown = MLabel::createClockCountDown(timeCountDown);
                timerCountDown->setTag(CLOCK);
                timerCountDown->setPosition(Vec2(sprite_clock->getWidth()/2, sprite_clock->getHeight()/2));
                sprite_clock->addChild(timerCountDown);*/
                
                sprite_clock->setVisible(true);
                sprite_clock->runAction(Spawn::create(ScaleTo::create(0.2f,1),
                                                      FadeIn::create(0.2f),NULL));
                auto frames = getFrameAnimation("clock_%d.png",3);
                auto animation = Animation::createWithSpriteFrames(frames,1.0f/9);
                auto repeat = Repeat::create(Animate::create(animation),5*3);
                auto callFuncClock = CallFunc::create([=]{
                    sprite_clock->setVisible(false);
                });
                sprite_clock->runAction(Sequence::create(repeat,Spawn::create(ScaleTo::create(0.2f,0.2f),FadeOut::create(0.2f), NULL),
                                                         callFuncClock,NULL));
                
                Vector<FiniteTimeAction*> countDownTime;
                for (int i = 0; i<timeCountDown; i++) {
                    auto callAppear = CallFunc::create([=]() {
                        timerCountDown->setString(StringUtils::format("%d", timeCountDown - i - 1));
                        timerCountDown->setPosition(sprite_clock->getWidth()/2 - timerCountDown->getWidth()/2,
                                                    sprite_clock->getHeight()/2 - timerCountDown->getHeight()*0.8f);
                        if(i == timeCountDown - 5){
                            sprite_clock->setSpriteFrame("clock_2.png");
                            auto frames = getFrameAnimation("clock_%d.png",3);
                            auto animation = Animation::createWithSpriteFrames(frames,1.0f/9);
                            auto repeat = Repeat::create(Animate::create(animation),5*3);
                            sprite_clock->runAction(Sequence::create(repeat,NULL));
                        }
                    });
                    auto sequence = Sequence::create(Sequence::create(ScaleTo::create(0.1f,1.2f),
                                                                      DelayTime::create(0.8f),ScaleTo::create(0.1f,1),NULL),
                                                     callAppear, NULL);
                    countDownTime.pushBack(sequence);
                }
                /*auto callFunc = CallFunc::create([=]{
                    sprite_clock->setSpriteFrame("clock_2.png");
                    sprite_clock->setVisible(false);
                });*/
                auto callFunc1 = CallFunc::create([=]{
                    timerCountDown->setString("0");
                    sprite_clock->setSpriteFrame("clock_2.png");
                });
                timerCountDown->runAction(Sequence::create(Sequence::create(countDownTime),callFunc1,NULL));
                
            }
        } else {
            this->showToast(response->message().c_str(), 2);
        }
    }
}

void SocdiaScene::prepareNewMatchResponse() {
    BINPlayerEnterRoomResponse *prepareNewMatch =
    (BINPlayerEnterRoomResponse*) Common::getInstance()->checkEvent(NetworkManager::PREPARE_NEW_MATCH);
    if (prepareNewMatch != 0) {
        log("prepare new match response: %s", prepareNewMatch->DebugString().c_str());
        if (prepareNewMatch->responsecode()) {
            bat->setGlobalZOrder(_batZorder);
            if (bat->getPosition() != batPos) {
                auto move = MoveBy::create(1, Vec2(-dia->getContentSize().width, 0));
                bat->runAction(move);
            }
            loadNormaTexture();
            _result = -1;
            _lstChipCuaChan.clear();
            _lstChipCuaLe.clear();
            _lstChipCua4trang.clear();
            _lstChipCua3trang.clear();
            _lstChipCua1trang.clear();
            _lstChipCua0trang.clear();
            _lstChipWin.clear();
            invisibleBetLable();
            
        } else {
            this->showToast(prepareNewMatch->message().c_str(), 2);
        }
    }
}

void SocdiaScene::playerExitRoomResponse() {
    BINPlayerExitRoomResponse* rs =
    (BINPlayerExitRoomResponse*) Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_ROOM);
    if (rs != 0) {
        log("player exit room response: %s", rs->DebugString().c_str());
        if (rs->responsecode()) {
			Player* playerWaiting = findWaiting(rs->exituserid());
			//xoa nguoi cho di
			if (playerWaiting != 0){
				deleteWaitingPlayer(playerWaiting->getID());
				showNumberPlayerOutsite();
			}
			else {
				int leng = (int)lst_player.size();
				Avatar* avatar;

				for (int i = 0; i < leng; i++) {
					//xoa nguoi choi khoi ban choi
					string user_id = lst_player[i].getID();
					if (user_id == Common::getInstance()->convertIntToString((int)rs->exituserid())){
						lst_player.erase(lst_player.begin() + i);

						showInvitePlayer(lst_player.size());  //show moi choi

						avatar = findAvatarOfPlayer(rs->exituserid());
						//xoa avatar khoi ban choi (khong hien thi nua)
						if (avatar != 0){
							removeOutTablePlay(avatar);
							//xoa khoi danh sach luu avatars
							avatars.erase(std::remove(avatars.begin(), avatars.end(), avatar), avatars.end());
						}

						if (rs->changeownerroomcd() > 0){
							CCLOG("player exit room time countdown %d", rs->changeownerroomcd());
							int time_wait = rs->changeownerroomcd() / 1000;
                            addCountDown(time_wait);
						}
						break;
					}
				}

				showNumberPlayerOutsite();
			}
        } else {
            this->showToast(rs->message().c_str(), 2);
        }
    }
}

void SocdiaScene::playerEnterRoomResponse() {
    BINPlayerEnterRoomResponse* rs =
    (BINPlayerEnterRoomResponse*) Common::getInstance()->checkEvent(NetworkManager::PLAYER_ENTER_ROOM);
    if (rs != 0) {
        log("player enter room response: %s", rs->DebugString().c_str());
        if (rs->responsecode()) {
			XocDiaPlayer player = convertFromBINPlayer(rs->player());

			//neu la nguoi choi
			if (rs->enterroomstatus() == PlayerState::PLAYING){
				player_list.push_back(rs->player());
				lst_player.push_back(player);
				
				showInvitePlayer(lst_player.size());  //show moi choi

				if (lst_player.size() <= NUMBER_PLAYER_ON_TABLE){  //ban choi chua du 10 nguoi
					int posIndex = -1;
					bool findPos = false;
					for (int i = 0; i < NUMBER_PLAYER_ON_TABLE; i++){
						findPos = false;
						for (int j = 0; j < avatars.size(); j++){
							if (avatar_position[i] == avatars[j]->getPositionIndex()) {
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
				}
				else {  //ban choi co qua 10 nguoi, sap xep lai nguoi choi co so tien cao nhat va nguoi login vao ban choi
					resetDisplayAvatar(); //xoa avatar
					sortListPlayer(); //sort lai player
					displayInfoPlayer(lst_player); //dat player len ban choi
					showNumberPlayerOutsite(); //tinh lai so nguoi choi ngoai ban
				}
			}
			else {
				// xu ly voi nguoi cho
				if (rs->enterroomstatus() == PlayerState::WAITING){
					lst_waiting.push_back(player);
					showNumberPlayerOutsite();
				}
			}
        } else {
            this->showToast(rs->message().c_str(), 2);
        }
    }
}

void SocdiaScene::playerExitRoomAfterMatchResponse() {
    BINPlayerExitAfterMatchEndResponse* rs =
    (BINPlayerExitAfterMatchEndResponse*) Common::getInstance()->checkEvent(NetworkManager::PLAYER_EXIT_AFTER_MATCH_END);
    if (rs != 0) {
        log("player exit room after match end : %s", rs->DebugString().c_str());
        if (rs->responsecode()) {
			int leng = (int)lst_player.size();
			for (int i = 0; i < leng; i++) {
				//reset position
				string user_id = lst_player[i].getID();
				if (user_id == Common::getInstance()->convertIntToString((int)rs->exituserid())){
					/*char message[60];
					sprintf(message, "Người chơi %s đăng ký rời bàn chơi", lst_player[i].getName().c_str());
					this->showToast(message, 2);*/

					Avatar* avatar = findAvatarOfPlayer(rs->exituserid());
					if (avatar != 0){
						avatar->showRegisterExitRoom(true);
					}
					
					break;
				}
			}
        } else {
            this->showToast(rs->message().c_str(), 2);
        }
    }
}

void SocdiaScene::matchEndResponseHandler() {
    BINMatchEndResponse* rs =
    (BINMatchEndResponse*) Common::getInstance()->checkEvent(NetworkManager::MATCH_END);
    if (rs != 0) {
        log("match end response: %s", rs->DebugString().c_str());
        if(rs->responsecode()) {
            bat->setGlobalZOrder(10000);
            auto move = MoveBy::create(1, Vec2(dia->getContentSize().width, 0));
            bat->runAction(move);
            displayResult();
            switch (_result) {
                case 0:
                    _btnCua4Trang->loadTextureNormal(XOCDIA_BTN_KHUNGCUOC_WIN);
                    _btnCuaChan->loadTextureNormal(XOCDIA_BTN_CUOC_WIN);
                    removeChip(_lstChipCua0trang);
                    removeChip(_lstChipCua1trang);
                    removeChip(_lstChipCua3trang);
                    removeChip(_lstChipCuaLe);
                    break;

                case 1:
                    _btnCuaLe->loadTextureNormal(XOCDIA_BTN_CUOC_WIN);
                    _btnCua3Trang->loadTextureNormal(XOCDIA_BTN_KHUNGCUOC_WIN);
                    removeChip(_lstChipCuaChan);
                    removeChip(_lstChipCua0trang);
                    removeChip(_lstChipCua1trang);
                    removeChip(_lstChipCua4trang);
                    break;

                case 2:
                    removeChip(_lstChipCua0trang);
                    removeChip(_lstChipCua1trang);
                    removeChip(_lstChipCua3trang);
                    removeChip(_lstChipCua4trang);
                    removeChip(_lstChipCuaLe);
                    _btnCuaChan->loadTextureNormal(XOCDIA_BTN_CUOC_WIN);
                    break;

                case 3:
                    removeChip(_lstChipCuaChan);
                    removeChip(_lstChipCua0trang);
                    removeChip(_lstChipCua3trang);
                    removeChip(_lstChipCua4trang);
                    _btnCuaLe->loadTextureNormal(XOCDIA_BTN_CUOC_WIN);
                    _btnCua1Trang->loadTextureNormal(XOCDIA_BTN_KHUNGCUOC_WIN);
                    break;

                case 4:
                    removeChip(_lstChipCuaLe);
                    removeChip(_lstChipCua1trang);
                    removeChip(_lstChipCua3trang);
                    removeChip(_lstChipCua4trang);
                    _btnCuaChan->loadTextureNormal(XOCDIA_BTN_CUOC_WIN);
                    _btnCua0Trang->loadTextureNormal(XOCDIA_BTN_KHUNGCUOC_WIN);
                    break;

                default:
                    break;
            }
            updateListMatchResult(_result % 2);
        }
    }
}

void SocdiaScene::updateMoneyLabel(long long userID, long long displayChangeMoney, long long currentMoney) {
	if (Common::getInstance()->getUserId() == userID) {
		if (is_vip_room) {
			Common::getInstance()->setCash(currentMoney);
		}
		else {
			Common::getInstance()->setGold(currentMoney);
		}
	}

    Avatar* avatar = findAvatarOfPlayer(userID);
    if (avatar != 0) {
		if (userID == Common::getInstance()->getUserId()) {
			_totalMoney = currentMoney;
		}
		if (displayChangeMoney != 0) {
			auto moneyText = MLabel::createUpdateMoney(displayChangeMoney);
            moneyText->setPosition(Vec2(avatar->getPosition().x + avatar->avatar->getWidth() / 2,
                                        avatar->getPosition().y + avatar->avatar->getHeight() / 2));
            this->addChild(moneyText,INDEX_UPDATE_MONEY);
        }
		avatar->setMoney(currentMoney);
    }
}

void SocdiaScene::hostRegistration() {
    BINHostRegistrationResponse* rs =
    (BINHostRegistrationResponse*) Common::getInstance()->checkEvent(NetworkManager::HOST_REGISTRATION);
    if (rs != 0) {
        log("host registration response: %s", rs->DebugString().c_str());
        if (rs->responsecode()) {
            //TODO: the hien thang lam cai
            if (rs->hostuseridqueue_size() != 0) {
                vector<int> lstLong;
                for (int i = 0; i < rs->hostuseridqueue_size(); i++) {
                    lstLong.push_back((int)rs->hostuseridqueue(i));
                }
                if (std::find(lstLong.begin(), lstLong.end(), Common::getInstance()->getUserId()) != lstLong.end()) {
                    _btnXinlamcai->setVisible(false);
                    _btnHuylamcai->setVisible(true);
                }
            } else {
                _btnXinlamcai->setVisible(true);
                _btnHuylamcai->setVisible(false);
            }
        }
    }
}

void SocdiaScene::extraBetHandler() {
    BINExtraBetResponse* rs =
    (BINExtraBetResponse*) Common::getInstance()->checkEvent(NetworkManager::EXTRA_BET);
    if (rs != 0) {
        log("extra bet response: %s", rs->DebugString().c_str());
        if (rs->responsecode()) {
            int userId;
            vector<vector<int>> playerBet;
            vector<vector<int>> totalBetGate;
            vector<vector<int>> totalplayerBet;
            
            if (rs->args_size() != 0) {
                for(int i = 0; i < rs->args_size(); i++) {
                    string key = rs->args(i).key();
                    string value = rs->args(i).value();
                    if (key == "userId") {
                        userId = Common::getInstance()->convertStringToInt(value);
                    } else if (key == "playerBetGate") {
                        playerBet = parseJSONtoVector(value);
                    } else if (key == "totalBetGate") {
                        totalBetGate = parseJSONtoVector(value);
                    } else if (key == "totalPlayerBetGate") {
                        totalBetGate = parseJSONtoVector(value);
                    }
                }
                for (int i = 0; i < totalBetGate.size(); i++) {
                    string totalBet = Common::getInstance()->convertIntToString(totalBetGate[i][1]);
                    string playBet = " ";
                    switch (totalBetGate[i][0]) {
                        case 10:;
                            updateBetLabel(_cuaChantotalBet, NULL, totalBet, playBet);
                            break;
                            
                        case 11:
                            updateBetLabel(_cuaLeTotalBet, NULL, totalBet, playBet);
                            break;
                            
                        case 0:
                            updateBetLabel(_cua4TrangTotalBet, NULL, totalBet, playBet);
                            break;
                            
                        case 1:
                            updateBetLabel(_cua3TrangTotalBet, NULL, totalBet, playBet);
                            break;
                            
                        case 3:
                            updateBetLabel(_cua1TrangTotalBet, NULL, totalBet, playBet);
                            break;
                            
                        case 4:
                            updateBetLabel(_cua0TrangTotalBet, NULL, totalBet, playBet);
                            break;
                            
                        default:
                            break;
                    }
                }
                if (Common::getInstance()->getUserId() == userId) {
                    for (int i = 0; i < totalBetGate.size(); i++) {
                        string totalBet = " ";
                        string playBet = Common::getInstance()->convertIntToString(totalBetGate[i][1]);
                        switch (totalBetGate[i][0]) {
                            case 10:;
                                updateBetLabel(NULL, _cuaChanPlayBet, totalBet, playBet);
                                break;
                                
                            case 11:
                                updateBetLabel(NULL, _cuaLePlayBet, totalBet, playBet);
                                break;
                                
                            case 0:
                                updateBetLabel(NULL, _cua4TrangPlayBet, totalBet, playBet);
                                break;
                                
                            case 1:
                                updateBetLabel(NULL, _cua3TrangPlayBet, totalBet, playBet);
                                break;
                                
                            case 3:
                                updateBetLabel(NULL, _cua1TrangPlayBet, totalBet, playBet);
                                break;
                                
                            case 4:
                                updateBetLabel(NULL, _cua0TrangPlayBet, totalBet, playBet);
                                break;
                                
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }
}

void SocdiaScene::menuCallBack(cocos2d::Ref *pSender,
                               cocos2d::ui::Widget::TouchEventType eventType) {
    if (eventType == ui::Widget::TouchEventType::ENDED) {
        int tag = ((MButton*) pSender)->getTag();
        switch (tag) {
			case TAG_XOCDIA_OUTSITE_PLAYER:
                if(this->getChildByTag(POPUP_TAG_OUTSITE_PLAYER) == nullptr){
                    auto m_popupViewPlayerOutsite = PopupViewPlayerOutsite::create();
                    m_popupViewPlayerOutsite->setPosition(MVec2(0, 0));
                    addChild(m_popupViewPlayerOutsite,INDEX_POPUP);
                    
                    m_popupViewPlayerOutsite->setLstUserOutsite(lst_player);
                    m_popupViewPlayerOutsite->appear();
                }
                    
                
				break;
            case TAG_XOCDIA_CUA_LE:
                if (_canBet && _totalMoney > getMinBet() * getBetRatio()) {
                    log("đặt cửa lẻ số tiền là:");
                    log(getMinBet() * getBetRatio());
                    NetworkManager::getInstance()->getBetXocDia(getRoomIndex(), getMinBet() * getBetRatio(), 11);
                } else {
                    this->showToast("hết mẹ tiền đặt éo gì nữa", 2);
                }
                break;

            case TAG_XOCDIA_CUA_CHAN:
                if (_canBet && _totalMoney > getMinBet() * getBetRatio()) {
                    log("đặt cửa chẵn số tiền là:");
                    log(getMinBet() * getBetRatio());
                    NetworkManager::getInstance()->getBetXocDia(getRoomIndex(), getMinBet() * getBetRatio(), 10);
                } else {
                    this->showToast("hết mẹ tiền đặt éo gì nữa", 2);
                }
                break;

            case TAG_XOCDIA_CUA_0_TRANG:
                if (_canBet && _totalMoney > getMinBet() * getBetRatio()) {
                    log("đặt cửa 4 đỏ số tiền là:");
                    log(getMinBet() * getBetRatio());
                    NetworkManager::getInstance()->getBetXocDia(getRoomIndex(), getMinBet() * getBetRatio(), 4);
                } else {
                    this->showToast("hết mẹ tiền đặt éo gì nữa", 2);
                }
                break;
            
            case TAG_XOCDIA_CUA_1_TRANG:
                if (_canBet && _totalMoney > getMinBet() * getBetRatio()) {
                    log("đặt cửa 3 đỏ số tiền là:");
                    log(getMinBet() * getBetRatio());
                    NetworkManager::getInstance()->getBetXocDia(getRoomIndex(), getMinBet() * getBetRatio(), 3);
                } else {
                    this->showToast("hết mẹ tiền đặt éo gì nữa", 2);
                }
                break;

            case TAG_XOCDIA_CUA_3_TRANG:
                if (_canBet && _totalMoney > getMinBet() * getBetRatio()) {
                    log("đặt cửa 1 đỏ số tiền là:");
                    log(getMinBet() * getBetRatio());
                    NetworkManager::getInstance()->getBetXocDia(getRoomIndex(), getMinBet() * getBetRatio(), 1);
                } else {
                    this->showToast("hết mẹ tiền đặt éo gì nữa", 2);
                }
                break;

            case TAG_XOCDIA_CUA_4_TRANG:
                if (_canBet && _totalMoney > getMinBet() * getBetRatio()) {
                    log("đặt cửa 4 trắng số tiền là:");
                    log(getMinBet() * getBetRatio());
                    NetworkManager::getInstance()->getBetXocDia(getRoomIndex(), getMinBet() * getBetRatio(), 0);
                } else {
                    this->showToast("hết mẹ tiền đặt éo gì nữa", 2);
                }
                break;

            case TAG_XOCDIA_BTN_DATLAI:
                log("đặt lại những cửa ván trước đặt");
                NetworkManager::getInstance()->getExtraBetRequest(getRoomIndex(), 1);
                break;

            case TAG_XOCDIA_BTN_HUYCUOC:
                log("huỷ cược");
                NetworkManager::getInstance()->getExtraBetRequest(getRoomIndex(), 0);
                break;
            
            case TAG_XOCDIA_BTN_GAPDOI:
                log("gấp đôi ván trước");
                NetworkManager::getInstance()->getExtraBetRequest(getRoomIndex(), 2);
                break;
            
            case TAG_XOCDIA_BTN_XINCAI:
                log("dang ki lam cai");
                NetworkManager::getInstance()->getHostRegistration(getRoomIndex());
                break;
            
            case TAG_XOCDIA_BTN_HUYCAI:
                log("xin huy lam cai");
                NetworkManager::getInstance()->getHostRegistration(getRoomIndex(), true);
                break;
			case TAG_BTN_SANSANG:
				NetworkManager::getInstance()->getReadyToPlayMessageFromServer(roomIndex, -1);
				break;
            default:
                break;
        }
    }
}

void SocdiaScene::chipCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType){
	if (eventType == ui::Widget::TouchEventType::ENDED) {
		int tag = ((MButton*)pSender)->getTag();
		showChipClicked(tag);
		switch (tag) {
		case TAG_XOCDIA_BTN_X1:
			setBetRatio(1);
			//TODO: hiển thị lớn button nhân 1, các button nhân khác về trạng thái bình thường
			break;

		case TAG_XOCDIA_BTN_X5:
			if (_totalMoney / getMinBet() > 5) {
				setBetRatio(5);
				//TODO: hiển thị lớn button nhân 5, các button nhân khác về trạng thái bình thường
			}
			else {
				//TODO: không thay đổi trạng thái các button
				this->showToast("đủ tiền éo đâu mà sĩ", 2);
			}
			break;

		case TAG_XOCDIA_BTN_X25:
			if (_totalMoney / getMinBet() > 25) {
				setBetRatio(25);
				//TODO: hiển thị lớn button nhân 25, các button nhân khác về trạng thái bình thường
			}
			else {
				//TODO: không thay đổi trạng thái các button
				this->showToast("đủ tiền éo đâu mà sĩ", 2);
			}
			break;

		case TAG_XOCDIA_BTN_X50:
			if (_totalMoney / getMinBet() > 50) {
				setBetRatio(50);
				//TODO: hiển thị lớn button nhân 50, các button nhân khác về trạng thái bình thường
			}
			else {
				//TODO: không thay đổi trạng thái các button
				this->showToast("đủ tiền éo đâu mà sĩ", 2);
			}
			break;
		default:
			break;
		}
	}
}

void SocdiaScene::enableBetButton(long long totalMoney) {
    _btnX1->setVisible(totalMoney > getMinBet());
    _btnX5->setVisible(totalMoney > getMinBet() * 5);
    _btnX25->setVisible(totalMoney > getMinBet() * 25);
    _btnX50->setVisible(totalMoney > getMinBet() * 50);
}

void SocdiaScene::setBetsRatio(string JSONString) {
    log("%s",JSONString.c_str());
    vector<JSONObject> result;
    Document document;
    document.Parse(JSONString.c_str());
    rapidjson::Value::ConstMemberIterator itr = document.MemberBegin();
    assert(itr->value.IsObject());
    for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); it++) {
        vector<int> betRatio;
        betRatio.push_back(Common::getInstance()->convertStringToInt(it->name.GetString()));
        betRatio.push_back(it->value.GetInt());
        _betsRatio.push_back(betRatio);
    }
    log("%lu",_betsRatio.size());
}

void SocdiaScene::setVisibleBetButton(bool visible) {
    _btnDatlai->setVisible(visible);
    _btnHuyCuoc->setVisible(visible);
    _btnGapDoi->setVisible(visible);
}

int SocdiaScene::getTypeBetRatio(int type) {
    int result = 0;
    for (vector<vector<int>>::iterator it = _betsRatio.begin(); it != _betsRatio.end(); it++) {
        if ((*it)[0] == type) {
            result = (*it)[1];
        }
    }
    return result;
}

void SocdiaScene::loadNormaTexture() {
    switch (_result) {
        case 0:
            _btnCuaChan->loadTextureNormal(XOCDIA_BTN_CUOC);
            _btnCua4Trang->loadTextureNormal(XOCDIA_BTN_KHUNGCUOC);
            break;
        case 1:
            _btnCuaLe->loadTextureNormal(XOCDIA_BTN_CUOC);
            _btnCua3Trang->loadTextureNormal(XOCDIA_BTN_KHUNGCUOC);
            break;
        case 2:
            _btnCuaChan->loadTextureNormal(XOCDIA_BTN_CUOC);
            break;
        case 3:
            _btnCuaLe->loadTextureNormal(XOCDIA_BTN_CUOC);
            _btnCua1Trang->loadTextureNormal(XOCDIA_BTN_KHUNGCUOC);
            break;
        case 4:
            _btnCuaChan->loadTextureNormal(XOCDIA_BTN_CUOC);
            _btnCua0Trang->loadTextureNormal(XOCDIA_BTN_KHUNGCUOC);
            break;
        default:
            break;
    }
}

void SocdiaScene::displayResult() {
    int firstRan = random(0, 3);
    int secondRan;
    do {
        secondRan = random(0, 3);
    } while (secondRan == firstRan);
    switch (_result) {
        case 0:
            for(int i = 0; i < _lstResult.size(); i ++) {
                _lstResult[i]->setTexture(XOCDIA_SPRITE_TRANG);
            }
            break;
        case 1:
            for (int i = 0; i < _lstResult.size(); i ++) {
                if (i == firstRan) {
                    _lstResult[i]->setTexture(XOCDIA_SPRITE_DO);
                } else {
                    _lstResult[i]->setTexture(XOCDIA_SPRITE_TRANG);
                }
            }
            break;
        case 2:
            for (int i = 0; i < _lstResult.size(); i++) {
                if (i == firstRan || i == secondRan) {
                    _lstResult[i]->setTexture(XOCDIA_SPRITE_DO);
                } else {
                    _lstResult[i]->setTexture(XOCDIA_SPRITE_TRANG);
                }
            }
            break;
        case 3:
            for (int i = 0; i < _lstResult.size(); i++) {
                if (i == firstRan) {
                    _lstResult[i]->setTexture(XOCDIA_SPRITE_TRANG);
                } else {
                    _lstResult[i]->setTexture(XOCDIA_SPRITE_DO);
                }
            }
            break;
        case 4:
            for (int i = 0; i < _lstResult.size(); i++) {
                _lstResult[i]->setTexture(XOCDIA_SPRITE_DO);
            }
            break;
            
        default:
            break;
    }
}

void SocdiaScene::addChipWhenBet(int typeID, string typeChip, long long userId) {
    auto chip = MSprite::create(typeChip);
    Avatar* ava = findAvatarOfPlayer(userId);
    int chipX = ava != NULL ? ava->getPositionX() : ic_songuoixem->getPositionX();
    int chipY = ava != NULL ? ava->getPositionY() : ic_songuoixem->getPositionY();
    chip->setPosition(Vec2(chipX, chipY));
    this->addChild(chip);
    Size size = chip->getContentSize();
    float randX, randY;
    if (typeID == 10) {
        _lstChipCuaChan.push_back(chip);
        randX = random(_btnCuaChan->getPositionX() + _btnCuaChan->getContentSize().width / 2 - 3 * size.width,
                       _btnCuaChan->getPositionX() + _btnCuaChan->getContentSize().width / 2 + 2 * size.width);
        randY = random(_btnCuaChan->getPositionY() + _btnCuaChan->getContentSize().height / 2 - size.height,
                       _btnCuaChan->getPositionY() + _btnCuaChan->getContentSize().height / 2 + size.height);
    } else if (typeID == 11) {
        _lstChipCuaLe.push_back(chip);
        randX = random(_btnCuaLe->getPositionX() - _btnCuaLe->getContentSize().width / 2 - 2 * size.width,
                       _btnCuaLe->getPositionX() - _btnCuaLe->getContentSize().width / 2 + 3 * size.width);
        randY = random(_btnCuaLe->getPositionY() + _btnCuaLe->getContentSize().height / 2 - size.height,
                       _btnCuaLe->getPositionY() + _btnCuaLe->getContentSize().height / 2 + size.height);
    } else if (typeID == 0) {
        _lstChipCua4trang.push_back(chip);
        randX = random(_btnCua4Trang->getPositionX() + _btnCua4Trang->getContentSize().width / 2 - size.width,
                       _btnCua4Trang->getPositionX() + _btnCua4Trang->getContentSize().width / 2 + size.width);
        randY = random(_btnCua4Trang->getPositionY() + _btnCua4Trang->getContentSize().height / 2 - size.height,
                       _btnCua4Trang->getPositionY() + _btnCua4Trang->getContentSize().height / 2 + size.height);
    } else if (typeID == 1) {
        _lstChipCua3trang.push_back(chip);
        randX = random(_btnCua3Trang->getPositionX() + _btnCua3Trang->getContentSize().width / 2 - size.width,
                       _btnCua3Trang->getPositionX() + _btnCua3Trang->getContentSize().width / 2 + size.width);
        randY = random(_btnCua3Trang->getPositionY() + _btnCua3Trang->getContentSize().height / 2 - size.height,
                       _btnCua3Trang->getPositionY() + _btnCua3Trang->getContentSize().height / 2 + size.height);
    } else if (typeID == 3) {
        _lstChipCua1trang.push_back(chip);
        randX = random(_btnCua1Trang->getPositionX() + _btnCua1Trang->getContentSize().width / 2 - size.width,
                       _btnCua1Trang->getPositionX() + _btnCua1Trang->getContentSize().width / 2 + size.width);
        randY = random(_btnCua1Trang->getPositionY() + _btnCua1Trang->getContentSize().height / 2 - size.height,
                       _btnCua1Trang->getPositionY() + _btnCua1Trang->getContentSize().height / 2 + size.height);
    } else if (typeID == 4) {
        _lstChipCua0trang.push_back(chip);
        randX = random(_btnCua0Trang->getPositionX() + _btnCua0Trang->getContentSize().width / 2 - size.width,
                       _btnCua0Trang->getPositionX() + _btnCua0Trang->getContentSize().width / 2 + size.width);
        randY = random(_btnCua0Trang->getPositionY() + _btnCua0Trang->getContentSize().height / 2 - size.height,
                       _btnCua0Trang->getPositionY() + _btnCua0Trang->getContentSize().height / 2 + size.height);
    }
    auto move = MoveTo::create(0.5, Vec2(randX, randY));
    chip->runAction(move);
}

void SocdiaScene::removeChip(vector<MSprite *> lst) {
        for (int i = lst.size() - 1; i >= 0; i--) {
            auto move = MoveTo::create(0.5, girl->getPosition());
            lst[i]->runAction(Sequence::create(move, RemoveSelf::create(), NULL));
        }
}

void SocdiaScene::addChipWin(vector<MSprite*> lst) {
    for (int i = lst.size() - 1; i >= 0; i--) {
        auto chip = MSprite::create();
        chip->setTexture(lst[i]->getTexture());
        chip->setPosition(girl->getPosition());
        this->addChild(chip);
        float ranX = (-lst[i]->getContentSize().width, lst[i]->getContentSize().width);
        float ranY = (-lst[i]->getContentSize().height, lst[i]->getContentSize().height);
        auto move = MoveTo::create(0.2, Vec2(lst[i]->getPositionX() + ranX, lst[i]->getPositionY() + ranY));
        chip->runAction(move);
        _lstChipWin.push_back(chip);
    }
}

void SocdiaScene::invisibleBetLable() {
    _cuaChantotalBet->setVisible(false);
    _cuaChanPlayBet->setVisible(false);
    _cuaLeTotalBet->setVisible(false);
    _cuaLePlayBet->setVisible(false);
    _cua1TrangTotalBet->setVisible(false);
    _cua1TrangPlayBet->setVisible(false);
    _cua3TrangTotalBet->setVisible(false);
    _cua3TrangPlayBet->setVisible(false);
    _cua4TrangTotalBet->setVisible(false);
    _cua4TrangPlayBet->setVisible(false);
    _cua0TrangTotalBet->setVisible(false);
    _cua0TrangPlayBet->setVisible(false);
}

void SocdiaScene::updateBetLabel(MLabel *totalBet, MLabel *playerBet, string total, string player) {
    if (totalBet != NULL) {
        totalBet->setVisible(true);
        totalBet->setString(total);
    }
    if (playerBet != NULL) {
        if (player != " ") {
            playerBet->setVisible(true);
            playerBet->setString(player);
        }
    }
}

vector<vector<int>> SocdiaScene::parseJSONtoVector(string JSONstring) {
    vector<vector<int>> vectorResult;
    vector<JSONObject> result;
    Document document;
    document.Parse(JSONstring.c_str());
    for(rapidjson::Value::ConstMemberIterator it = document.MemberBegin(); it != document.MemberEnd(); it++) {
        vector<int> betRatio;
        betRatio.push_back(Common::getInstance()->convertStringToInt(it->name.GetString()));
        betRatio.push_back(it->value.GetInt());
        vectorResult.push_back(betRatio);
    }
    return vectorResult;
}
