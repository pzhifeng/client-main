#include "SceneMain.h"
#include "Facade.h"
#include "views/SceneHome.h"
#include "commands/CommandHead.h"


USING_NS_CC;
USING_NS_CC_EXT;

SceneMain::SceneMain()
: version(NULL)
, server(NULL)
{}

SceneMain::~SceneMain()
{
    CC_SAFE_RELEASE(version);
    CC_SAFE_RELEASE(server);
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
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "server", CCLabelTTF*, this->server);
    return false;
}

SEL_MenuHandler SceneMain::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler SceneMain::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onStart", SceneMain::onStart);
    
    return NULL;
}

void SceneMain::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    //this->mLabelText->setString("All Loaded");
}


void SceneMain::onStart(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    Facade::send(CommandHead::Home);
}


void SceneMain::onExit(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
