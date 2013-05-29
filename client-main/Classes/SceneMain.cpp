#include "SceneMain.h"
#include "Facade.h"
#include "views/SceneHome.h"
#include "commands/CommandHead.h"


USING_NS_CC;
USING_NS_CC_EXT;

//========SceneMain==========
SceneMain::SceneMain()
: version(NULL)
, mainServer(NULL)
{}

SceneMain::~SceneMain()
{
    CC_SAFE_RELEASE(version);
    CC_SAFE_RELEASE(mainServer);
}

LayerUI* SceneMain::scene()
{
    CCScene *scene = CCScene::create();
    
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    lib->registerCCNodeLoader("SceneMain", SceneMainLoader::loader());
    
    CCBReader *reader = new CCBReader(lib);
    
    CCNode *node = reader->readNodeGraphFromFile("SceneMain.ccbi", scene);
    
    reader->release();
    
    if (node!=NULL)
    {
        scene->addChild(node);
    }
    
    
    if(NULL==CCDirector::sharedDirector()->getRunningScene()){
        CCDirector::sharedDirector()->runWithScene(scene);
    }else{
        CCDirector::sharedDirector()->replaceScene(scene);
    }
    
    
    return (LayerUI*)node;
}

bool SceneMain::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, CCString *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "version", CCLabelTTF*, this->version);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mainServer", CCControlButton*, this->mainServer);
    return false;
}

SEL_MenuHandler SceneMain::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler SceneMain::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMainServer", SceneMain::onMainServer);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMainServer2", SceneMain::onMainServer);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onStart", SceneMain::onStart);
    
    return NULL;
}

void SceneMain::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}


void SceneMain::onStart(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    Facade::send(CommandHead::Home);
}

void SceneMain::onMainServer(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    Facade::send(CommandHead::MainServer);
}


void SceneMain::onExit(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//=========UIMainServer=========

bool UIMainServer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF( !CCLayer::init() );
        
        CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
        CCTableView* pTableView = CCTableView::create(this, CCSizeMake(220,180));
        pTableView->setDirection(kCCScrollViewDirectionVertical);
        pTableView->setPosition(CCPointMake(winSize.width/2-90,winSize.height/2-60));
        pTableView->setDelegate(this);
        pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        pTableView->setTag(LayerUI::SubWin);
        this->addChild(pTableView);
        pTableView->reloadData();        
        bRet = true;
    }while(0);
    
    return bRet;
}

void UIMainServer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
    this->removeChildByTag(LayerUI::SubWin, true);
    
    Facade::send(CommandHead::MainServerSelect);
}

CCSize UIMainServer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(220,30);
}

CCTableViewCell* UIMainServer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *pString = CCString::createWithFormat("%d", idx);
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCFileUtils::sharedFileUtils()->setResourceDirectory("ui");
        CCSprite *pSprite = CCSprite::create("home-bg.png");
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
        
        VoServer *vo=Facade::Servers[idx+1];
        std:string tmp;
        tmp.append(vo->name).append("  ").append(vo->tag);
        CCLabelTTF *pLabel = CCLabelTTF::create(tmp.c_str(), "Arial", 20.0);
        pLabel->setPosition(CCPointZero);
        pLabel->setAnchorPoint(CCPointZero);
        pLabel->setTag(1000+idx);
        pCell->addChild(pLabel);
    }
    else
    {
        //CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(1000+idx);
        //pLabel->setString(pString->getCString());
    }
    
    return pCell;
}

unsigned int UIMainServer::numberOfCellsInTableView(CCTableView *table)
{
    return Facade::Servers.size();
}

void UIMainServer::scrollViewDidScroll(CCScrollView *view)
{
    CCLog("scrollViewDidScroll");
}

void UIMainServer::scrollViewDidZoom(CCScrollView *view)
{
    CCLog("scrollViewDidScroll");
}