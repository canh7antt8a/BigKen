#include "XocDiaPlayer.hpp"
#include <ostream>
#include "Utils/Common.h"

XocDiaPlayer::XocDiaPlayer(){

}

XocDiaPlayer::~XocDiaPlayer(){

}

XocDiaPlayer::XocDiaPlayer(string n, string i, int number, long long c, long long g, int pos,
    int tableIndex, int avatarId) : Player(n, i, c, g, avatarId) {
    this->position = pos;
    this->tableIndex = tableIndex;
}

int XocDiaPlayer::getPostion() {
    return this->position;
}

void XocDiaPlayer::setPostion(int position) {
    this->position = position;
}

int XocDiaPlayer::getTableIndex() {
    return this->tableIndex;
}

void XocDiaPlayer::setTableIndex(int tableIndex) {
    this->tableIndex = tableIndex;
}

//bool XocDiaPlayer::operator<(const XocDiaPlayer &right) const {
//    int currentUserId = Common::getInstance()->convertStringToInt(id);
//    int rightUserId = Common::getInstance()->convertStringToInt(right.id);
//    if (currentUserId == Common::getInstance()->getUserId())
//        return true; 
//    if (rightUserId == Common::getInstance()->getUserId())
//        return false;
//    return (tableIndex < right.tableIndex);
//}
