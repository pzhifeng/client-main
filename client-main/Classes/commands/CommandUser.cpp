#include "Facade.h"
#include "cocos2d.h"
#include "CommandUser.h"
#include "../views/SceneHome.h"
#include "../utils/jsoncpp/json.h"

using namespace cocos2d;

int CommandUser::Head=10200;

LayerUI* CommandUser::success(VoObject* vo){
    
	
    
    return  NULL;
}

void CommandUser::fail(int code,VoObject* vo){
	
}

VoObject* CommandUser::parse(const char *data){
    VoHome* voServer=new VoHome();
    if(sizeof(data)>0){
        Json::Reader reader;
		Json::Value value;
        if(reader.parse(data, value)){
            //voServer->name=value["domain"].asString();
            //voServer->id=value["id"].asInt();
            
        }
    }
    
    
    return voServer;
}


