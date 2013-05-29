#include "cocos-ext.h"
#include "CommandHome.h"
#include "../views/SceneHome.h"
#include "../views/SceneFight.h"

USING_NS_CC;
USING_NS_CC_EXT;

//=========================
LayerUI* CommandHome::success(const char *data){
    SceneHome *scene=(SceneHome*)LayerUI::scene("SceneHome", SceneHomeLoader::loader());
    scene->title->setString("SceneHome OK!");
    CCMenuItemImage *homeGate5=scene->homeGate5;
    homeGate5->setEnabled(false);
    
    CCMenuItemImage *homeGate1=scene->homeGate1;
    CCFileUtils::sharedFileUtils()->setResourceDirectory("ui");
    homeGate1->setNormalImage(CCSprite::create("btn-a-0.png"));
    
    return (LayerUI*)scene;
}


//=========================
LayerUI* CommandHomeGate::success(const char *data){
    UIHomeGate *scene=(UIHomeGate*)LayerUI::layer("UIHomeGate", UIHomeGateLoader::loader());
    
    scene->gateTitle->setString("HomeGate OK!");
    
    return (LayerUI*)scene;
}


//=========================
LayerUI* CommandHomePve::success(const char *data){
    SceneFight *scene=(SceneFight*)SceneFight::scene(NULL);;
    
    return (LayerUI*)scene;
}
