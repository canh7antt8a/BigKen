//
//  BaseScene.hpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/8/16.
//
//

#ifndef BaseScene_hpp
#define BaseScene_hpp

#include "cocos2d.h"
#include <vector>
#include <algorithm>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "protobufObject/mail.pb.h"
#include <string>
#include <sstream>
#include "Objects/Avatar.hpp"
#include "Objects/Player.hpp"
#include "Objects/WaitingPlayer.hpp"
#include "Objects/TLMNPlayer.hpp"
#include "Objects/Mail.h"
#include "UI/MToast.hpp"
#include "Popups/PopupUserInfo.hpp"
#include "Utils/TLMNConfig.hpp"
#include "protobufObject/ping.pb.h"
#include "Utils/Common.h"
#include "Utils/NetworkManager.h"
#include <string>
#include <sstream>
#include "Objects/PositionPlayer.h"
#include "Utils/Utility.h"
#include "Utils/LoadingManager.hpp"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

class BaseScene : public Layer
{
public:
    
    virtual bool init();
    virtual void onExit();

    CREATE_FUNC(BaseScene);

    void update(float);
    
public:
    void showToast(const char* message,float duration);

    //show tin nhan chat
    void showMessageChat(const char* message, Avatar* avatar, float duration);

    void closeApp();

    void goToIntroScene(float dt);

    void initialMessageResponseHandler();
    
protected:
    Vec2 MVec2(float x, float y);
    Size visibleSize;
    float width;
    float height;
    Vec2 origin;
    float originX;
    float originY;
    
    //vector<WaitingPlayer*> lstDisplayWaitingPlayer;
    ////so nguoi choi toi da
    //int capacity_size = 0;

    //show ra vi tri cho ngoi cua player, dua vao capacity_size
    void showPositionPlayer();

    //xoa avatar khoi ban choi
    virtual void removeOutTablePlay(Avatar* avatar);

	virtual void loadEmail(vector<Mail> lstEmail);
	virtual void readMail(Mail mail);
	virtual void deleteMail(vector<long> lstMailId);
	virtual void viewUserInfo(BINViewUserInfoResponse *viewUserInfo);
	virtual void loadMoneyLogHistory(vector<BINMoneyLog> lstMoneyLogs);

    //mail
    void filterEmailResponse();
    void sendMailResponse();
    void readMailResponse();
    void deleteMailResponse();
    void claimMailResponse();
    Mail parseFromBinMail(BINMail binMail);
    //end

	//thong tin user
	void viewUserInfoFromServer();

	//lich su doi thuong
	void lookupMoneyHistoryResponse();

    void captureScreenShareFace();
    void shareFaceBook(const std::string& outputFile);

    //pair<google::protobuf::Message*, int> registerResult;

    //show list nguoi cho len game
    //void showWaitingPlayerOnScene(vector<TLMNPlayer> lstWaiting);
    //reset danh sach nguoi cho
    //void resetListWaiting();
    //hidden card remaining count
    //void hiddenCardRemainingCount(vector<Avatar*> &avatars);
};

#endif /* BaseScene_hpp */
