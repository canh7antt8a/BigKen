//
//  MListView.hpp
//  MyCards
//
//  Created by hungle on 4/14/16.
//
//

#ifndef MListView_hpp
#define MListView_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "protobufObject/filter_room.pb.h"

using namespace std;
using namespace cocos2d;

class MListView : public ui::ListView {

public:
    static MListView* create(vector<BINRoomPlay> listRoomPlay,string text);
    static MListView* create(vector<BINRoomPlay> listRoomPlay);
    
};

#endif /* MListView_hpp */
