#include "SceneMain.h"

#include "core/Command.h"
#include "core/Client.h"
#include "Facade.h"
#include "commands/CommandSystem.h"
#include "views/SenceHome.h"


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
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);


    //add title
    CCLabelTTF* pLabel = CCLabelTTF::create("My Game", "Thonburi", 24);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    this->addChild(pLabel, 1);

    // add  screen bg
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//    pSprite->setPosition( ccp(size.width/2, size.height/2) );
//    this->addChild(pSprite, 0);
    
    //add menu
    CCMenuItemFont::setFontName("Marker Felt");
    CCMenuItemFont::setFontSize(22);
    CCMenuItemFont* pFontMenuItem1 = CCMenuItemFont::itemWithString("首页",this,menu_selector(SceneMain::start));
    CCMenuItemFont* pFontMenuItem2 = CCMenuItemFont::itemWithString("人物",this,menu_selector(SceneMain::start));
    pFontMenuItem2->setPositionY(-50);
    CCMenuItemFont* pFontMenuItem3 = CCMenuItemFont::itemWithString("装备",this,menu_selector(SceneMain::start));
    pFontMenuItem3->setPositionY(-100);

    CCMenu* pFontMenu = CCMenu::menuWithItems(pFontMenuItem1,pFontMenuItem2,pFontMenuItem3,NULL);
    pFontMenu->setPosition( ccp(size.width/2,size.height -80) );
    this->addChild(pFontMenu);
    
    initGame();
    
    return true;
}

void SceneMain::initGame(){
    //init system commands
    Facade::registerCommands();
    
    if(!Facade::isMock){
        Client* client=Client::GetInstance();
        bool b=client->connet(Facade::ip, Facade::port);
        if(b){
            client->setConfig("18602122551", "PASSPORT");
            Facade::send(CommandCheck::Head,Facade::version);
        }
    }
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
