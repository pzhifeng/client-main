#include "CommandSystem.h"
#include "cocos2d.h"
#include "../SceneMain.h"
#include "../views/SceneHome.h"
#include "../views/SceneTest.h"
#include "../utils/jsoncpp/include/json.h"
#include "VoObject.h"
#include "../utils/FileUtil.h"

using namespace cocos2d;

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
    vo->title="你好111";
    return vo;
}

int CommandTest::Head=99103;

LayerUI* CommandTest::success(VoObject* vo){
	LayerUI *layer = SceneTest::scene((VoTest*)vo);
    return layer;
}

void CommandTest::fail(int code,VoObject* vo){
	
}

VoObject* CommandTest::parse(const char *data){
    VoTest* vo=new VoTest();
    vo->name="Hello TEST";
    vo->title="你好TEST";
    return vo;
}




