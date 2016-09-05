//
//  PhomPlayer.hpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 6/22/16.
//
//

#ifndef PhomPlayer_hpp
#define PhomPlayer_hpp

#include <stdio.h>
#include <ostream>
#include "Player.hpp"
#include "Utils/TLMNConfig.hpp"

using namespace std;

class PhomPlayer : public Player {
public:
    PhomPlayer(string n, string i, int number, long long c, long long g, int pos, int tableIndex, int avatarId);
    int getNumberCard();
    void setNumberCard(int number);
    
    int getPostion();
    void setPostion(int position);
    
    int getTableIndex();
    void setTableIndex(int tableIndex);
    
    PlayerState getState();
    void setState(PlayerState state);
    
    int getAvatarId();
    void setAvatarId(int id);

    bool operator<(const PhomPlayer &right) const;
    
protected:
    int numberCard;
    int position;
    PlayerState state;
    int tableIndex;
    int avatarId;
};

#endif /* PhomPlayer_hpp */
