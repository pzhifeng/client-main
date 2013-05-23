#include "CommandSystem.h"
#include "cocos2d.h"
#include "../SceneMain.h"
#include "../views/SceneHome.h"
#include "../utils/jsoncpp/json.h"
#include "../utils/FileUtil.h"


using namespace cocos2d;

//======CommandCheck======

LayerUI* CommandCheck::init(){
    return NULL;
}


void CommandCheck::parse(LayerUI* layer,const char *data){
    
}

void CommandCheck::success(LayerUI* layer){
	
}


//void CommandCheck::fail(int code,VoObject* vo){
//    
//    SceneMain::scene((VoMain*)vo,false);
//    
//	if(code==1){
//		/*
//		myHttpRequest=new MyHttpRequest();
//		myHttpRequest->doGet();
//		while(true){
//			if(myHttpRequest->m_isCompleted)
//				break;
//			Sleep(100);
//		}
//		//CCLOG("m_responseData===%s",myHttpRequest->m_responseData.c_str());
//
//		const char * fileName= "lang/zh_CN.properties";
//		//myHttpRequest->m_responseData="{\"v\":\"1.0\",\"email\":{\"1\":{\"content\":\"123888\",\"id\":1},\"2\":{\"content\":\"456\",\"id\":2}}}";
//		FileUtil::write(fileName,myHttpRequest->m_responseData.c_str());
//
//		myHttpRequest->release();
//		*/
//	}else if(code==2){
//
//	}
//}

//======CommandMain======

LayerUI* CommandMain::init(){
    return SceneMain::scene();
}


void CommandMain::parse(LayerUI* layer,const char *data){
    //SceneMain *scene=(SceneMain*)layer;
    
}

void CommandMain::success(LayerUI* layer){
	
}


//======CommandServer======

LayerUI* CommandServer::init(){
    return NULL;
}


void CommandServer::parse(LayerUI* layer,const char *data){
    
    
}

void CommandServer::success(LayerUI* layer){
	
}

//======CommandHome======

LayerUI* CommandHome::init(){
    SceneHome *layer =SceneHome::create();
    layer->window("SceneHome.ccbi", "SceneHome", SceneHomeLoader::loader());
    return layer;
}


void CommandHome::parse(LayerUI* layer,const char *data){
    //SceneHome *home=(SceneHome*)layer;
    
}

void CommandHome::success(LayerUI* layer){
	
}





