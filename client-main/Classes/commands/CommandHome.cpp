#include "cocos-ext.h"
#include "CommandHome.h"
#include "../views/SceneHome.h"
#include "../views/SceneFight.h"

USING_NS_CC;
USING_NS_CC_EXT;

//======CommandHome======

LayerUI* CommandHome::init(){
    return LayerUI::scene("SceneHome", SceneHomeLoader::loader());
}


void CommandHome::parse(LayerUI* layer,const char *data){
    SceneHome *scene=(SceneHome*)layer;
    scene->title->setString("SceneHome OK!");
    CCMenuItemImage *homeGate5=scene->homeGate5;
    homeGate5->setEnabled(false);
    
    CCMenuItemImage *homeGate1=scene->homeGate1;
    CCFileUtils::sharedFileUtils()->setResourceDirectory("ui");
    homeGate1->setNormalImage(CCSprite::create("btn-a-0.png"));
}

void CommandHome::success(LayerUI* layer){
	
}

//======CommandHomeGate======

LayerUI* CommandHomeGate::init(){
    return LayerUI::layer("UIHomeGate", UIHomeGateLoader::loader());
}


void CommandHomeGate::parse(LayerUI* layer,const char *data){
    UIHomeGate *scene=(UIHomeGate*)layer;
    //scene->title->setString("HomeGate OK!");
    
}

void CommandHomeGate::success(LayerUI* layer){
	
}

//======CommandHomePve======

LayerUI* CommandHomePve::init(){
    return SceneFight::scene(NULL);
}


void CommandHomePve::parse(LayerUI* layer,const char *data){

}

void CommandHomePve::success(LayerUI* layer){
	
}