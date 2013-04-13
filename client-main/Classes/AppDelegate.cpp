#include "AppDelegate.h"

#include "cocos2d.h"
#include "SceneMain.h"
#include "core/Client.h"
#include "Facade.h"
#include "commands/CommandSystem.h"
#include "utils/FileUtil.h"
#include "VoConfig.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
	Facade::release();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = SceneMain::scene();

    // run
    pDirector->runWithScene(pScene);

	initGame();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


void AppDelegate::initGame(){
	//init system commands
	Facade::registerCommands();
	if(!Facade::IsMock){
		Client* client=Client::GetInstance();
		bool b=client->connet(Facade::Ip, Facade::Port);
		if(b){
			client->setConfig("18602122551", "PASSPORT");
			Facade::send(CommandCheck::Head,Facade::Version);
		}
	}
	
	//��ʼ������
	//��ȡ����json
//	const char * fileName= "config.txt";
//	string jsonStr=FileUtil::read(fileName);
	//����json
//	Facade::Emails=ConfigUtil::parseEmail(jsonStr.c_str());
//	CCLOG("id==%d",Facade::Emails[1].id);
//	CCLOG("content==%s",Facade::Emails[1].content.c_str());
}