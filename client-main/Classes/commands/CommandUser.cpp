#include "Facade.h"
#include "cocos2d.h"
#include "CommandUser.h"
#include "../views/SceneHome.h"
#include "../utils/jsoncpp/json.h"

USING_NS_CC;
USING_NS_CC_EXT;

//=========================
LayerUI* CommandUser::success(const char *data){
    return NULL;
}

//=========================
LayerUI* CommandUserName::success(const char *data){
    return NULL;
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


