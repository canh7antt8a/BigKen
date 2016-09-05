//
//  Player.hpp
//  MyCards
//
//  Created by hungle on 4/22/16.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <string>

class Player
{
public:
    Player(std::string n, std::string i, long long c, long long g, int h);
    Player();
    ~Player();
    std::string getName();
    std::string getID();
    long long int getCash();
    long long int getGold();
    int getAvatarId();
    
    void setWin(bool _win);

    void setName(std::string n);
    void setID(std::string i);
    
    void setCash(long long int c);
    void setGold(long long int g);
    bool isWin() const; 
    
    //set tien cho nguoi choi la cash hay gold
    void setMoney(bool isCash, long long money);

    virtual void setPostion(int postion) = 0;
    virtual int getTableIndex() = 0;
protected:
    
    std::string name;
    std::string id;
    int avatar_id;
    long long int cash;
    long long int gold;
    bool _win;
};

#endif /* Player_hpp */
