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
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();  
    pDirector->setOpenGLView(pEGLView);

	//2013-04-15 liuzhuang
	CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	initGame();

    // create a scene. it's an autorelease object
    CCScene *pScene = SceneMain::scene();

	// run
	pDirector->runWithScene(pScene);


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
	
	//初始化配置
	//读取配置json
//	const char * configFileName= "config.txt";
//	string configStr=FileUtil::read(configFileName);
	//解析json
//	Facade::Emails=ConfigUtil::parseEmail(configStr.c_str());
//	CCLOG("id==%d",Facade::Emails[1].id);
//	CCLOG("content==%s",Facade::Emails[1].content.c_str());

	//读取语言文件
	const char *langFileName="lang/zh_CN.properties";
	Facade::Langs=ConfigUtil::parseLang(langFileName);
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
/*
std::vector<std::string> split(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();
 
	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}
*/