//
//  ThreeCardPlayer.cpp
//  MyCards
//
//
//

#include "ThreeCardPlayer.hpp"
#include <ostream>
#include "Utils/Common.h"

ThreeCardPlayer::ThreeCardPlayer(string n, string i, int number, long long c, long long g, int pos,
    int tableIndex, int avatarId) : Player(n, i, c, g, avatarId) {
    this->numberCard = number;
    this->position = pos;
    this->tableIndex = tableIndex;
}

int ThreeCardPlayer::getNumberCard() {
    return this->numberCard;
}

void ThreeCardPlayer::setNumberCard(int number){
    this->numberCard = number;
}

int ThreeCardPlayer::getPostion() {
    return this->position;
}

void ThreeCardPlayer::setPostion(int position) {
    this->position = position;
}

int ThreeCardPlayer::getTableIndex() {
    return this->tableIndex;
}

void ThreeCardPlayer::setTableIndex(int tableIndex) {
    this->tableIndex = tableIndex;
}

PlayerState ThreeCardPlayer::getState() {
    return this->state;
}

void ThreeCardPlayer::setState(PlayerState state) {
    this->state = state;
}

bool ThreeCardPlayer::operator<(const ThreeCardPlayer &right) const {
    int currentUserId = Common::getInstance()->convertStringToInt(id);
    int rightUserId = Common::getInstance()->convertStringToInt(right.id);
    if (currentUserId == Common::getInstance()->getUserId())
        return true; 
    if (rightUserId == Common::getInstance()->getUserId())
        return false;
    return (tableIndex < right.tableIndex);
}
