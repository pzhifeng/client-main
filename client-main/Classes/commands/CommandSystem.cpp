#include "CommandSystem.h"
#include "cocos2d.h"
#include "../views/SenceHome.h"
#include "../utils/jsoncpp/include/json.h"
#include "VoObject.h"

using namespace cocos2d;



int CommandCheck::Head=99100;

void CommandCheck::success(VoObject* vo){
	//CCScene *pScene = SceneMain::scene();
	//CCDirector::sharedDirector()->runWithScene(pScene);
}

void CommandCheck::fail(int code,VoObject* vo){
	if(code==1){
        
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
    SceneHome* home=(SceneHome*) pScene;
    home->voHome=(VoHome*)vo;
}

void CommandServer::fail(int code,VoObject* vo){
	
}

VoObject* CommandServer::parse(const char *data){
    VoHome* vo=new VoHome();
    vo->name="Hello OOO";
    return vo;
}




