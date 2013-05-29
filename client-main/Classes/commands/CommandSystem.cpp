#include "cocos2d.h"
#include "CommandSystem.h"
#include "../Facade.h";
#include "../SceneMain.h"
#include "../utils/jsoncpp/json.h"
#include "../utils/FileUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;

//=========================
LayerUI* CommandCheck::success(const char *data){
    return NULL;
}

//=========================
LayerUI* CommandMain::success(const char *data){
	SceneMain *scene=(SceneMain*)SceneMain::scene();
    
    VoServer *vo=new VoServer();
    vo->id=1;
    vo->name="一区 东方不败";
    vo->tag="爆满";
    VoServer *vo2=new VoServer();
    vo2->id=1;
    vo2->name="二区 日月神教";
    vo2->tag="推荐";
    Facade::Servers[1]=vo;
    Facade::Servers[2]=vo2;
    
    scene->version->setString("v1.2.0");
    scene->mainServer->setTitleForState(CCString::create("HelloServer"), CCControlStateNormal);
    
    return (LayerUI*)scene;
}

//=========================
LayerUI* CommandMainServer::success(const char *data){
    CCScene* scene=cocos2d::CCDirector::sharedDirector()->getRunningScene();
    
    UIMainServer* layer=UIMainServer::create();
    
    scene->addChild(layer);
    return (LayerUI*)layer;
}

//=========================
LayerUI* CommandMainServerSelect::success(const char *data){
    SceneMain *scene=(SceneMain*)SceneMain::scene();
    
    int id=0;
    VoServer *vo=Facade::Servers[id+1];
    std:string tmp;
    tmp.append(vo->name).append("  ").append(vo->tag);

    scene->mainServer->setTitleForState(CCString::create(tmp.c_str()), CCControlStateNormal);

    return (LayerUI*)scene;
}








