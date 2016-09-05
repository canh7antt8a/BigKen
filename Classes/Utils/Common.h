#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "protobufObject/enter_zone.pb.h"
#include "protobufObject/update_user_setting.pb.h"
#include <ctime>

using namespace std;

class Common {
public:
    static Common* getInstance();
    Common(string = "", string = "", string = "", string = "", string = "",
        string = "", string = "", int = 0, int = 0, string = "-1", int = -1);
    ~Common();

    string getDeviceId() const;
    string getUserIdFacebook() const;
    string getUserNameFacebook() const;
    string getTokenFacebook() const;
    string getDeviceInfo() const;
    string getAppVersion() const;
    string getCp() const;
    string getLanguage() const;
    string getCountry() const;
    string getIpaddress() const;
    string getSessionId();
    string convertIntToString(int var);
    string convertIntToMoneyView(int var);
    string convertIntToMoneyView100k(int var);
	void callPhone(string myPhone);
    std::string getPackageName();
    long long getCurrentTime() const;
    void setSessionId(string sessionId);
    google::protobuf::Message* checkEvent(int);
    

    int getOS();

    int getZoneId();
    void setZoneId(int zoneId);

    int getChannelId();
    int getRoomIndex();
    int getUserId();
    void closeApp();
    void swap(int &x, int &y);
    void shareContentFace(const std::string& filePath);

    char* getScreenShotPath();

    char* getNetworkStrength();
    
    void setGameTag(int gameTag);
    int getGameTag();
    
    /* userInfo */
    void setUserName(std::string userName);
    std::string getUserName();
    
    void setDisplayName(std::string displayName);
    std::string getDisplayName();
    
    void setCash(long long cash);
    long long getCash();
    void setNewPhone(string phone);
    string getNewPhone();
    void setGold(long long gold);
    long long getGold();
    
    void setAvatarId(int avatarId);
    int getAvatarId();
    
    void setLevel(int level);
    int getLevel();
    
    void setAutoReady(bool autoReady);
    bool isAutoRead();
    
    void setAutoDenyInvitation(bool autoDenyInvitation);
    bool isAutoDenyInvitation();

	void setPhoneNunber(std::string phoneNumber);
	std::string getPhoneNumber();
    
    void setCashRoomList(vector<BINRoomConfig> cashRoomList);
    vector<BINRoomConfig> getCashRoomList();
    
    void setGoldRoomList(vector<BINRoomConfig> goldRoomList);
    vector<BINRoomConfig> getGoldRoomList();

	/*Common Function */
	string convertListCardToString(vector<int> _card_values);
	vector<string> split(string str, char delimiter);
	vector<int> convertStringsToInt(vector<string> str);
	int convertStringToInt(string str);
    
	bool to_bool(std::string str);
    std::string boolToString(bool value);
	string convertMillisecondToTime(long long milliseconds);
	string convertMillisecondToTime(long long milliseconds, string fomat);
    void setIdle(bool _idle);
    bool isIdle() const;
    void sleep(int milliseconds);
    
    void removeElement(vector<int> &vector, int a);

    vector<char> decompress_gzip2(const char* byte_arr, int length);

	std::string convertLongToCurrency(long money);
	std::string numberFormatWithCommas(long long value);

	/*Common Constant*/
	std::string getTitleGame();
    
    int getOwnerUserId() const;
    void setOwnerUserId(const int ownerUserId);
	void setRoomIndex(int roomIndex);
    vector<pair<int, int>> parseBetMoney(int money);

    bool isEnabledPurchaseCash() const; 
    bool isEnabledTopup() const; 
    void setEnablePurchaseCash(bool _enablePurchaseCash);
    void setEnableTopup(bool _enableTopup);

    static char* KEY_SESSION_ID;
    static char* KEY_USER_ID; 
    static const int FREE_ROOM_GROUP_ID = 5003;
    static const int VIP_ROOM_GROUP_ID = 5002;
    static char* NO_DEVICE;

    static int FACEBOOK_CHANNEL;
    static int GOOGLE_CHANNEL;
    static int TIENLENMIENNAM_ZONE;
    static int BACAY_ZONE;
    static int XITO_ZONE;
    static int POKER_ZONE;
    static int PHOM_ZONE;
    static int COTUONG_ZONE;
    static int CARO_ZONE;
    static int BAUCUA_ZONE;
    static int CHAN_ZONE;
    static int SAM_ZONE;
    static int LIENG_ZONE;
    static int MAUBINH_ZONE;
    static int XENG_ZONE;
    static int XOCDIA_ZONE;
// filed update
    static int UPDATE_DISPLAY_NAME;
    static int UPDATE_EMAIL;
    static int UPDATE_PHONE;
    static int UPDATE_IDENTIFY;
    static int UPDATE_AVATAR;
    static int UPDATE_PASSWORD;
//    static int XITO_ZONE;
private:
	static Common* instance; 
	std::string device_id; 
	std::string device_info; 
	std::string app_version; 
	std::string cp; 
	std::string language; 
	std::string country; 
	std::string ipaddress; 
	std::string sessionId;
    bool _autoReady = false;
    bool _autoDenyInvitation = false;
	char* screenshot_path;
	int os;
	int channelId;
	int roomIndex;
	char* networkStrength;
    int ownerUserId;
    std::string userName;
    std::string displayName;
    bool _idle;
    long long cash;
    long long gold;
    string new_phone;
    int avatarId;
    int level;
    int gameTag;
    int _zoneId = -1;
	std::string phoneNumber;
    bool _enablePurChaseCash;
    bool _enableTopup; 
    
    vector<BINRoomConfig> cashRoomList;
    vector<BINRoomConfig> goldRoomList;
    
};

#endif // __COMMON_H__
