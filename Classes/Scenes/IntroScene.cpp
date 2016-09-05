#include "IntroScene.h"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "LoginScene.h"
#include "Utils/Common.h"
#include "Utils/Utility.h"
#include "Utils/TLMNConfig.hpp"
#include "Utils/SoundManager.h"
#include "Utils/LoadingManager.hpp"
#include "Popups/PopupReconnect.hpp"

Scene* IntroScene::createScene() {

    auto scene = Scene::create();

    auto layer = IntroScene::create();

    scene->addChild(layer);

    return scene;
}

void connectData() {
	NetworkManager::getInstance()->connectServer(SERVER_NAME, SERVER_PORT);
}

bool IntroScene::init() {
    if (!BaseScene::init()) {
        return false;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("an.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("nem.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("avatar_win_animation.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("toitrang_animation.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_cards.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cogai_xocdia.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("clock_sprites.plist");
    
    SoundManager::getInstance()->preLoadAudio(soundTLMN);

    /*auto background = LayerColor::create(Color4B(0,0,0,255));
    background->setContentSize(visibleSize);
	background->setPosition(MVec2(0, 0));
	this->addChild(background);*/

	auto bkg = MSprite::create(BGR_LISTGAMES, visibleSize);
	bkg->setPosition(MVec2(0, 0));
	this->addChild(bkg);

	auto bg_card = MSprite::create("bg_card.png");
	bg_card->setPosition(MVec2(visibleSize.width / 2 - bg_card->getWidth() / 2, visibleSize.height / 2 - bg_card->getHeight() / 2));
	this->addChild(bg_card);

	auto girl = MSprite::create("sprite_cogai.png");
	girl->setScale(0.9*height / girl->getHeight());
	girl->setPosition(MVec2(visibleSize.width / 2 - girl->getWidth() / 2, 0));
	this->addChild(girl);

	loadingBar = Slider::create();
	loadingBar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	loadingBar->loadBarTexture("insite_process_initgame.png");
	loadingBar->loadProgressBarTexture("outsite_process_initgame.png");
	loadingBar->loadSlidBallTextureNormal("sprite_ball_process.png");
	loadingBar->setMaxPercent(100);
	loadingBar->setPosition(MVec2(width / 2, loadingBar->getContentSize().height));
	this->addChild(loadingBar);

	auto sprite_loading = MSprite::create("sprite_loading.png");
	sprite_loading->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprite_loading->setPosition(loadingBar->getPosition());
	this->addChild(sprite_loading);

    /*auto label = MLabel::create("BigKen Online", 65);
    label->setPosition(MVec2(width/2 - label->getWidth()/2,height/2 - label->getHeight()/2));
    this->addChild(label);*/

    //this->scheduleOnce(schedule_selector(IntroScene::gotoStartScene), 3.0f);
	this->scheduleUpdate();

    return true;
}

void IntroScene::gotoStartScene(float dt) {
    CCLOG("package name:%s", Common::getInstance()->getPackageName().c_str());

    if (NetworkManager::getInstance()->isConnected()) {
        NetworkManager::getInstance()->closeConnection();
    }

    NetworkManager::getInstance()->connect();

    if (NetworkManager::getInstance()->isConnected()) {
        NetworkManager::setListening(true);
        NetworkManager::getInstance()->listenData();

        NetworkManager::getInstance()->getInitializeMessageFromServer(
            Common::getInstance()->getCp(),
            Common::getInstance()->getAppVersion(),
            Common::getInstance()->getCountry(),
			Common::getInstance()->getLanguage(),
            Common::getInstance()->getDeviceId(),
            Common::getInstance()->getDeviceInfo(),
            Common::getInstance()->getIpaddress(), 
            Common::getInstance()->getPackageName()
            );
        NetworkManager::getInstance()->getPingMessageFromServer(0);
    }
    else {
        PopupReconnect::getInstance()->showPopup();
        // this->showToast("Không thể kết nối đến máy chủ, vui lòng thử lại", 2);
    }
}

void IntroScene::onExit() {
    BaseScene::onExit();
}

void IntroScene::update(float delta) {
    BaseScene::update(delta);
    
    if(!nextScene){
        if(deltaTime < 2){
            deltaTime += 0.04f;
        }else if(deltaTime >=2 && deltaTime <= 3){
            deltaTime += 0.02f;
        }else{
            nextScene = true;
            gotoStartScene(deltaTime);
        }
        percent = 100*deltaTime/3;
        
        loadingBar->setPercent(percent);
    }

    BINInitializeResponse *init_response = (BINInitializeResponse*)
        Common::getInstance()->checkEvent(NetworkManager::INITIALIZE);

    //int roomIndex; std::vector<BINPlayer> playerList; vector<BINPlayer> _waitingPlayerList;
    //    bool createRoom;
    //  
   
    if (init_response != 0) {
        CCLOG("init response: %s", init_response->DebugString().c_str());
        NetworkManager::setInitialize(init_response->responsecode());
        auto scene = LoginScene::createScene();
		REPLACESCENE(0.25f, scene);
    }
}
   
