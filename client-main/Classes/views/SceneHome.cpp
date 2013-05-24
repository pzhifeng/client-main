#include "SceneHome.h"
#include "../SceneMain.h"
#include "Facade.h"
using namespace cocos2d;

LayerUI* SceneHome::scene(VoHome* vo)
{
    
    CCScene *scene = CCScene::create();

    SceneHome *layer = SceneHome::create();
    
    layer->vo=vo;
    
    layer->initLayer();

    scene->addChild(layer);
    
    CCDirector::sharedDirector()->replaceScene(scene);
    
    return layer;
}

void SceneHome:: initLayer()
{
    if ( !CCLayer::init() )
    {
        return;
    }
    


}

void SceneHome::back(CCObject* pSender)
{
    LayerUI *pScene = SceneMain::scene(NULL,false);
}
