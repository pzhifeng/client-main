#include "CommandSystem.h"
#include "cocos2d.h"
#include "../views/SenceHome.h"
#include "../utils/jsoncpp/include/json.h"
#include "core/VoObject.h"

using namespace cocos2d;
using namespace extension;

int CommandCheck::Head=99100;

void CommandCheck::success(VoObject* vo){
	//CCScene *pScene = SceneMain::scene();
	//CCDirector::sharedDirector()->runWithScene(pScene);
}

void CommandCheck::fail(int code,VoObject* vo){
	if(code==1){
        //需要更新配置文件,下载最新配置文件，进入游戏
		/*
		myHttpRequest=new HttpRequest();
		myHttpRequest->doGet();
		while(true){
			if(myHttpRequest->m_isCompleted)
				break;
			Sleep(100);
		}
		//CCLOG("m_responseData===%s",myHttpRequest->m_responseData.c_str());
		myHttpRequest->release();
		*/
		//const char * fileName= "config.txt";
		//string str="{\"v\":\"1.0\",\"email\":{\"1\":{\"content\":\"123888\",\"id\":1},\"2\":{\"content\":\"456\",\"id\":2}}}";
		//FileUtil::write(fileName,myHttpRequest->m_responseData.c_str());
	}else if(code==2){

	}
}

VoObject* CommandCheck::parse(const char *data){
    return NULL;
}

int CommandServer::Head=99102;

void CommandServer::success(VoObject* vo){
	CCScene *pScene = SceneHome::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CommandServer::fail(int code,VoObject* vo){
	
}

VoObject* CommandServer::parse(const char *data){
    VoHome* vo=new VoHome();
    vo->name="Hello OOO";
    return vo;
}




