//
//  MLabel.cpp
//  GameVina
//
//  Created by Black3rry on 3/25/16.
//
//

#include "MLabel.hpp"

using namespace cocos2d;

MLabel* MLabel::create(std::string text, float size){
    MLabel *label = (MLabel*)Label::createWithTTF(text,"fonts/gamevina.otf", size);
    label->setAnchorPoint(cocos2d::Vec2(0,0));
    return label;
}

MLabel* MLabel::create(std::string text,float size, cocos2d::Color3B color){
    MLabel *label = (MLabel*)Label::createWithTTF(text, "fonts/gamevina.otf", size);
    label->setAnchorPoint(cocos2d::Vec2(0,0));
    label->setColor(color);
    
    return label;
}

MLabel* MLabel::create(std::string text,float size, cocos2d::Color3B color,int tag){
    MLabel *label = (MLabel*)Label::createWithTTF(text, "fonts/gamevina.otf", size);
    label->setAnchorPoint(cocos2d::Vec2(0,0));
    label->setColor(color);
    label->setTag(tag);
    
    return label;
}

MLabel* MLabel::createWithBitmapFont(std::string text,std::string fontName){
    MLabel *label = (MLabel*)Label::createWithBMFont("fonts/"+fontName,text);
    label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    return label;
}

MLabel* MLabel::createCountDown(int timeCountDown){
  MLabel *label = (MLabel*)Label::createWithBMFont("fonts/font_demnguoc.fnt",
                                                   cocos2d::StringUtils::format("%d",timeCountDown));
    if(timeCountDown == 0){
        return label;
    }
  Vector<FiniteTimeAction*> countDownTime;
  auto delayin = DelayTime::create(1.0f);
  for (int i = 0; i<timeCountDown; i++) {
    auto callAppear = CallFunc::create([=]() {
      label->setString(StringUtils::format("%d", timeCountDown - i - 1));
    });
    auto sequence = Sequence::create(delayin->clone(), callAppear, NULL);
    countDownTime.pushBack(sequence);
  }
  auto countFinal = Sequence::create(delayin->clone(), RemoveSelf::create(), NULL);

  label->runAction(Sequence::create(Sequence::create(countDownTime), countFinal, NULL));
  return label;
}

MLabel* MLabel::createClockCountDown(int timeCountDown){
    MLabel *label = (MLabel*)Label::createWithBMFont("fonts/font_clock.fnt",
                                                     cocos2d::StringUtils::format("%d",timeCountDown));
    return label;
}

MLabel* MLabel::createUpdateMoney(long long money){
    MLabel *label = (MLabel*)Label::createWithBMFont(money > 0 ? "fonts/font_thang.fnt" : "fonts/font_thua.fnt",
                                                     StringUtils::format(money>0 ? "+%lld" : "%lld",money));
    //label->setTextColor(money<0 ? Color4B::RED : Color4B::YELLOW);
    //label->enableOutline(Color4B::WHITE, 2);
    auto move = MoveBy::create(1.2f, Vec2(0,50));
    auto fadeout = FadeOut::create(1.2f);
    auto zoomout = ScaleTo::create(1.2f, 1.1f);
    label->runAction(Sequence::create(Spawn::create(move,fadeout,zoomout, NULL),RemoveSelf::create(),NULL));
    return label;
}

MLabel* MLabel::createUpdateMoney(long long money, int time_delay, float height, std::string text){
	MLabel *label = (MLabel*)Label::createWithTTF(
		StringUtils::format(money>0 ? "+%lld" : "%lld", money) + text, money > 0 ? "fonts/gamevina.otf" : "fonts/gamevina.otf", 25);
	label->setTextColor(money<0 ? Color4B::RED : Color4B::YELLOW);
	label->enableOutline(Color4B::WHITE, 2);

	label->setVisible(false);
	float time = 3.0f;
	auto delay = DelayTime::create(time_delay);

	auto move = MoveBy::create(1.5f, Vec2(0, height));
	auto fadeout = FadeOut::create(time);
	auto zoomout = ScaleTo::create(time, 1.3f);
	auto callFunc = CallFunc::create([=]{
		label->setVisible(true);
	});
	label->runAction(Sequence::create(delay, callFunc, Spawn::create(move, fadeout, zoomout, NULL), RemoveSelf::create(), NULL));

	return label;
}

float MLabel::getWidth(){
    return this->getContentSize().width;
}

float MLabel::getHeight(){
    return this->getContentSize().height;
}


bool MLabel::init()
{
    if (!MLabel::init()) {
        return false;
    }
    return true;
}