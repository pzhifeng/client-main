#include "UIServer.h"
#include "Facade.h"
#include "../SceneMain.h"
using namespace cocos2d;

LayerUI* UIServer::scene(VoServer* vo)
{
    
    CCScene *scene = CCScene::create();
    
    UIServer *layer = UIServer::create();
    
    layer->vo=vo;
    
    layer->initLayer();
    
    scene->addChild(layer);
    
    CCDirector::sharedDirector()->runWithScene(scene);
    
    return layer;
}

void UIServer:: initLayer()
{
    if ( !CCLayer::init() )
    {
        return;
    }
    
    //todo 循环
    
    CCLabelTTF* pLabel = addLable("", "Thonburi", 24 ,vo->name);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    this->addChild(pLabel, 1);
    
    
    
}

void UIServer::onClick(CCObject* pSender)
{
    
}
