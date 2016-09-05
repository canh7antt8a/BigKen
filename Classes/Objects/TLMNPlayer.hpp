//
//  TLMNPlayer.hpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 5/17/16.
//
//

#ifndef TLMNPlayer_hpp
#define TLMNPlayer_hpp

#include <stdio.h>
#include <ostream>
#include "Player.hpp"
#include "Utils/TLMNConfig.hpp"

using namespace std;

class TLMNPlayer : public Player {
public:
    TLMNPlayer(std::string n, std::string i, int number, long long c, long long g, int pos, int tableIndex, int avatar_id);
    int getNumberCard();
    void setNumberCard(int number);
    
    int getPostion();
    void setPostion(int postion);
    int getTableIndex();
    void setTableIndex(int _tableIndex);
    
    PlayerState getState();
    void setState(PlayerState state);
    bool operator<(const TLMNPlayer &right) const;
protected:
    int numberCard;
    int postion;
    PlayerState state;
    int tableIndex;
};

#endif /* TLMNPlayer_hpp */
