#include "CommandSystem.h"
#include "cocos2d.h"
#include "../views/SenceHome.h"
#include "../utils/jsoncpp/include/json.h"
#include "VoObject.h"
#include "utils/FileUtil.h"

using namespace cocos2d;

int CommandCheck::Head=99100;

LayerUI* CommandCheck::success(VoObject* vo){
	//CCScene *pScene = SceneMain::scene();
	//CCDirector::sharedDirector()->runWithScene(pScene);
    return NULL;
}

void CommandCheck::fail(int code,VoObject* vo){
	if(code==1){
		/*
		myHttpRequest=new HttpRequest();
		myHttpRequest->doGet();
		while(true){
			if(myHttpRequest->m_isCompleted)
				break;
			Sleep(100);
		}
		//CCLOG("m_responseData===%s",myHttpRequest->m_responseData.c_str());

		const char * fileName= "lang/zh_CN.properties";
		//myHttpRequest->m_responseData="{\"v\":\"1.0\",\"email\":{\"1\":{\"content\":\"123888\",\"id\":1},\"2\":{\"content\":\"456\",\"id\":2}}}";
		FileUtil::write(fileName,myHttpRequest->m_responseData.c_str());

		myHttpRequest->release();
		*/
	}else if(code==2){

	}
}

VoObject* CommandCheck::parse(const char *data){
    return NULL;
}


int CommandServer::Head=99102;

LayerUI* CommandServer::success(VoObject* vo){
	LayerUI *layer = SceneHome::scene((VoHome*)vo);
	
    return layer;
}

void CommandServer::fail(int code,VoObject* vo){
	
}

VoObject* CommandServer::parse(const char *data){
    VoHome* vo=new VoHome();
    vo->name="Hello OOO";
    vo->title="你好";
    return vo;
}




