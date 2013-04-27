#include "AppDelegate.h"

#include "cocos2d.h"
#include "SceneMain.h"
#include "core/Client.h"
#include "Facade.h"
#include "commands/CommandSystem.h"
#include "utils/FileUtil.h"
#include "VoConfig.h"
#include "core/SmartRes.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
	//Facade::release();
	SmartRes::sharedRes()->release();

    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&AppDelegate::excuteCommand),ccPoint);
    delete ccPoint;

}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	//2013-04-15 liuzhuang
	CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	initGame();

    // create a scene. it's an autorelease object
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);

    CCScene *pScene = SceneMain::scene();
    pDirector->runWithScene(pScene);

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

	//��ȡ�����ļ�
	const char *langFileName="lang/zh_CN.properties";
	Facade::Langs=ConfigUtil::parseLang(langFileName);
}

void AppDelegate::excuteCommand(float dt){
    Client* client=Client::GetInstance();
    client->excuteCommand();
}
