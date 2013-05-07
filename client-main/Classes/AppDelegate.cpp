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
	SmartRes::sharedRes()->release();

	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&AppDelegate::excuteCommand),pObj);
	delete pObj;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();  
    pDirector->setOpenGLView(pEGLView);

	

    //pDirector->setDisplayStats(true);
    //pDirector->setAnimationInterval(1.0 / 60);

	initGame();

    LayerUI *layerUI = SceneMain::scene(NULL,true);

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
    
	pObj=new CCObject();
    
	Facade::registerCommands();
    
	if(!Facade::IsMock){
		Client* client=Client::GetInstance();
		bool b=client->connet(Facade::Ip, Facade::Port);
		if(b){
			CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&AppDelegate::excuteCommand), pObj, 0.01f, false);
			client->setConfig("18602122551", "PASSPORT");
			Facade::send(CommandCheck::Head,Facade::Version);
		}
	}
    
    //CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
	
	//初始化配置
	//读取配置json
//	const char * configFileName= "config.txt";
//	string configStr=FileUtil::read(configFileName);
	//解析json
//	Facade::Emails=ConfigUtil::parseEmail(configStr.c_str());
//	CCLOG("id==%d",Facade::Emails[1].id);
//	CCLOG("content==%s",Facade::Emails[1].content.c_str());

	//读取语言文件
	
	Facade::Langs=ConfigUtil::parseLang("langs","zh-CN");
}
void AppDelegate::excuteCommand(float dt){
	Client* client=Client::GetInstance();
	client->excuteCommand();
}


std::vector<std::string> split(const std::string s, char delim) {
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}
