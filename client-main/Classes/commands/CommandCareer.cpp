#include "CommandCareer.h"
#include "Facade.h"
#include "cocos2d.h"
#include "../views/SenceHome.h"
#include "../utils/jsoncpp/include/json.h"

using namespace cocos2d;

std::string CommandCareer::Head="10200";

CommandCareer::CommandCareer(void)
{
    //CommandHead::CAREER="10200";
    //CommandCareer::Head="10200";
}


CommandCareer::~CommandCareer(void)
{
}

void CommandCareer::success(VoObject* vo){
    VoServer* voServer=(VoServer*)vo;
	CCScene *pScene = SceneHome::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
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


