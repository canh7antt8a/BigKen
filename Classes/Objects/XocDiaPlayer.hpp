#ifndef XocDiaPlayer_hpp
#define XocDiaPlayer_hpp

#include <stdio.h>
#include <ostream>
#include "Player.hpp"
#include "Utils/TLMNConfig.hpp"

using namespace std;

class XocDiaPlayer : public Player {
public:
	XocDiaPlayer();
	~XocDiaPlayer();
    XocDiaPlayer(string n, string i, int number, long long c, long long g, int pos, int tableIndex, int avatarId);
    
    int getPostion();
    void setPostion(int position);
    
    int getTableIndex();
    void setTableIndex(int tableIndex);
       
    //bool operator<(const XocDiaPlayer &right) const; 
protected:
    int position;
    int tableIndex;
};

#endif /* XocDiaPlayer_hpp */
