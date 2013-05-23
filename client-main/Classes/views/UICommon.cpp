#include "UICommon.h"
#include "Facade.h"
#include "../SceneMain.h"
using namespace cocos2d;


//======UIHead======
LayerUI* UIHead::scene(VoHead* vo)
{
    
    CCScene *scene = CCScene::create();
    
    UIHead *layer = UIHead::create();
    
    layer->vo=vo;
    
    layer->initLayer();
    
    scene->addChild(layer);
    
    CCDirector::sharedDirector()->runWithScene(scene);
    
    return layer;
}

void UIHead:: initLayer()
{
    if ( !CCLayer::init() )
    {
        return;
    }
    
        
    
    
}

void UIHead::onClick(CCObject* pSender)
{
    
}

//======UIFoot======

LayerUI* UIFoot::scene(VoFoot* vo)
{
    
    CCScene *scene = CCScene::create();
    
    UIFoot *layer = UIFoot::create();
    
    layer->vo=vo;
    
    layer->initLayer();
    
    scene->addChild(layer);
    
    CCDirector::sharedDirector()->runWithScene(scene);
    
    return layer;
}

void UIFoot:: initLayer()
{
    if ( !CCLayer::init() )
    {
        return;
    }
    
    
    
    
}
