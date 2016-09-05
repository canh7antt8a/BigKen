//
//  MauBinhPlayer.hpp
//  MyCards
//
//  Created by hungle on 8/4/16.
//
//

#ifndef MauBinhPlayer_hpp
#define MauBinhPlayer_hpp

#include <stdio.h>
#include <ostream>
#include "Player.hpp"
#include "Utils/TLMNConfig.hpp"

using namespace std;

class MauBinhPlayer : public Player {
public:
    MauBinhPlayer(std::string n, std::string i, int number, long long c, long long g, int pos, int tableIndex, int avatar_id);
    int getNumberCard();
    void setNumberCard(int number);
    
    int getPostion();
    void setPostion(int postion);
    int getTableIndex();
    void setTableIndex(int _tableIndex);

    
    PlayerState getState();
    void setState(PlayerState state);
    bool operator<(const MauBinhPlayer &right) const;
    void setDraw(bool _draw); 
    bool isDraw() const;
    void setStatus(int _status);
    int getStatus() const; 

    static const int WIN_STATUS = 3; 
    static const int LOSE_STATUS = 2; 
    static const int DRAW_STATUS = 1; 
    static const int NO_STATUS = 0;

protected:
    int numberCard;
    int postion;
    PlayerState state;
    int tableIndex;
    bool _draw; 
    int _status;  //2: lose, 1: draw:, 3: win, 0: no status
};

#endif /* MauBinhPlayer_hpp */
