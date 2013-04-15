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
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&AppDelegate::excuteCommand),ccPoint);
    delete ccPoint;
	Facade::release();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);

    CCScene *pScene = SceneMain::scene();
    pDirector->runWithScene(pScene);

	initGame();

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::initGame(){
    ccPoint=new CCPoint();
	//init system commands
	Facade::registerCommands();
	if(!Facade::IsMock){
		Client* client=Client::GetInstance();
		bool b=client->connet(Facade::Ip, Facade::Port);
		if(b){
            CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&AppDelegate::excuteCommand), ccPoint, 0.01f, false);
            client->setConfig("18602122551", "PASSPORT");
			Facade::send(CommandCheck::Head,Facade::Version);
		}
	}
	
	//≥ı ºªØ≈‰÷√
	//∂¡»°≈‰÷√json
//	const char * fileName= "config.txt";
//	string jsonStr=FileUtil::read(fileName);
	//Ω‚Œˆjson
//	Facade::Emails=ConfigUtil::parseEmail(jsonStr.c_str());
//	CCLOG("id==%d",Facade::Emails[1].id);
//	CCLOG("content==%s",Facade::Emails[1].content.c_str());
}

void AppDelegate::excuteCommand(float dt){
    Client* client=Client::GetInstance();
    client->excuteCommand();
}
