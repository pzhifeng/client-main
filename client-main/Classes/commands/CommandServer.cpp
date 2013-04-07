#include "CommandServer.h"
#include "cocos2d.h"
#include "../views/SenceHome.h"
#include "../utils/jsoncpp/include/json.h"
#include "core/VoObject.h"

using namespace cocos2d;

int CommandServer::Head=99102;

CommandServer::CommandServer(void)
{
}


CommandServer::~CommandServer(void)
{
}

void CommandServer::success(VoObject* vo){
    VoServer* voServer=(VoServer*)vo;
	CCScene *pScene = SceneHome::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CommandServer::fail(int code,VoObject* vo){
	
}

VoObject* CommandServer::parse(const char *data){
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

