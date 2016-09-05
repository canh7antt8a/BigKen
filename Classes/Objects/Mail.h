#ifndef Mail_hpp
#define Mail_hpp

#include <string>

using namespace std;

class Mail
{
private:
    long mailId;
    long senderUserId;
    string senderUserName;
    long recipientUserId;
    string recipientUserName;
    string title;
    string body;
    string sentTime;
    bool readed;
    int attachItemId;
    long attachItemQuatity;
    string expiredTime;
public:
    Mail();
    ~Mail();
    void setMailId(long mailId);
    long getMailId();
    void setSenderUserId(long senderUserId);
    long getSenderUserId();
    void setSenderUserName(string senderUserName);
    string getSenderUserName();
    void setRecipientUserId(long recipientUserId);
    long getRecipientUserId();
    void setRecipientUserName(string recipientUserName);
    string getRecipientUserName();
    void setTitle(string title);
    string getTitle();
    void setBody(string body);
    string getBody();
    void setSentTime(string sentTime);
    string getSentTime();
    void setReaded(bool readed);
    bool getReaded();
    void setAttachItemId(int attachItemId);
    int getAttachItemId();
    void setAttachItemQuatity(long attachItemQuatity);
    long getAttachItemQuatity();
    void setExpiredTime(string expiredTime);
    string getExpiredTime();
};

#endif