#ifndef PositionPlayer_h
#define PositionPlayer_h

#include "cocos2d.h"

using namespace cocos2d;

class PositionPlayer : public cocos2d::Sprite {
private :
	int roomIndex;
	int tableIndex;
	int autoReady = false;
public :
	CREATE_FUNC(PositionPlayer);
	bool init();
	void addEvent();
	void setPositionPlayer(int roomIndex, int tableIndex, Vec2 origin, Size visibleSize);
};

#endif
