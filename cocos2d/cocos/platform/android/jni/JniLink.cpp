/*
 * JniLink.cpp
 */


#include "JniLink.h"
#include "JniHelper.h"
#include <string>
#include <sstream>
using namespace cocos2d;

extern "C"
{

	void openURLX(const char* url)
	{
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t,
			"org/cocos2dx/lib/Cocos2dxActivity",    // fully qualified class name
			"openURLX",                              // method name
			"(Ljava/lang/String;)V")) {             // data type of argument

			// jstring - C++ representation of Java String
			jstring stringArg = t.env->NewStringUTF(url);

			// call the method, with arguments
			t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg);
		}
	}

	char* GetIdJNI() {
		JniMethodInfo t;
		std::string a("");
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "GetId", "()Ljava/lang/String;")) {
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			return (char*)JniHelper::jstring2string(str).c_str();
		}
		return NULL;
	}

	char* GetNameJNI(){
		JniMethodInfo t;
		std::string a("");
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getDeviceName", "()Ljava/lang/String;")) {
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			return (char*)JniHelper::jstring2string(str).c_str();
		}
		return NULL;
	}

	char* GetVersionApp(){
		JniMethodInfo t;
		std::string a("");
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getVersionApp", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);

		return (char*)JniHelper::jstring2string(str).c_str();
		}
		return NULL;
	}


	//goi khi click button dang nhap cho facebook
	char* callLoginFacebook(){
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "loginFaceBookClick", "()Ljava/lang/String;")) {
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			return (char*)JniHelper::jstring2string(str).c_str();
		}

		return NULL;
	}
	
	char* GetLoginNameFacebook(){
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getLoginNameFacebook", "()Ljava/lang/String;")) {
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			return (char*)JniHelper::jstring2string(str).c_str();
		}

		return NULL;
	}

	//goi sau khi dang nhap thanh cong de lay token
	char* GetTokenFacebook(){
		JniMethodInfo t;
		std::string a("");
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getTokenFacebook", "()Ljava/lang/String;")) {
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);

			return (char*)JniHelper::jstring2string(str).c_str();
		}
		return NULL;
	}

	//chia se voi facebook
	void shareFace(const std::string& url){
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "shareFace", "(Ljava/lang/String;)V")) {
			jstring stringArg = t.env->NewStringUTF(url.c_str());

			t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg);
		}
	}
	
	//goi dien
	void CallMobileJNI(const char* myPhone){
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"org/cocos2dx/lib/Cocos2dxActivity",    // fully qualified class name
			"callMobile",                              // method name
			"(Ljava/lang/String;)V")) {             // data type of argument

			// jstring - C++ representation of Java String
			jstring stringArg = t.env->NewStringUTF(myPhone);

			// call the method, with arguments
			t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg);
		}
	}

	//get do manh cua mang
	char* GetNetworkStrength(){
		JniMethodInfo t;
		int strengResult = 0;
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getNetworkStrengh", "()Ljava/lang/String;")) {
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);

			return (char*)JniHelper::jstring2string(str).c_str();
		}

		return NULL;
	}

	char* GetPackageName() {
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getPackagename", "()Ljava/lang/String;")) {
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			return (char*)JniHelper::jstring2string(str).c_str();
		}

		return NULL;
	}
}