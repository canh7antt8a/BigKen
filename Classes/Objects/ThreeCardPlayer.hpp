//
//  PhomPlayer.hpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 6/22/16.
//
//

#ifndef ThreeCardPlayer_hpp
#define ThreeCardPlayer_hpp

#include <stdio.h>
#include <ostream>
#include "Player.hpp"
#include "Utils/TLMNConfig.hpp"

using namespace std;

class ThreeCardPlayer : public Player {
public:
    ThreeCardPlayer(string n, string i, int number, long long c, long long g, int pos, int tableIndex, int avatarId);

    int getNumberCard();
    void setNumberCard(int number);
    
    int getPostion();
    void setPostion(int position);
    
    int getTableIndex();
    void setTableIndex(int tableIndex);
       
    PlayerState getState();
    void setState(PlayerState state);
    bool operator<(const ThreeCardPlayer &right) const; 
protected:
    int numberCard;
    int position;
    int tableIndex;
    PlayerState state;
};

#endif /* ThreeCardPlayer_hpp */
