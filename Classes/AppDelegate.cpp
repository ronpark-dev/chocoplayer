﻿#include "AppDelegate.h"

#include "COMMON/DebugingCode.h"
#include "AppMulti.h"

#include "TRANSLATE/TranslateMain.h"

#include "COMMON/GlobalLangFile.h"
#include "COMMON/MgrSetting.h"
#include "GRAPHIC/ImageBuffer.h"
#include "COMMON/MultiOutter.h"
#include "SCENE/APPMAIN/ScrAppMain.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
	GlobalLangFile::removeInstance();
	MgrSetting::removeInstance();
	IBuffer::removeInstance();
}

TString GetGamesPath();

bool AppDelegate::applicationDidFinishLaunching() {

	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);
	
	// turn on display FPS
	pDirector->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	CCSize frameSize = pEGLView->getFrameSize();

	ScreenCommon::setAppScreen(frameSize.width, frameSize.height);
	//ScreenCommon::setAppScreen(640, 400);

	gm.appstart(GetGamesPath());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
	CCDirector::sharedDirector()->pause();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	gm.onPause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->stopAnimation();
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->startAnimation();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	gm.onResume();
}