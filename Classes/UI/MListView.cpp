//
//  MListView.cpp
//  MyCards
//
//  Created by hungle on 4/14/16.
//
//

#include "MListView.hpp"

using namespace cocos2d;

MListView* MListView::create(vector<BINRoomPlay> listRoomPlay){
    MListView* listview = (MListView*)ui::ListView::create();
   
    return listview;
}

/*

 lvRight = ListView::create();
 for (int i=0; i<20; i++)
 {
 auto bkg_item = Sprite::create("bgr_list_item.png");
 auto number_table = MLabel::create("6",30);
 auto money = MLabel::create("1000 xu",30);
 auto status = MLabel::create("xxx",30);
 
 auto lock = Sprite::create("ic_lock.png");
 auto custom_item = Layout::create();
 
 custom_item->setContentSize(Size(layoutRight->getContentSize().width,lock->getContentSize().height*2));
 
 bkg_item->setScale(layoutRight->getContentSize().width/bkg_item->getContentSize().width,
 lock->getContentSize().height*2/bkg_item->getContentSize().height);
 bkg_item->setPosition(layoutRight->getContentSize().width/2,custom_item->getContentSize().height/2);
 
 number_table->setPosition(Vec2(number_table->getContentSize().width/2+backgroundRight->getContentSize().width/8,
 custom_item->getContentSize().height / 2.0f-number_table->getContentSize().height/2));
 money->setPosition(Vec2(money->getContentSize().width/2+backgroundRight->getContentSize().width*2.5f/8,
 custom_item->getContentSize().height / 2.0f-money->getContentSize().height/2));
 status->setPosition(Vec2(status->getContentSize().width/2+backgroundRight->getContentSize().width*5/8,
 custom_item->getContentSize().height / 2.0f-status->getContentSize().height/2));
 lock->setPosition(Vec2(lock->getContentSize().width/2+backgroundRight->getContentSize().width*7/8,
 custom_item->getContentSize().height / 2.0f));
 
 custom_item->addChild(bkg_item);
 custom_item->addChild(number_table);
 custom_item->addChild(money);
 custom_item->addChild(status);
 custom_item->addChild(lock);
 custom_item->setTouchEnabled(true);
 lvRight->pushBackCustomItem(custom_item);
 }
 lvRight->setItemsMargin(15);
	lvRight->addEventListener([this](Ref* sender, ui::ListView::EventType type){
 CCLOG("123");
	});
 
	[this](Ref* sender, ui::ListView::EventType type) {
 if (type == ui::ListView::EventType::ON_SELECTED_ITEM_END){
 CCLOG("scrolViewCallback %s", "CLicked!");
 }
	}
*/