//
//  PhomPlayer.cpp
//  MyCards
//
//  Created by Hoàng Bắc Phùng on 6/22/16.
//
//

#include "PhomPlayer.hpp"
#include <ostream>

PhomPlayer::PhomPlayer(string n, string i, int number, long long c, long long g, int pos,
    int tableIndex, int avatarId) : Player(n, i, c, g, avatarId) {
    this->numberCard = number;
    this->position = pos;
    this->tableIndex = tableIndex;
    this->avatarId = avatarId;
}

int PhomPlayer::getNumberCard() {
    return this->numberCard;
}

void PhomPlayer::setNumberCard(int number){
    this->numberCard = number;
}

int PhomPlayer::getPostion() {
    return this->position;
}

void PhomPlayer::setPostion(int position) {
    this->position = position;
}

int PhomPlayer::getTableIndex() {
    return this->tableIndex;
}

void PhomPlayer::setTableIndex(int tableIndex) {
    this->tableIndex = tableIndex;
}

PlayerState PhomPlayer::getState() {
    return this->state;
}

void PhomPlayer::setState(PlayerState state) {
    this->state = state;
}

int PhomPlayer::getAvatarId() {
    return this->avatarId;
}

void PhomPlayer::setAvatarId(int id) {
    this->avatarId = id;
}

bool PhomPlayer::operator<(const PhomPlayer &right) const {
    return (tableIndex < right.tableIndex);
}
