#include "SceneMain.h"
#include "Facade.h"
#include "commands/CommandSystem.h"
#include "core/SmartRes.h"

using namespace cocos2d;

CCScene* SceneMain::scene()
{
    CCScene *scene = CCScene::create();
    
    SceneMain *layer = SceneMain::create();

    scene->addChild(layer);

    return scene;
}

bool SceneMain::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }


    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(SceneMain::exit) );
    pCloseItem->setPosition(ccp(_right-30,_bottom+30));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

	
    //add title
    CCLabelTTF* pLabel = CCLabelTTF::create("My Game", "Thonburi", SCALE_FACTOR*60);
    pLabel->setPosition(ccp(_center.x, _top-100));
    this->addChild(pLabel, 1);
	CCLOG("SCALE_FACTOR===%f",SCALE_FACTOR);
	
    // add  screen bg
    CCSprite* bg = CCSprite::create("bg.jpg");
	bg->setPosition(_center);
	addChild(bg);
	
	//CCSprite* title = CCSprite::create("title.png");
	//title->setPosition(ccp(_center.x, _center.y + 120));
	//addChild(title);
	
	CCSprite* buttonPlay = CCSprite::create("buttonPlay.png");
	buttonPlay->setPosition(ccp(_center.x - 180, _bottom + 140));
	addChild(buttonPlay);

	CCSprite* buttonMore = CCSprite::create("buttonMore.png");
	buttonMore->setPosition(ccp(_center.x + 180, _bottom + 140));
	addChild(buttonMore);
    
    //add menu
    CCMenuItemFont::setFontName("Marker Felt");
    CCMenuItemFont::setFontSize(SCALE_FACTOR*60);
    CCMenuItemFont* pFontMenuItem1 = CCMenuItemFont::create(Facade::Langs["首页"].value.c_str(),this,menu_selector(SceneMain::start));;  
    CCMenuItemFont* pFontMenuItem2 = CCMenuItemFont::create(Facade::Langs["人物"].value.c_str(),this,menu_selector(SceneMain::start));
    pFontMenuItem2->setPositionY(-100);
    CCMenuItemFont* pFontMenuItem3 = CCMenuItemFont::create(Facade::Langs["装备"].value.c_str(),this,menu_selector(SceneMain::start));
    pFontMenuItem3->setPositionY(-200);

    CCMenu* pFontMenu = CCMenu::create(pFontMenuItem1,pFontMenuItem2,pFontMenuItem3,NULL); 
	pFontMenu->setPosition(ccp(_center.x, _top-300)); 
    this->addChild(pFontMenu);
	
    return true;
}



void SceneMain::start(CCObject* pSender)
{
    //Facade::send(CommandCheck::Head,Facade::version);
    Facade::send(CommandServer::Head);
}


void SceneMain::exit(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
