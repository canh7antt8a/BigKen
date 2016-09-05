
#include "Mail.h"

Mail::Mail(){

}

Mail::~Mail()
{
}

void Mail::setMailId(long mailId){
    this->mailId = mailId;
}

long Mail::getMailId(){
    return this->mailId;
}

void Mail::setSenderUserId(long senderUserId){
    this->senderUserId = senderUserId;
}

long Mail::getSenderUserId(){
    return this->senderUserId;
}

void Mail::setSenderUserName(string senderUserName){
    this->senderUserName = senderUserName;
}

string Mail::getSenderUserName(){
    return this->senderUserName;
}

void Mail::setRecipientUserId(long recipientUserId){
    this->recipientUserId = recipientUserId;
}

long Mail::getRecipientUserId(){
    return this->recipientUserId;
}

void Mail::setRecipientUserName(string recipientUserName){
    this->recipientUserName = recipientUserName;
}

string Mail::getRecipientUserName(){
    return this->recipientUserName;
}

void Mail::setTitle(string title){
    this->title = title;
}

string Mail::getTitle(){
    return this->title;
}

void Mail::setBody(string body){
    this->body = body;
}

string Mail::getBody(){
    return this->body;
}

void Mail::setSentTime(string sentTime){
    this->sentTime = sentTime;
}

string Mail::getSentTime(){
    return this->sentTime;
}

void Mail::setReaded(bool readed){
    this->readed = readed;
}

bool Mail::getReaded(){
    return this->readed;
}

void Mail::setAttachItemId(int attachItemId){
    this->attachItemId = attachItemId;
}

int Mail::getAttachItemId(){
    return this->attachItemId;
}

void Mail::setAttachItemQuatity(long attachItemQuatity){
    this->attachItemQuatity = attachItemQuatity;
}

long Mail::getAttachItemQuatity(){
    return this->attachItemQuatity;
}

void Mail::setExpiredTime(string expiredTime){
    this->expiredTime = expiredTime;
}

string Mail::getExpiredTime(){
    return this->expiredTime;
}