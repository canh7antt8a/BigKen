#include <vector>
#include <string>
#include <queue>

#if WIN32
    #pragma comment(lib, "libprotobuf.lib")
#endif


#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <thread>
#include <mutex>
#include <protobufObject/map_field_entry.pb.h>


#include "protobufObject/register.pb.h"
#include "protobufObject/initialize.pb.h"
#include "protobufObject/login.pb.h"
#include "protobufObject/logout.pb.h"
#include "protobufObject/ping.pb.h"
#include "protobufObject/quick_play.pb.h"
#include "protobufObject/session_expired.pb.h"
#include "protobufObject/open_id_login.pb.h"
#include "protobufObject/enter_zone.pb.h"
#include "protobufObject/player.pb.h"
#include "protobufObject/session_expired.pb.h"
#include "protobufObject/filter_room.pb.h"
#include "protobufObject/enter_room.pb.h"
#include "protobufObject/create_room.pb.h"
#include "protobufObject/start_match.pb.h"
#include "protobufObject/turn.pb.h"
#include "protobufObject/exit_room.pb.h"
#include "protobufObject/room_owner_changed.pb.h"
#include "protobufObject/match_begin.pb.h"
#include "protobufObject/match_end.pb.h"
#include "protobufObject/update_money.pb.h"
#include "protobufObject/prepare_new_match.pb.h"
#include "protobufObject/room_owner_changed.pb.h"
#include "protobufObject/kick_player_out.pb.h"
#include "protobufObject/ready_to_play.pb.h"
#include "protobufObject/update_user_info.pb.h"
#include "protobufObject/lock_room.pb.h"
#include "protobufObject/filter_top_user.pb.h"
#include "protobufObject/friend.pb.h"
#include "protobufObject/change_rule.pb.h"
#include "protobufObject/lookup_money_history.pb.h"
#include "protobufObject/send_text_emoticon.pb.h"
#include "protobufObject/instant_message.pb.h"
#include "protobufObject/mail.pb.h"
#include "protobufObject/level.pb.h"
#include "protobufObject/captcha.pb.h"
#include "protobufObject/purchase_money.pb.h"
#include "protobufObject/administrator.pb.h"
#include "protobufObject/bet.pb.h"
#include "protobufObject/change_host.pb.h"
#include "protobufObject/invite_to_play.pb.h"
#include "protobufObject/gift.pb.h"
#include "protobufObject/exchange.pb.h"

using namespace std;

class NetworkManager
{
public:
    NetworkManager();
    virtual ~NetworkManager();

    static NetworkManager* getInstance();

    google::protobuf::Message* initPingMessage(int = 0);
    google::protobuf::Message* initLoginMessage(string = "sanglx", string =
        "12345678");
    void sendPingAndReceiveMessage(int disconnect_time);
    google::protobuf::Message* initLogoutMessage(bool = "true");
    google::protobuf::Message* initRegisterMessage(string = "register", string
        = "12345678", string="12345678", string="register", string = "sdt");
    google::protobuf::Message* initInitializeMessage(string = "0", string = "1"
        , string = "vn", string = "vi", string = "00000000", string =
        "Samsung galaxy S2",  string = "127.0.0.1", string = "cocos2dx");

    google::protobuf::Message* initFilterRoomMessage(int zone_id = 5, bool
		vip_room = false, int first_result = -1, int max_result = -1, int orderByField = -1, bool asc = true);

    google::protobuf::Message* initEnterRoomMessage(int room_index = 0, std::string password = "");

    google::protobuf::Message* initQuickPlayMessage(string = "", string = "");
    google::protobuf::Message* initOpenIdLoginMessage(int channelId = 0, string openId = "", string firstname="");
    google::protobuf::Message* initExitRoomLoginMessage(int room_index = 0); 
    google::protobuf::Message* initCancelExitRoomLoginMessage(int room_index = 0);
    google::protobuf::Message* initEnterZoneMessage(int zoneId);
    google::protobuf::Message* initCreateRoomMessage(int zone_id, int
        room_group_id, bool vip_room, int min_bet, int player_size,
        std::string password = "");

    google::protobuf::Message* initStartMatchMessage(int roomIndex = -1);
    google::protobuf::Message* initTurnMessage(int room_index, vector<BINMapFieldEntry> entries);
    google::protobuf::Message* initKichPlayerOutMessage(int roomIndex = 0, int kickedUserId = 0);
    google::protobuf::Message* initLockRoomMessage(int roomIndex, bool isLock, std::string pass = nullptr);
    google::protobuf::Message* initReadyMessage(int roomIndex, int tableIndex);
    google::protobuf::Message* initUpdateUserInfoMessage(BINEditingInfo *user_infos, int n);
    google::protobuf::Message* initFilterTopUserMessage(int firstResult, int maxResult, int orderByField = 1);
    google::protobuf::Message* initListFriendMessage(int firstResult, int maxResult);
    google::protobuf::Message* initAddFriendMessage(int targetUserId);
    google::protobuf::Message* initFilterFriendMessage(int firstResult, int maxResult);
    google::protobuf::Message* initFilterAddFriendMessage(int firstResult, int maxResult);
    google::protobuf::Message* initLookupMoneyHistoryMessage(int firstResult,
        int maxResult, int filterType);

    google::protobuf::Message* initCaptchaMessage(bool refresh);
    google::protobuf::Message* initPurchaseMoneyMessage(string provider,
        string cardSerial, string cardPin, string securityKey, string captcha,
        bool toCash);
    google::protobuf::Message* initKillRoomMessage(int zoneId, int roomIndex);
    google::protobuf::Message* initExitZoneMessage(int zoneId);
    google::protobuf::Message* initBetMessage(int roomIndex, int betType, int 
        betMoney, BINPrivateBet* privateBets, int size);
	google::protobuf::Message* initChangeHostMessage(int roomIndex, long long userId, bool isAccept, int requestType);

	google::protobuf::Message* initLookupUserToInviteMessage(int room_index, int max_result);
	google::protobuf::Message* initInviteToRoomMessage(int room_index, vector<long> target_user_ids);
	google::protobuf::Message* initCancelInviteMessage(int room_index, long long target_user_id);
	google::protobuf::Message* initRelyInviteMessage(int zone_id, int room_index, bool accept);

	google::protobuf::Message* initRedeemGiftCodeMessage(string giftcode);
	google::protobuf::Message* initRedeemGiftCodeHistoryMessage(int firstResult, int maxResult);

	google::protobuf::Message* initAssetConfigMessage(int type);
	google::protobuf::Message* initExchangeAssetMessage(int assetId, int amount);

    bool connectServer(const char* , const int);
    void connect(); 
    void recvMessage();
    void handlerMessage();
    void listenData();

	//doi thuong
	void getAssetConfigFromServer(int type);
	void getExchangeAssetFromServer(int assetId, int amount);
	//end

	//gift
	void getRedeemGiftCodeFromServer(string giftcode);
	void getRedeemGiftCodeHistoryFromServer(int firstResult, int maxResult);
	//end gift

	//invite to play
	void getLookupUserToInviteFromServer(int room_index, int max_result);
	void getInviteToRoomFromServer(int room_index, vector<long> target_user_ids);
	void getCancelInviteFromServer(int room_index, long long target_user_id);
	void getRelyInviteFromServer(int zone_id, int room_index, bool accept);
	//end

    void getTurnMessageFromServer(int room_index, vector<BINMapFieldEntry> entries);
    void getRegisterMessageFromServer(string, string, string, string, string);
    void getLoginMessageFromServer(string, string);
    void getLogoutMessageFromServer(bool doLogout);
    void getQuickPlayMessageFromServer(string, string);
    void getInitializeMessageFromServer(string cp, string appversion, string
        country, string language, string device_id, string device_info, string
        ipaddress, string packageName);
    void getPingMessageFromServer(int disconnect_time);
    void getEnterRoomMessageFromServer(int room_index,  string password);

	void getFilterRoomMessageFromServer(int zone_id, bool vip_room, int first_result, int max_result, int orderByField, bool asc);
    void getOpenIdLoginMessageFromServer(int channelId, string openId, string firstname);

    void getExitRoomMessageFromServer(int roomIndex);
    void getCancelExitRoomMessageFromServer(int roomIndex);
    void getEnterZoneMessageFromServer(int zoneId);
    void getCreateRoomMessageFromServer(int zone_id, int room_group_id, bool
        vip_room, int min_bet, int player_size, std::string password);
    void getKichPlayerOut(int roomIndex, int kickedUserId);
    void getLockRoom(int roomIndex, bool isLock, std::string password = "");
    void getStartMatchMessageFromServer(int roomIndex);
    void getReadyToPlayMessageFromServer(int roomIndex, int tableIndex);
    void getUpdateUserInfoMessageFromServer(BINEditingInfo *user_infos, int n);
    void getFilterTopUserMessageFromServer(int firstResult, int maxResult, int orderByField = 1);
    void getListFriendFromServer(int firstResult, int maxResult);
    void getAddFriend(int targetUserId);
    void getFilterFriendFromServer(int firstResult, int maxResult);
    void getFilterAddFriendFromServer(int firstResult, int maxResult);

    void getApproveAddFriendFromServer(int requestId, bool accepted);
    void getFindUserFromServer(std::string userNameQuery);
    void getViewUserInfoFromServer(int targetUserId);
    void getRemoveFriendFromServer(int targetUserId);
    void getChangeRuleFromServer(int roomIndex, BINMapFieldEntry *entries);
    void getLookupMoneyHistoryMessage(int firstResult = -1, int maxResult = -1, int filterType = 2);
    void getSendTextEmoticonFromServer(int textEmoticonId, int targetUserId);
    void getEnterRoomGroupFromServer(int roomGroupId, bool vipRoom);

    void getCaptchaMessageFromServer(bool refresh = false);
    void getPurchaseMoneyMessageFromServer(string provider,
        string cardSerial, string cardPin, string securityKey, string captcha,
        bool toCash = false);

    void getKillRoomMessageFromServer(int zoneId, int roomIndex);
    void getExitZoneMessageFromServer(int zoneId);
    //mail
    //loc danh sach mail: firstResult(index ban ghi dau tien), maxResult(max so ban ghi muon lay), lastRequestTime(thoi gian cuoi cung gui mail)
    void getFilterMailFromServer(int firstResult, int maxResult, long lastRequestTime);
    //send mail: lst_recipientuser(danh sach mail nguoi nhan), title(tieu de mail), body(noi dung mail), parent_id (id mail truoc)  
    void sendMail(vector<char*> lst_recipientuser, std::string title, std::string body, long parent_id);
    //xoa mail: selectedMailIds(danh sach id mail can xoa)
    void deleteMail(vector<long> selectedMailIds);
    //doc mail: readedMailId(id email can doc), getContent(load noi dung mail khong)
    void readMail(long readedMailId, bool getContent);
    //nhan vat pham dinh kem
    void claimAttachMail(long mailId);
    //end mail

    /*
        update user setting
     */
    //thay doi ca 2 gia tri
    void getUpdateUserSettingFromServer(bool autoReady, bool autoDenyInvitation);
    
    void changeAutoReady(bool autoReady);
    void changeAutoDenyInvitation(bool autoDenyInvitation);

    /* bet message */
    
    //đặt cược bàn
    void getBetByTable(int roomIndex, int betMoney);
    
    //đặt gà
    void getBetByUnion(int roomIndex, int betMoney);
    
    //Đánh biên, first = targetuserid, second = betmoney
    void getBetByBarier(int roomIndex, std::vector<std::pair<int, int>> lstBet);
    
	//đồng ý đánh biên
	void getConfirmBetByBarier(int roomIndex, std::vector<std::pair<int, int>> lstBet);
    
    //đặt cửa xóc đĩa
    void getBetXocDia(int roomIndex, int betMoney, int betType);
    
    //update đặt cửa xóc đĩa : action = 1 (đặt lại), = 2 (đặt gấp đôi), = 0 (huỷ cược)
    void getExtraBetRequest(int roomIndex, int action);
    
    /* end bet message */
    
	/*
	message ban chuong, xac nhan lam chuong
	*/
	void getConfirmChangeHostRequest(int roomIndex, long long userId, bool isAccept, int requestType);

    /*
        chat
        scope = 1 (chat zone), 2 (chat room), 3 (chat private)
     */
    void sendMessageToServer(int scope, std::string message,
                             std::string receiverUserName,
                             int receiverUserId);
    void sendMessageToServer(int scope, std::string message);
    
    void getHostRegistration(int roomIndex, bool cancleRegistration = false);
    

    void requestMessage(google::protobuf::Message *, int, int, string);

    char* initData(google::protobuf::Message* ,int ,int ,std::string ,int &);

    void callNetwork(char* ackBuf, int size);

    // static void callNetwork(char* , int);
    static std::vector<std::pair<google::protobuf::Message*, int>> parseFrom(std::vector<char>, int);
    bool reconnect();

    static void setInitialize(bool _isInitialize);
    static bool isInitialized();
    static bool _initialized;
    void sendPing(char* ackBuf, int size);
    void closeConnection();
    bool isConnected() const {
        return _connected;
    }

    void setConnected(bool _connect) {
        this->_connected = _connect; 
    }

    static int receiver_number;

    static bool isListening() {
        return listening;
    }

    void initConnection();

    static void setListening(bool _isListening) {
        listening = _isListening;
    }

    void setDisconnected(bool _disconnected) {
        this->_disconnected = _disconnected; 
    }

    bool isDisconnected() const {
        return _disconnected; 
    }

    static std::queue<std::vector<char>> lstBuffer;
    static std::vector<std::pair<google::protobuf::Message*, int>> listEvent;

    static const int SEND_PING_DELAY = 15000;
    static const int DATA_DELAY = 50;
    static const int SEND_MESSAGE_DELAY = 100;

    static const int REGISTER = 1000;
    static const int LOGIN = 1001;
    static const int QUICK_PLAY = 1002;
    static const int OPEN_ID_LOGIN = 1003;
    static const int LOGOUT = 1004;
    static const int ENTER_ZONE = 1005;
    static const int FILTER_ROOM = 1006;
    static const int CREATE_ROOM = 1007;
    static const int ENTER_ROOM = 1008;
    static const int ENTER_GROUP_ROOM = 1026;
    static const int PLAYER_ENTER_ROOM = 1009;
    static const int START_MATCH = 1010;
    static const int TURN = 1011;
    static const int EXIT_ROOM = 1012;
    static const int PLAYER_EXIT_AFTER_MATCH_END = 1013;
    static const int PLAYER_EXIT_ROOM = 1014;
    static const int ROOM_OWNER_CHANGED = 1015;
    static const int MATCH_BEGIN = 1016;
    static const int MATCH_END = 1017;
    static const int UPDATE_MONEY = 1018; 
    static const int PREPARE_NEW_MATCH = 1019;
    static const int CANCEL_EXIT_ROOM = 1020;
    static const int KICK_USER = 1023;
    static const int LOCK_ROOM = 1022;
    static const int READY_TO_PLAY = 1021;
    static const int HOST_REGISTRATION = 1035;
    static const int UPDATE_USER_INFO = 1200;
    static const int FILTER_TOP_USER = 1201;
    static const int FILTER_MAIL = 1202;
    static const int SEND_MAIL = 1203;
    static const int DELETE_MAIL = 1204;
    static const int READED_MAIL = 1205;
    static const int CLAIM_ATTACH_ITEM = 1206;
    static const int FILTER_FRIEND = 1207;
    static const int ADD_FRIEND = 1208;
    static const int FILTER_ADD_FRIEND = 1209;
    static const int APPROVE_ADD_FRIEND = 1210;
    static const int FIND_USER = 1211;
    static const int VIEW_USER_INFO = 1212;
    static const int REMOVE_FRIEND = 1213;
    static const int CHANGE_RULE = 1024;
    static const int SEND_TEXT_EMOTICON = 1025;

    static const int BET = 1031;
    static const int EXIT_ZONE = 1032;
    static const int CHANGE_HOST = 1033;
    static const int EXTRA_BET = 1034;

	//invite
	static const int LOOKUP_USER_TO_INVITE = 1027;
	static const int INVITE_TO_ROOM = 1028;
	static const int CANCEL_INVITE = 1030;
	static const int RELY_INVITE = 1029;
	//end

    static const int LOOKUP_MONEY_HISTORY = 1214;
    
    static const int INSTANT_MESSAGE = 1215;
    static const int UPDATE_USER_SETTING = 1216;

    static const int PURCHASE_MONEY = 1217;
    static const int FILTER_AVATAR = 1218;

    static const int LEVEL_UP = 1219;
    static const int MEDAL_UP = 1220;

//admin message
    static const int KILL_ROOM = 1300;
//special message
    static const int INITIALIZE = 1111;
    static const int PING = 8888;
    static const int EXPIRED_SESSION = 9999;
    static const int CAPTCHA = 5555;

//max connection
    static const long long MAX_CONNECTION = 15000;
    static const long long EPS = 1000;

//gift code
	static const int REDEEM_GIFT_CODE = 1221;
	static const int REDEEM_GIFT_CODE_HISTORY = 1222;

//doi thuong
	static const int ASSET_CONFIG = 1223;
	static const int EXCHANGE_ASSET = 1224;
private:
    static NetworkManager* _instance;
    bool _connected;
    static bool listening;
    std::mutex mtx;
    bool _disconnected; 
    long long connectTime;
    long long disconnect_duration;
    long long disconnect_time;
};