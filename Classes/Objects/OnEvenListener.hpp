//  OnEvenListener.hpp

#ifndef OnEvenListener_hpp
#define OnEvenListener_hpp

#include "cocos2d.h"
using namespace cocos2d;

template <typename R>
class OnEvenListener{
public:
	const int EVENT_CONFIRM_OK = 1000;
	const int EVENT_CONFIRM_BUY_CHUONG = 1001;
	const int EVENT_CONFIRM_SELL_CHUONG = 1002;
	const int EVENT_CANCEL_CONFIRM = 1003;
public:
	virtual void onEvent(int enventType, R sender) = 0;
};

#endif /* OnEvenListener_hpp */
