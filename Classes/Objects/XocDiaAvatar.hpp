#ifndef XocDiaAvatar_hpp
#define XocDiaAvatar_hpp

#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "UI/MCircleBar.hpp"
#include "UI/MButton.hpp"
#include "Utils/Common.h"
#include "Utils/TLMNConfig.hpp"
#include "Avatar.hpp"
#include "Card.hpp"
#include <vector>

using namespace std;


class XocDiaAvatar : public Avatar {
public:
    
    virtual bool init();
    virtual void onExit();
    
    CREATE_FUNC(XocDiaAvatar);
    
    void loadAvatar(int index,std::string id,std::string name,std::string money, int roomIndex, int minBet = 0); //chung 
    void setAvatarPostion(int index,Vec2 origin,Size visiableSize);

};
#endif /* XocDiaAvatar_hpp */
