#include "Facade.h"
#include "cocos2d.h"
#include "CommandUser.h"
#include "../views/SceneHome.h"
#include "../utils/jsoncpp/json.h"

using namespace cocos2d;

LayerUI* CommandUser::init(){
    return NULL;
}


void CommandUser::parse(LayerUI* layer,const char *data){
        
}

void CommandUser::success(LayerUI* layer){
	
}


//VoObject* CommandUser::parse(const char *data){
//    VoHome* voServer=new VoHome();
//    if(sizeof(data)>0){
//        Json::Reader reader;
//		Json::Value value;
//        if(reader.parse(data, value)){
//            //voServer->name=value["domain"].asString();
//            //voServer->id=value["id"].asInt();
//            
//        }
//    }
//    
//    
//    return voServer;
//}


