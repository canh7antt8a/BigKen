//
//  SoundManager.h
//  MyCards
//
//  Created by hungle on 6/18/16.
//
//

#ifndef SoundManager_h
#define SoundManager_h

#include "SimpleAudioEngine.h"
#include "vector"

using namespace CocosDenshion;

class SoundManager{

public:
    SoundManager();
    ~SoundManager();
    static SoundManager* getInstance();
    void preLoadAudio(std::vector<const char *> names);
    void playSound(const char * name);
private:
    SimpleAudioEngine* audio;
    static SoundManager* instance;
};

#endif /* SoundManager_h */
