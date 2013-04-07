#include "CommandCheck.h"
#include "Facade.h"
#include "cocos2d.h"
#include "SceneMain.h"
#include "../utils/jsoncpp/include/json.h"

using namespace cocos2d;

int CommandCheck::Head=99100;

CommandCheck::CommandCheck(void)
{
}


CommandCheck::~CommandCheck(void)
{
}

void CommandCheck::success(VoObject* vo){
	//CCScene *pScene = SceneMain::scene();
	//CCDirector::sharedDirector()->runWithScene(pScene);
}

void CommandCheck::fail(int code,VoObject* vo){
	if(code==1){
        
    }else if(code==2){
        
    }
}

VoObject* CommandCheck::parse(const char *data){
    return NULL;
}


