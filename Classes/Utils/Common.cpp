#include "Common.h"
#include <string>

#define TEST_ENVIRONMENT 0
#define IOS 2
#define ANDROID 1

#include "NetworkManager.h"
#include <chrono>
#include "cocos2d.h"
#include "platform/android/jni/JniLink.h"
#include "platform/ios/NativeUtility.h"
#include "TLMNConfig.hpp"
#include <sstream>
#include <stdexcept>
#include "zlib.h"
#include <ctime>
#include "Utils/LoadingManager.hpp"

#define MOD_GZIP_ZLIB_WINDOWSIZE 15
#define MOD_GZIP_ZLIB_CFACTOR    9
#define MOD_GZIP_ZLIB_BSIZE      8096

USING_NS_CC;

using namespace std;
using namespace std::chrono; 

Common::Common(std::string device_id, std::string device_info, std::string
    app_version, std::string cp, std::string country, std::string language,
    std::string ipaddress, int os, int channelId, std::string sessionId, 
    int roomIndex) {
    this->device_id = device_id; 
    this->device_info = device_info; 
    this->app_version = app_version; 
    this->cp = cp; 
    this->country = country; 
    this->language = language; 
    this->ipaddress = ipaddress; 
    this->os = os; 
    this->channelId = channelId; 
    this->sessionId = sessionId; 
    this->roomIndex = roomIndex; 
    this->_idle = false;
}

Common::~Common() {
}

int Common::FACEBOOK_CHANNEL = 1;
int Common::GOOGLE_CHANNEL = 2;
int Common::BACAY_ZONE = 1;
int Common::XITO_ZONE = 2;
int Common::POKER_ZONE = 3;
int Common::PHOM_ZONE = 4;
int Common::TIENLENMIENNAM_ZONE = 5;
int Common::COTUONG_ZONE = 6;
int Common::CARO_ZONE = 7;
int Common::BAUCUA_ZONE = 8;
int Common::CHAN_ZONE = 9;
int Common::SAM_ZONE = 10;
int Common::LIENG_ZONE = 11;
int Common::MAUBINH_ZONE = 12;
int Common::XENG_ZONE = 13;
int Common::XOCDIA_ZONE = 15;
char* Common::KEY_SESSION_ID = "key_session_id";
char* Common::KEY_USER_ID = "key_user_id";
char* Common::NO_DEVICE = "NO_DEVICE";

int Common::UPDATE_DISPLAY_NAME = 1;
int Common::UPDATE_EMAIL = 2;
int Common::UPDATE_PHONE = 3;
int Common::UPDATE_IDENTIFY = 4;
int Common::UPDATE_AVATAR = 5;
int Common::UPDATE_PASSWORD = 6;
int Common::getUserId() {
    return cocos2d::UserDefault::getInstance()->getIntegerForKey(Common::KEY_USER_ID);
}


void Common::sleep(int milliseconds)
{
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

vector<char> Common::decompress_gzip2(const char* byte_arr, int length) {

    vector<char> result;
    vector<char> nil_vector;
    if (length == 0) return nil_vector;
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    zs.next_in = (Bytef*)byte_arr;
    zs.avail_in = length;
    zs.total_out = 0;
    zs.zalloc = Z_NULL;
    zs.zfree = Z_NULL;

    if (inflateInit2(&zs, MOD_GZIP_ZLIB_WINDOWSIZE + 16) != Z_OK)  return nil_vector;

    int ret;

    char outbuffer[32768];

    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = inflate(&zs, Z_SYNC_FLUSH);

        if (result.size() < zs.total_out) {
            int size = (int)result.size();
            for (int i = 0; i < zs.total_out - size; i++)
                result.push_back(outbuffer[i]);
        }

    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
            << zs.msg;
        return nil_vector;
    }
    return result;
}

void Common::swap(int &x, int &y) {
    int tmp = x; 
    x = y; 
    y = tmp; 
}

void Common::setIdle(bool _idle) {
    this->_idle = _idle; 
}

bool Common::isIdle() const {
    return this->_idle; 
}

std::string Common::getSessionId() {
    if (sessionId == "-1") {
        sessionId = cocos2d::UserDefault::getInstance()->getStringForKey(Common::KEY_SESSION_ID);
    }
    return sessionId;
}

std::string Common::getPackageName() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return NativeUtility::getBundleId();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return GetPackageName();
#endif
    return "com.kinggame.bigken";
}

bool Common::isEnabledPurchaseCash() const {
    return this->_enablePurChaseCash; 
}

bool Common::isEnabledTopup() const {
    return _enableTopup;
}

void Common::setEnablePurchaseCash(bool _enablePurchaseCash) {
	this->_enablePurChaseCash = _enablePurchaseCash;
}

void Common::setEnableTopup(bool _enableTopup) {
    this->_enableTopup = _enableTopup; 
}

std::string Common::convertIntToString(int var) {
    char buffer[20];
    sprintf(buffer, "%d", var);
    std::string var_string = std::string(buffer);
    return var_string;
}

std::string Common::convertIntToMoneyView(int var) {
  int i = 0;
  vector<string> end = { "", "K", "M", "B" };
  while (var > 1000){
    var = var/1000;
    i++;
  }
  char buffer[15];
  sprintf(buffer, "%d", var);
  std::string var_string = std::string(buffer);
  return var_string + " " + end[i];
}

//duoi 100000 thi hien thi 100.000 
//>= 100000 thi hien thi 100k
std::string Common::convertIntToMoneyView100k(int var) {  
	int i = 0;
	vector<string> end = { "", "K", "M", "B" };

	if (var < 100000){
		return numberFormatWithCommas(var);
	}

	while (var > 1000){
		var = var / 1000;
		i++;
	}
	
	char buffer[15];
	sprintf(buffer, "%d", var);
	std::string var_string = std::string(buffer);
	return var_string + " " + end[i];
}

void Common::setSessionId(std::string _sessionid) {
    sessionId = _sessionid; 
}

/* Singleton pattern */
Common* Common::instance = 0; 
Common* Common::getInstance() {
    if (!instance) {
        instance = new Common(); 
    }
    return instance;
}


std::string Common::getDeviceId() const {
    /*if (TEST_ENVIRONMENT)
        return "00000000";*/
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
          return NativeUtility::deviceID();
    #endif
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
          return GetIdJNI();
    #endif
    return "";
}

std::string Common::getDeviceInfo() const {
    /*if (TEST_ENVIRONMENT)
        return "Samsung Galaxy S2";*/
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return NativeUtility::deviceName();
    #endif
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        return GetNameJNI();
    #endif
        return NO_DEVICE;
}

std::string Common::getAppVersion() const {
    //if (TEST_ENVIRONMENT)
        //return "1";
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return NativeUtility::appVersion();
    #endif
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        return GetVersionApp();
    #endif
        return "1";
}

// lay user_id nguoi dung facebook khi dang nhap
std::string Common::getUserIdFacebook() const {
    //if (TEST_ENVIRONMENT)
       // return "1";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return NativeUtility::getFacebookId();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return callLoginFacebook();
#endif
    return "1";
}

// lay user_id nguoi dung facebook khi dang nhap
std::string Common::getUserNameFacebook() const {
    //if (TEST_ENVIRONMENT)
    // return "1";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return NativeUtility::getFacebookName();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return callLoginFacebook();
#endif
    return "1";
}

void Common::callPhone(string myPhone){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return NativeUtility::callPhoneNumber(myPhone);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return CallMobileJNI(myPhone.c_str());
#endif
}

//lay token facebook sau khi dang nhap
std::string Common::getTokenFacebook() const {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NativeUtility::getAccessToken();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return GetTokenFacebook();
#endif
    return "1";
}

//chia se anh len facebook
//filePath: duong dan anh
void Common::shareContentFace(const std::string& filePath) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    shareFace(filePath);
#endif
}

//lay ra duong dan anh chup man hinh
char* Common::getScreenShotPath(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    screenshot_path = screenshot_path_ios;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    screenshot_path = screenshot_path_android;
#endif
    
    return screenshot_path;
}

//lay ra do manh yeu cua song wifi or 3g
char* Common::getNetworkStrength(){

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    networkStrength = GetNetworkStrength();
#endif
    return networkStrength;

}

std::string Common::getCp() const  {
    // if (TEST_ENVIRONMENT)
        return "1";
    
}

std::string Common::convertLongToCurrency(long money){
	stringstream ss;
	ss.imbue(locale(""));
	ss << std::fixed << money;
	CCLOG("convertLongToCurrency: %s", ss.str().c_str());
	return ss.str();
}

std::string Common::numberFormatWithCommas(long long value){
	if (value < 0){
		value = 0;
	}
	struct Numpunct : public std::numpunct<char>{
	protected:
		virtual char do_thousands_sep() const{ return '.'; }
		virtual string do_grouping() const{ return "\03"; }
	};
	stringstream ss;
	ss.imbue({ locale(), new Numpunct });
	ss << std::fixed << value;
	return ss.str();
}

void Common::closeApp(){
    NetworkManager::getInstance()->closeConnection();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    cocos2d::MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

google::protobuf::Message* Common::checkEvent(int message_id) {
    std::mutex mtx;
    try {
//      bool isSuccess = false;
        int k = -1; 
        std::pair<google::protobuf::Message*, int> result;
        mtx.lock();
        int list_event_len = NetworkManager::listEvent.size();
        for (int i = 0; i< list_event_len; i++) {
          //  CCLOG("len: %d, index: %d, size: %d", list_event_len, i, NetworkManager::listEvent.size());
            if (!NetworkManager::listEvent.empty() && 
                NetworkManager::listEvent[i].second == message_id){
                result = NetworkManager::listEvent[i];
                k = i;
                break;
            }
        }

		if (k != -1 && !NetworkManager::listEvent.empty()) {
			CCLOG("BaseScene hideLoading()");
			LoadingManager::getInstance()->hideLoading();
			NetworkManager::listEvent.erase(NetworkManager::listEvent.begin() + k);
		}
            
        mtx.unlock();
        
        if (k != -1) { //found
            return result.first;
        }
        return 0;
    }
    catch (...) {
        return 0;
    }
}

std::string Common::getCountry() const {
    // if (TEST_ENVIRONMENT)
        return "vn";
    
}

std::string Common::getLanguage() const {
    // if (TEST_ENVIRONMENT)
        return "vi";
}

std::string Common::getIpaddress() const {
    // if (TEST_ENVIRONMENT)
        return "127.0.0.1";
}

int Common::getOS()  {
    if (os == 0) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        os = ANDROID;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        os =IOS;
#else
        os = IOS;
#endif
    }
    return os; 
}

long long Common::getCurrentTime() const {

    milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
        );
    return ms.count();
}

int Common::getZoneId() {
    int result = -1;
    //CCLOG("%d", this->gameTag);
    switch (this->gameTag)
    {
        case TAG_SHOW_GAME_SAM:
            result = Common::SAM_ZONE;
            break;
        case TAG_SHOW_GAME_POCKER:
            result = Common::POKER_ZONE;
            break;
        case TAG_SHOW_GAME_PHOM:
            result = Common::PHOM_ZONE;
            break;
        case TAG_SHOW_GAME_TLMN:
            result = Common::TIENLENMIENNAM_ZONE;
            break;
        case TAG_SHOW_GAME_BACAY:
            result = Common::BACAY_ZONE;
            break;
        case TAG_SHOW_GAME_XITO:
            result = Common::XITO_ZONE;
            break;
        case TAG_SHOW_GAME_XOCDIA:
            result = Common::XOCDIA_ZONE;
            break;
        case TAG_SHOW_GAME_MAUBINH: 
            result = Common::MAUBINH_ZONE; 
            break;
        default:
            result = Common::TIENLENMIENNAM_ZONE;
            break;
    }
    return _zoneId != -1 ? _zoneId : result;
}

void Common::setZoneId(int zoneId) {
    _zoneId = zoneId;
}

int Common::getChannelId() {
    if (channelId == 0) {
        if (TEST_ENVIRONMENT)
            channelId = Common::FACEBOOK_CHANNEL; //Facebook
    }
    return channelId;
}

/* Common Function */

std::string Common::convertListCardToString(vector<int> _card_values) {
    std::string result = "";
    try {
        char *_convert = new char[20];
        if (_card_values.size() > 0) {
            for (int i = 0; i < _card_values.size() - 1; i++) {
                //int number = _card_values[i];
                sprintf(_convert, "%d", _card_values[i]);
                result += _convert;
                result += ',';
            }
            sprintf(_convert, "%d", _card_values.back());
            result += _convert;
            CCLOG("list card string: %s", result.c_str());
            delete[] _convert;
            return result;
        }
        return "";
    }
    catch (...) {
        return "";
    }
}


vector<string> Common::split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;


    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    return internal;
}

vector<int> Common::convertStringsToInt(vector<string> str) {
    vector<int>result;
    for (int i = 0; i < str.size(); i++) {
        int numb;
        istringstream(str[i]) >> numb;
        result.push_back(numb);
    }
    return result;
}


bool Common::to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

std::string Common::boolToString(bool value) {
    return value ? "true" : "false";
}

int Common::convertStringToInt(string str){
    int convert_int;
    std::stringstream ss(str);
    ss >> convert_int;
    return convert_int;
}

string Common::convertMillisecondToTime(long long milliseconds){
    time_t now = static_cast<time_t>(milliseconds / 1000);
    struct tm * timeinfo = localtime(&now);

    char output[30];
    strftime(output, 30, "%H:%M %d/%m/%Y", timeinfo);

    return string(output);
}

string Common::convertMillisecondToTime(long long milliseconds, string fomat){
	time_t now = static_cast<time_t>(milliseconds / 1000);
	struct tm * timeinfo = localtime(&now);

	char output[30];
	strftime(output, 30, fomat.c_str(), timeinfo);

	return string(output);
}

int Common::getOwnerUserId() const {
    return this->ownerUserId;
}

void Common::setOwnerUserId(const int ownerUserId) {
    this->ownerUserId = ownerUserId;
}

std::string Common::getUserName() {
    return this->userName;
}

void Common::setUserName(std::string userName) {
    this->userName = userName;
}

std::string Common::getDisplayName() {
    return this->displayName;
}

void Common::setDisplayName(std::string displayName) {
    this->displayName = displayName;
}

int Common::getLevel() {
    return this->level;
}

void Common::setLevel(int level) {
    this->level = level;
}

long long Common::getGold() {
    return this->gold;
}
string Common::getNewPhone(){
    return this->new_phone;
}
void Common::setNewPhone(string new_phone){
    this->new_phone = new_phone;
}

void Common::setGold(long long gold) {
    this->gold = gold;
}

int Common::getAvatarId() {
    if (this->avatarId < 100000){
        return 0;
    }
    return this->avatarId;
}

void Common::setAvatarId(int avatarId) {
    this->avatarId = avatarId;
}

void Common::setPhoneNunber(std::string phoneNumber){
	this->phoneNumber = phoneNumber;
}

std::string Common::getPhoneNumber(){
	return this->phoneNumber;
}

long long Common::getCash() {
    return this->cash;
}

void Common::setCash(long long cash) {
    this->cash = cash;
}

int Common::getRoomIndex(){
    return roomIndex;
}

void Common::setRoomIndex(int roomIndex){
    this->roomIndex = roomIndex;

}

void Common::setCashRoomList(vector<BINRoomConfig> cashRoomList) {
    this->cashRoomList = cashRoomList;
}

vector<BINRoomConfig> Common::getCashRoomList() {
    return this->cashRoomList;
}

void Common::setGoldRoomList(vector<BINRoomConfig> goldRoomList) {
    this->goldRoomList = goldRoomList;
}

vector<BINRoomConfig> Common::getGoldRoomList() {
    return this->goldRoomList;
}

void Common::setAutoReady(bool autoReady) {
    this->_autoReady = autoReady;
}

bool Common::isAutoRead() {
    return this->_autoReady;
}

void Common::setAutoDenyInvitation(bool autoDenyInvitation) {
    this->_autoDenyInvitation = autoDenyInvitation;
}

bool Common::isAutoDenyInvitation() {
    return this->_autoDenyInvitation;
}

void Common::setGameTag(int gameTag) {
    this->gameTag = gameTag;
}

int Common::getGameTag() {
    return this->gameTag;
}

std::string Common::getTitleGame(){
	std::string title_game = "";

    int zoneId = Common::getInstance()->getZoneId();

	if (zoneId == Common::TIENLENMIENNAM_ZONE){
		title_game = TXT_TITLE_GAME_TLMN;
	}
    else if (zoneId == Common::PHOM_ZONE){
		title_game = TXT_TITLE_GAME_PHOM;
	}
    else if (zoneId == Common::BACAY_ZONE){
		title_game = TXT_TITLE_GAME_BACAY;
	}
    else if (zoneId == Common::XOCDIA_ZONE){
		title_game = TXT_TITLE_GAME_XOCDIA;
    }
    else if (zoneId == Common::MAUBINH_ZONE) {
        title_game = TXT_TITLE_GAME_MAUBINH;
    }
	return title_game;
}

void Common::removeElement(vector<int> &myVector, int a) {
    for (vector<int>::iterator it = myVector.begin(); it != myVector.end(); it++) {
        if (*it == a) {
            myVector.erase(it);
            break;
        }
    }
}

vector<pair<int, int>> Common::parseBetMoney(int money) {
    vector<pair<int, int>> result; 
    int tmp = money; 
    for (int i = moneyType.size() - 1; i >= 0; i--) {
        if (tmp >= moneyType[i]) {
            int count = tmp / moneyType[i];
            tmp -= count * moneyType[i];
            result.push_back(std::make_pair(moneyType[i], count));
        }
    }
    return result; 
}
