//
//  Avatar.cpp
//  MyCards
//
//  Created by hungle on 4/22/16.
//
//

#include "Avatar.hpp"
#include "Utils/NetworkManager.h"
#include <math.h>

using namespace cocos2d::ui;

#define PADDING 15
#define XONG 3
#define WIN 1
#define LOSE 2

bool Avatar::init(){
    if (!Node::init())
        return false;
    
    this->setAnchorPoint(Point::ZERO);
     
    background = MSprite::create("sprite_avatar_background.png");
    background->setPosition(Point::ZERO);
    this->addChild(background);
    
    avatar = MSprite::create("null_bg.png", cocos2d::Size(background->getWidth(), background->getWidth()));
    avatar->setPosition(0,(background->getHeight() / 2 - background->getWidth() / 2));
    this->addChild(avatar);
    
    circleBar = MCircleBar::createWithPer(0, 0);
    circleBar->setPosition(Vec2(background->getWidth()/2 + circleBar->getContentSize().width/2,
                                background->getHeight()/2));
    this->addChild(circleBar);
    
    spritePassUp = MSprite::create("sprite_boluot.png");
    spritePassUp->setVisible(false);
    this->addChild(spritePassUp);
    
    name = MLabel::create("z",background->getWidth()/5);
    name->setPosition(Vec2(background->getWidth()/2-name->getWidth()/2,
                           background->getHeight()+5));
    name->setAlignment(TextHAlignment::CENTER);
    this->addChild(name);
    
    under_money = MSprite::create("sprite_diem.png");
    under_money->setPosition(Vec2(background->getWidth()/2-under_money->getWidth()/2,
                                  -5-under_money->getHeight()));
    this->addChild(under_money);
    
    money = MLabel::create("10$",background->getWidth()/6);
    money->setPosition(Vec2(background->getWidth()/2-money->getWidth()/2,
                            under_money->getPosition().y+under_money->getHeight()/2-money->getHeight()/2));
    money->setAlignment(TextHAlignment::CENTER);
    this->addChild(money);
    
    spriteCard = MSprite::createwithFrameName("card_cover.png");
    this->addChild(spriteCard);
    
    /* Anh Điệp xem lại chỗ này tạo Sprite mới không dùng hàm này được
    exit_room = MSprite::createwithFrameName("close.png");
    this->addChild(exit_room);
     */
    
    number = MLabel::create("13", 30);
    number->enableOutline(Color4B(201,227,29,255),2);
    this->addChild(number);

	ic_register_exit_room = MSprite::create("ic_exit_room.png");
	ic_register_exit_room->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	ic_register_exit_room->setPosition(Vec2(background->getPosition().x
		, background->getPosition().y + background->getHeight() / 2));
	ic_register_exit_room->setVisible(false);
	this->addChild(ic_register_exit_room , 10);

    this->setContentSize(background->getContentSize());
    
    this->addEvents();

    return true;
}

//show dang ki thoat
void Avatar::showRegisterExitRoom(bool isShow){
	ic_register_exit_room->setVisible(isShow);
}


//void Avatar::menuCallBack(Ref *pSender, Widget::TouchEventType eventType) {
//	if (eventType == Widget::TouchEventType::ENDED){
//
//	}
//}

void Avatar::setDraw(int duration) {
    auto spriteDraw = Sprite::create("sprite_draw.png");
    spriteDraw->setPosition(Vec2(background->getWidth() / 2,
        background->getHeight()/ 2));
    this->addChild(spriteDraw);
    spriteDraw->runAction(Sequence::create(DelayTime::create(duration), RemoveSelf::create(), NULL));
}

void Avatar::showXong(bool finished){
    if(this->getChildByTag(XONG) != nullptr){
        this->getChildByTag(XONG)->setVisible(finished);
    }else{
        auto sprite = Sprite::create("xong.png");
        sprite->setTag(XONG);
        sprite->setPosition(Vec2(background->getWidth()/2,background->getHeight()/2));
        this->addChild(sprite);
        sprite->setVisible(finished);
    }
}

//cap nhat percent xung quanh avatar
void Avatar::updateProgressCircleBar(float percent, float time_countdown){
    circleBar->upDatePer(percent, time_countdown / 1000);
}

//reset percent xung quanh avatar
void Avatar::resetProcessCircleBar(){
    this->updateProgressCircleBar(0, 100);
}

void Avatar::loadAvatar(int index, std::string id, std::string _name, std::string _money, int roomIndex) {
    this->roomIndex = roomIndex;
    std::stringstream ss(id);
    ss >> player_id;

    avatar->setTexture(StringUtils::format("avatar%d.png", index));
    avatar->setScale(background->getWidth() / avatar->getWidth());
    
    name->setString(_name);
    name->setPosition(Vec2(background->getWidth()/2-name->getWidth()/2,
                           background->getHeight()+5));
    
    money->setString(_money);
    money->setPosition(Vec2(background->getWidth()/2-money->getWidth()/2,
                            under_money->getPosition().y+under_money->getHeight()/2-money->getHeight()/2));
}

/*void Avatar::onRequestImgCompleted(HttpClient *sender, HttpResponse *response){
    if (!response) {
        log("onHttpRequestCompleted - No Response");
        return;
    }
    
    if (!response->isSucceed()){
        log("onHttpRequestCompleted - Response failed");
        log("onHttpRequestCompleted - Error buffer: %s", response->getErrorBuffer());
        return;
    }
    std::vector<char> *buffer = response->getResponseData();
    Image * image = new  Image ();
    image-> initWithImageData( reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());
    auto texture = new  Texture2D();
    texture->initWithImage(image);
    
    avatar = Sprite::createWithTexture(texture);
    avatar->setScale((background->getWidth()-10)/avatar->getContentSize().width);
    avatar->setPosition(background->getWidth()/2,background->getHeight()/2);
    this->addChild(avatar);
}*/

void Avatar::addParticle(){
    auto m_emitter=ParticleSystemQuad::create("particle_texture.plist");
    m_emitter->setVisible(true); 
    this->addChild(m_emitter);
    m_emitter->setPosition(Vec2(background->getWidth()/2,background->getHeight()/2));
    m_emitter->runAction(Sequence::create(DelayTime::create(4.0),RemoveSelf::create(), NULL));
}

Vector<SpriteFrame*> Avatar::getAnimation(const char *format, int count) {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++) {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

int Avatar::getPositionIndex(){
	return posIndex;
}

void Avatar::setU(int index,int duration){
    //addParticle();
    auto node = Node::create();
    this->addChild(node);
    
    auto frames = getAnimation("win_%d.png",6);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setPosition(Vec2(background->getWidth()/2,background->getHeight()/2));
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f/10);
    auto repeat =  RepeatForever::create(Animate::create(animation));
    sprite->runAction(repeat);
    node->addChild(sprite);
    
    auto spriteBlur = MSprite::create("sprite_avatar_background.png");
    spriteBlur->setColor(Color3B::BLACK);
    spriteBlur->setOpacity(180);
    spriteBlur->setPosition(Vec2(background->getWidth()/2-spriteBlur->getWidth()/2,
                                background->getHeight()/2-spriteBlur->getHeight()/2));
    node->addChild(spriteBlur);
    
    string text_u = "u1.png";
    if(index == 9){
        text_u = "u2.png";
    }else if(index == 10){
        text_u = "u3.png";
    }else if(index == 8){
        text_u = "u1.png";
    }
    
    auto spriteU = MSprite::create(text_u);
    spriteU->setPosition(Vec2(background->getWidth()/2-spriteU->getWidth()/2,
                                background->getHeight()/2-spriteU->getHeight()/2));
    node->addChild(spriteU);
    
    node->runAction(Sequence::create(DelayTime::create(duration),RemoveSelf::create(), NULL));
}

void Avatar::setWin(int duration){
    
    auto node = Node::create();
    this->addChild(node);
    
    auto frames = getAnimation("win_%d.png",6);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setPosition(Vec2(background->getWidth()/2,background->getHeight()/2));
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f/10);
    auto repeat =  RepeatForever::create(Animate::create(animation));
    sprite->runAction(repeat);
    node->addChild(sprite);
    
    auto spriteWin = MSprite::create("sprite_win.png");
    spriteWin->setPosition(Vec2(background->getWidth()/2-spriteWin->getWidth()/2,
                                background->getHeight()/2-spriteWin->getHeight()/2));
    node->addChild(spriteWin);
    
    node->runAction(Sequence::create(DelayTime::create(duration),RemoveSelf::create(), NULL));
}

void Avatar::setLose(int duration){
    auto spriteLose = MSprite::create("sprite_lose.png");
    spriteLose->setPosition(Vec2(background->getWidth()/2-spriteLose->getWidth()/2,
                                 background->getHeight()/2-spriteLose->getHeight()/2));
    this->addChild(spriteLose);
    spriteLose->runAction(Sequence::create(DelayTime::create(duration),RemoveSelf::create(), NULL));
}

//show bo luot
void Avatar::showPassUp(bool isPassUp){
    spritePassUp->setVisible(isPassUp);
    this->isPassUp = isPassUp;
    if (isPassUp){
        Size avatarSize = background->getContentSize();
        spritePassUp->setPosition(Point::ZERO);
    }
}

Vec2 Avatar::getAvatarPostion(int index,Vec2 origin,Size visibleSize,float buttonHeight){
    Vec2 pos = Vec2(0, 0);
    posIndex = index;
    auto spritez = MSprite::create("nem_gach_da/background_nem.png");
    switch (index) {
        case 3:
            pos = Vec2(origin.x + PADDING + spritez->getWidth(), origin.y + visibleSize.height / 2 - this->getContentSize().height / 2);
            break;
        case 2:
            if(Common::getInstance()->getZoneId() == Common::MAUBINH_ZONE){
                pos = Vec2(origin.x + visibleSize.width / 2 + visibleSize.width* 2 / 12.5f,
                           origin.y + visibleSize.height - this->getContentSize().height - (PADDING + spritez->getHeight()));
            }else{
                pos = Vec2(origin.x + visibleSize.width / 2 - this->getContentSize().width*1.5f,
                           origin.y + visibleSize.height - this->getContentSize().height - (PADDING + spritez->getHeight()));
            }
            break;
        case 1:
            pos = Vec2(origin.x + visibleSize.width - this->getContentSize().width - (PADDING + spritez->getWidth()),
                origin.y + visibleSize.height / 2 - this->getContentSize().height / 2);
            break;
        case 0:
            if(Common::getInstance()->getZoneId() == Common::PHOM_ZONE){
                pos = Vec2(origin.x + visibleSize.width / 2 - visibleSize.width * 5 / 18.0f - this->getContentSize().width,
                           origin.y + 5 + buttonHeight*1.5f + under_money->getHeight());
            }else{
                pos = Vec2(origin.x + visibleSize.width / 2 - visibleSize.width * 6.5f / 18.0f - this->getContentSize().width/2,
                           origin.y + 5 + buttonHeight*1.5f + under_money->getHeight() + 5 + (visibleSize.width / 18) * CARD_RATIO* 0.5f
                           - this->getContentSize().height / 2);
            }
            
            break;
        default:
            break;
    }
    return pos;
}

Vec2 Avatar::getCardCoverPostion(int index, Size avatarSize, Size cardSize){
    Vec2 pos;
    
    switch (index) {
    case 3:
        pos = Vec2(20 + avatarSize.width, avatarSize.height / 2 - cardSize.height / 2);
        break;
    case 2:
        pos = Vec2(20 + avatarSize.width, avatarSize.height / 2 - cardSize.height / 2);
        break;
    case 1:
        pos = Vec2(-20 - cardSize.width, avatarSize.height / 2 - cardSize.height / 2);
        break;
    case 0:
        pos = Vec2(-cardSize.width / 2, -cardSize.height / 4);
        break;
    default:
        break;
    }
    
    return pos;
}

void Avatar::loadCardCover(float width,int index,int numberCard){
    this->is_current_avatar = false;

    float scale = width/spriteCard->getWidth();
    spriteCard->setScale(scale);
    spriteCard->setPosition(this->getCardCoverPostion(index,background->getContentSize(),
                                                 spriteCard->getSize()*scale));
    
    number->setString(StringUtils::format("%d",numberCard));
    number->setPosition(spriteCard->getPosition().x+spriteCard->getWidth()*scale/2-number->getWidth()/2,
                        spriteCard->getPosition().y+spriteCard->getHeight()/2*scale-number->getHeight()/2);
}

void Avatar::setCurrentAvatar(bool isCurrentAvatar){
    this->is_current_avatar = isCurrentAvatar;
}

void Avatar::loadExitRoom(float width, int index, int numberCard){
  float scale = width / exit_room->getWidth();
  exit_room->setScale(scale);
  exit_room->setPosition(this->getCardCoverPostion(index, background->getContentSize(),
    exit_room->getSize()*scale));
}

bool Avatar::getPassUp(){
    return isPassUp;
}

void Avatar::setNumberCard(int _numberCard) {
    if (_numberCard == 0) {
        number->setVisible(false);
        this->numberCard = _numberCard;
        number->setString(StringUtils::format("%d",_numberCard));
        number->setPosition(spriteCard->getPosition().x+spriteCard->getWidth()*spriteCard->getScale()/2-number->getWidth()/2,
                            spriteCard->getPosition().y+spriteCard->getHeight()*spriteCard->getScale()/2-number->getHeight()/2);
        spriteCard->setVisible(false);
    } else {
        this->numberCard = _numberCard;
        number->setString(StringUtils::format("%d",_numberCard));
        number->setPosition(spriteCard->getPosition().x+spriteCard->getWidth()*spriteCard->getScale()/2-number->getWidth()/2,
                            spriteCard->getPosition().y+spriteCard->getHeight()*spriteCard->getScale()/2-number->getHeight()/2);
        number->setVisible(true);

        if (!is_current_avatar){
            spriteCard->setVisible(true);
        }
    }
}

//cap nhat tien hien thi cho avatar, money: so tien hien thi
void Avatar::setMoney(long long _money){
    money->setString(StringUtils::format("%lld $",_money));
    money->setPosition(Vec2(background->getWidth()/2-money->getWidth()/2,
                            under_money->getPosition().y+under_money->getHeight()/2-money->getHeight()/2));
}

int Avatar::getNumberCard(){
    return numberCard;
}

void Avatar::hideCardCover(){
    this->is_current_avatar = true;
    spriteCard->setVisible(false);
    number->setVisible(false);
}

void Avatar::hiddenNumberCardAndCover(bool ishide){
    number->setVisible(!ishide);
    spriteCard->setVisible(!ishide);
}

void Avatar::hideExitRoom(){
  CCLOG("hide card cover");
  exit_room->setVisible(false);
}

void Avatar::onExit() {
    Node::onExit();
}

void Avatar::hideCardCover(bool ishide){
    spriteCard->setVisible(!ishide);
}

void Avatar::hideNumberCard(bool ishide){
    number->setVisible(!ishide);
}

void Avatar::addEvents(){
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p)) {
            return true;
        }
		
		if (this->getChildByTag(TAG_NODE_EMOTICON) != nullptr){
			hiddenInfoExtend();
		}
        return false;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        this->touchEvent(touch);
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Avatar::showObjectThrow(){
	//test
	auto common = Common::getInstance();

	Node* node_emoticon = Node::create();
	node_emoticon->setTag(TAG_NODE_EMOTICON);
    this->addChild(node_emoticon);

	if (player_id != common->getUserId()){
		auto sprite_bg_phao = MSprite::create("nem_gach_da/background_nem.png");
		sprite_bg_phao->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_bg_phao->setPosition(Vec2(-PADDING - sprite_bg_phao->getWidth() / 2, background->getHeight() / 2));
		node_emoticon->addChild(sprite_bg_phao);

		auto sprite_phao = MButton::create("nem_gach_da/sprite_daibac.png", TAG_CLICK_PHAO);
		sprite_phao->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_phao->addTouchEventListener(CC_CALLBACK_2(Avatar::menuCallBack, this));
		sprite_phao->setPosition(sprite_bg_phao->getPosition());
		node_emoticon->addChild(sprite_phao);

		auto sprite_bg_dep = MSprite::create("nem_gach_da/background_nem.png");
		sprite_bg_dep->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_bg_dep->setPosition(Vec2(background->getWidth() + PADDING + sprite_bg_dep->getWidth() / 2,
			background->getHeight() / 2));
		node_emoticon->addChild(sprite_bg_dep);

		auto sprite_dep = MButton::create("nem_gach_da/sprite_dep.png", TAG_CLICK_DEP);
		sprite_dep->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_dep->setPosition(sprite_bg_dep->getPosition());
		sprite_dep->addTouchEventListener(CC_CALLBACK_2(Avatar::menuCallBack, this));
		node_emoticon->addChild(sprite_dep);

		float y = sqrt(pow(background->getWidth() / 2 + PADDING + sprite_bg_phao->getWidth() / 2, 2) - pow(background->getWidth() / 2, 2));
		auto sprite_bg_beer = MSprite::create("nem_gach_da/background_nem.png");
		sprite_bg_beer->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_bg_beer->setPosition(Vec2(0, background->getHeight() / 2 + y));
		node_emoticon->addChild(sprite_bg_beer);

		auto sprite_beer = MButton::create("nem_gach_da/sprite_beer.png", TAG_CLICK_BEER);
		sprite_beer->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_beer->setPosition(sprite_bg_beer->getPosition());
		sprite_beer->addTouchEventListener(CC_CALLBACK_2(Avatar::menuCallBack, this));
		node_emoticon->addChild(sprite_beer);

		auto sprite_bg_cachua = MSprite::create("nem_gach_da/background_nem.png");
		sprite_bg_cachua->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_bg_cachua->setPosition(Vec2(background->getWidth(), background->getHeight() / 2 + y));
		node_emoticon->addChild(sprite_bg_cachua);

		auto sprite_cachua = MButton::create("nem_gach_da/sprite_cachua.png", TAG_CLICK_CACHUA);
		sprite_cachua->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_cachua->setPosition(sprite_bg_cachua->getPosition());
		sprite_cachua->addTouchEventListener(CC_CALLBACK_2(Avatar::menuCallBack, this));
		node_emoticon->addChild(sprite_cachua);

		auto sprite_bg_egg = MSprite::create("nem_gach_da/background_nem.png");
		sprite_bg_egg->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_bg_egg->setPosition(Vec2(0, background->getHeight() / 2 - y));
		node_emoticon->addChild(sprite_bg_egg);

		auto sprite_egg = MButton::create("nem_gach_da/sprite_trung.png", TAG_CLICK_TRUNG);
		sprite_egg->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_egg->setPosition(sprite_bg_egg->getPosition());
		sprite_egg->addTouchEventListener(CC_CALLBACK_2(Avatar::menuCallBack, this));
		node_emoticon->addChild(sprite_egg);

		auto sprite_bg_rose = MSprite::create("nem_gach_da/background_nem.png");
		sprite_bg_rose->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_bg_rose->setPosition(Vec2(background->getWidth(), background->getHeight() / 2 - y));
		node_emoticon->addChild(sprite_bg_rose);

		auto sprite_rose = MButton::create("nem_gach_da/sprite_hoahong.png", TAG_CLICK_ROSE);
		sprite_rose->setAnchorPoint(Point::ANCHOR_MIDDLE);
		sprite_rose->setPosition(sprite_bg_rose->getPosition());
		sprite_rose->addTouchEventListener(CC_CALLBACK_2(Avatar::menuCallBack, this));
		node_emoticon->addChild(sprite_rose);

		if (common->getUserId() == common->getOwnerUserId()){
			//neu la chu phong thi hien thi nut duoi
			auto btn_out = MButton::create("nem_gach_da/btn_extends.png", "Đuổi", 20, TAG_CLICK_USER_OUT);
			btn_out->setTitleFontSize(btn_out->getHeight() / 2);
			btn_out->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
			btn_out->setPosition(Vec2(background->getWidth() / 2, background->getHeight() + 5));
			btn_out->addTouchEventListener(CC_CALLBACK_2(Avatar::btnCallBack, this));
			node_emoticon->addChild(btn_out);
		}
	}

	//add nut info
	auto btn_info_user = MButton::create("nem_gach_da/btn_extends.png", "Thông tin", 20, TAG_CLICK_USER_INFO);
	btn_info_user->setTitleFontSize(btn_info_user->getHeight() / 2);
	btn_info_user->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	btn_info_user->setPosition(Vec2(background->getWidth() / 2, -5));
	btn_info_user->addTouchEventListener(CC_CALLBACK_2(Avatar::btnCallBack, this));
	node_emoticon->addChild(btn_info_user);
}

void Avatar::touchEvent(cocos2d::Touch *touch) {
	if (this->getChildByTag(TAG_NODE_EMOTICON) == nullptr){
		showObjectThrow();  //show cac doi tuong nem, thong tin user va duoi khoi phong
	}
	else {
		hiddenInfoExtend();
	}
}

void Avatar::hiddenInfoExtend(){
	if (this->getChildByTag(TAG_NODE_EMOTICON) != nullptr){
		this->removeChildByTag(TAG_NODE_EMOTICON);
	}
}

void Avatar::btnCallBack(Ref *pSender, ui::Widget::TouchEventType eventType){
	if (eventType == Widget::TouchEventType::ENDED){
		MButton *button = (MButton*)pSender;
		int tag = button->getTag();

		hiddenInfoExtend();

		switch (tag){
		case TAG_CLICK_USER_OUT:
			NetworkManager::getInstance()->getKichPlayerOut(this->roomIndex, (int)this->player_id);
			break;
		case TAG_CLICK_USER_INFO:
			NetworkManager::getInstance()->getViewUserInfoFromServer((int)this->player_id);
			break;
		default:
			break;
		}
	}
}

void Avatar::menuCallBack(Ref *pSender, Widget::TouchEventType eventType) {
	if (eventType == Widget::TouchEventType::ENDED){
		hiddenInfoExtend();

		MButton *button = (MButton*)pSender;
		int tag = button->getTag();

		NetworkManager::getInstance()->getSendTextEmoticonFromServer(tag,(int)player_id);
	}
}

void Avatar::setStatus(string status, int duration) {
    auto sprite_under = MSprite::create("sprite_avatar_background.png");
    sprite_under->setOpacity(200);
    sprite_under->setColor(Color3B::BLACK);
    sprite_under->setPosition(Vec2(background->getWidth()/2-sprite_under->getWidth()/2,
                                 background->getHeight()/2-sprite_under->getHeight()/2));
    this->addChild(sprite_under);
    
    auto mStatus = MLabel::create(status,sprite_under->getWidth()/3);
    mStatus->setPosition(sprite_under->getWidth()/2 - mStatus->getWidth()/2,
                         sprite_under->getHeight()/2 - mStatus->getHeight()/2);
    sprite_under->addChild(mStatus);
    
    sprite_under->runAction(Sequence::create(DelayTime::create(duration),RemoveSelf::create(), NULL));
}
