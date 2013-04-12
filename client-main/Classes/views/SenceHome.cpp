#include "SenceHome.h"
#include "../SceneMain.h"
#include "Facade.h"
using namespace cocos2d;

SceneUI* SceneHome::scene()
{
    SceneUI *scene = SceneUI::create();

    SceneHome *layer = SceneHome::create();

    scene->addChild(layer);
    
    return scene;
}

bool SceneHome::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(SceneHome::back) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    CCLabelTTF* pLabel = addLable("", "Thonburi", 34,&vo->name);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    this->addChild(pLabel, 1);

    return true;
}

void SceneHome::back(CCObject* pSender)
{
    CCScene *pScene = SceneMain::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
