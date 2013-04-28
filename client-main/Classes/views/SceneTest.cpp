#include "SceneTest.h"
#include "../SceneMain.h"
#include "Facade.h"
using namespace cocos2d;

LayerUI* SceneTest::scene(VoTest* vo)
{
    
    CCScene *scene = CCScene::create();
    
    SceneTest *layer = SceneTest::create();
    
    layer->vo=vo;
    
    layer->initLayer();
    
    scene->addChild(layer);
    
    CCDirector::sharedDirector()->replaceScene(scene);
    
    return layer;
}

void SceneTest:: initLayer()
{
    if ( !CCLayer::init() )
    {
        return;
    }
    
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(SceneTest::back) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    CCLabelTTF* pLabel = addLable("", "Thonburi", 34,vo->name);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    this->addChild(pLabel, 1);
    
    CCLabelTTF* pLabel2 = addLable("", "Thonburi", 34,vo->title);
    pLabel2->cocos2d::CCNode::setPosition(200, 200);
    this->addChild(pLabel2, 1);
    
    
}

void SceneTest::back(CCObject* pSender)
{
    LayerUI *pScene = SceneMain::scene(NULL,false);
	//CCDirector::sharedDirector()->replaceScene(pScene);
}
