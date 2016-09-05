//
//  SoundManager.cpp
//  MyCards
//
//  Created by hungle on 6/18/16.
//
//

#include "SoundManager.h"
#include "Utils/Utility.h"

SoundManager* SoundManager::instance = 0;

SoundManager::SoundManager(){
}

SoundManager::~SoundManager(){
}

SoundManager* SoundManager::getInstance(){
    if(!instance){
        instance = new SoundManager();
    }
    return instance;
}

void SoundManager::preLoadAudio(std::vector<const char *> names){
    
    audio = SimpleAudioEngine::getInstance();
    for(int i =0;i<names.size();i++) {
        audio->preloadEffect(names[i]);
    }

}

void SoundManager::playSound(const char *name) {
    if(getPrefs(SOUND)) {
        audio->playEffect(name);
    }
}