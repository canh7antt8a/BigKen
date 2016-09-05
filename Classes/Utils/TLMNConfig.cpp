//
//  TLMNConfig.cpp
//  MyCards
//
//  Created by Black3rry on 4/9/16.
//
//

#include "TLMNConfig.hpp"

using namespace std;

const int		SCREEN_WIDTH			 = 1280;
const int		SCREEN_HEIGHT			 = 720;

//anh Linh
//const char*  SERVER_NAME = "192.168.100.200";

//stagging server
const char*  SERVER_NAME = "192.168.100.250";

// anh Hai
//const char*  SERVER_NAME = "192.168.100.32";
//const char*  SERVER_NAME = "192.168.1.100";

//real server
//const char*  SERVER_NAME = "103.28.37.24";
const int SERVER_PORT = 1240;

// TLMN

const char* TurnResponseKey[] = { "turnCards", "newTurn", "passUp"};
vector<const char *> soundTLMN = {
    "sounds/tienlen/boqua1.mp3","sounds/tienlen/boqua2.mp3","sounds/tienlen/boqua3.mp3","sounds/tienlen/boqua4.mp3","sounds/tienlen/boqua5.mp3","sounds/tienlen/boqua6.mp3", //0->5
    "sounds/tienlen/chat1.mp3","sounds/tienlen/chat2.mp3","sounds/tienlen/chat3.mp3","sounds/tienlen/chat4.mp3", //6->9
    "sounds/tienlen/danhbo1.mp3","sounds/tienlen/danhbo2.mp3","sounds/tienlen/danhbo3.mp3","sounds/tienlen/danhbo4.mp3","sounds/tienlen/danhbo5.mp3","sounds/tienlen/danhbo6.mp3", //10->15
    "sounds/tienlen/danhdoi1.mp3","sounds/tienlen/danhdoi2.mp3","sounds/tienlen/danhdoi3.mp3","sounds/tienlen/danhdoi4.mp3","sounds/tienlen/danhdoi5.mp3","sounds/tienlen/danhdoi6.mp3", // 16->21
    "sounds/tienlen/danhle1.mp3","sounds/tienlen/danhle2.mp3","sounds/tienlen/danhle3.mp3","sounds/tienlen/danhle4.mp3","sounds/tienlen/danhle5.mp3","sounds/tienlen/danhle6.mp3", // 22->27
    "sounds/tienlen/haine1.mp3","sounds/tienlen/haine2.mp3","sounds/tienlen/haine3.mp3","sounds/tienlen/haine4.mp3", //28->31
    "sounds/tienlen/doihai1.mp3","sounds/tienlen/doihai2.mp3", // 32->33
    "sounds/tienlen/end_game1.mp3","sounds/tienlen/end_game2.mp3", // 34->35
    "sounds/click_card.mp3", //36
    "sounds/chiabai.mp3" }; // 37

vector<const char *> soundPhom = {
    "sounds/phom/anquan1.mp3"
};

vector<int> moneyType = {50, 100, 500, 2000, 5000, 20000};

//COMMON
char* screenshot_path_ios = "";
char* screenshot_path_android = "/sdcard/snapshot.jpg";
