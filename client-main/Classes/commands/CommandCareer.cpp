#include "CommandCareer.h"
#include "Facade.h"
#include "cocos2d.h"
#include "../views/SceneHome.h"
#include "../utils/jsoncpp/include/json.h"

using namespace cocos2d;

int CommandCareer::Head=10200;

LayerUI* CommandCareer::success(VoObject* vo){
    VoServer* voServer=(VoServer*)vo;
	
    
    return  NULL;
}

void CommandCareer::fail(int code,VoObject* vo){
	
}

VoObject* CommandCareer::parse(const char *data){
    VoServer* voServer=new VoServer();
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


