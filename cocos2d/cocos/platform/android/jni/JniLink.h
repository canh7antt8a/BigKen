/*
 * JniLink.h
 */

#ifndef JNILINK_H_
#define JNILINK_H_

#include <string>
#include <sstream>

using namespace std;

extern "C"
{
    extern void openURLX(const char* url);
    extern char* GetIdJNI();
	extern char* GetNameJNI();
	extern char* GetVersionApp();
	extern char* callLoginFacebook();
	extern char* GetLoginNameFacebook();
	extern char* GetTokenFacebook();
	void shareFace(const std::string& url);
	extern void CallMobileJNI(const char* myPhone);
	extern char* GetNetworkStrength();
	extern char* GetPackageName();
}

#endif /* JNILINK_H_ */
