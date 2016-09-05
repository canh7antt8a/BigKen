//
//  Avatar.hpp
//  MyCards
//
//  Created by hungle on 4/22/16.
//
//

#ifndef WaitingPlayer_hpp
#define WaitingPlayer_hpp

#include <cocos2d.h>
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"

using namespace cocos2d;

class WaitingPlayer : public Node {
public:
    
    virtual bool init();
    virtual void onExit();
    
	CREATE_FUNC(WaitingPlayer);
    
    void loadAvatar(int index,std::string id,std::string name,std::string money);

private:
	MSprite* background;
    MSprite* avatar;
    MLabel* name;

public:
	void setPositionAvatar(Vec2 origin, int position);
	void setAvatar(std::string playerName, int index);
	MSprite* getAvatar();
};
#endif /* Avatar_hpp */
