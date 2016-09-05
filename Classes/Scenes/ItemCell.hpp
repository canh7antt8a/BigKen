//
//  ItemCell.hpp
//  MyCards
//
//  Created by hungle on 5/25/16.
//
//

#ifndef ItemCell_hpp
#define ItemCell_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Scenes/SceneTable.hpp"

using namespace cocos2d;

class ItemCell : public Node {
    
public:
    
    ItemCell();
    virtual ~ItemCell();
    
    bool init();
    
    static ItemCell* create(int index, bool passwordRequired, float width, float height,int minBet, int number_user,
		bool isVipRoom, int max_number_user, long long minEnterMoney);
    
    virtual void onExit();
    
    float getWidth();
    float getHeight();
    
private:
    SceneTable* sceneTable;
    cocos2d::Vec2 getPostion();
};



#endif /* ItemCell_hpp */
