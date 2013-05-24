#include "CommandSystem.h"
#include "cocos2d.h"
#include "../SceneMain.h"
#include "../views/SceneHome.h"
#include "../utils/jsoncpp/json.h"
#include "../utils/FileUtil.h"


using namespace cocos2d;

//======CommandCheck======

int CommandCheck::Head=99100;

LayerUI* CommandCheck::success(VoObject* vo){
	LayerUI *layer= SceneMain::scene((VoMain*)vo,false);

    return layer;
}

void CommandCheck::fail(int code,VoObject* vo){
    
    SceneMain::scene((VoMain*)vo,false);
    
	if(code==1){
		/*
		myHttpRequest=new MyHttpRequest();
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


//======CommandServer======

int CommandServer::Head=99102;

LayerUI* CommandServer::success(VoObject* vo){
	LayerUI *layer = UIServer::scene((VoServer*)vo);
	
    return layer;
}

void CommandServer::fail(int code,VoObject* vo){
	
}

VoObject* CommandServer::parse(const char *data){
    VoServer* vo=new VoServer();
    vo->id=1;
    vo->name="luan shi ying xiong";
    vo->domain="s1.gameus.cn";
    vo->tag="xin";
    return vo;
}



