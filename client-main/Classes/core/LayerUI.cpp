#include "LayerUI.h"
#include "../Facade.h"
#include "../commands/CommandHead.h"

USING_NS_CC;
USING_NS_CC_EXT;

LayerUI* LayerUI::layer(const char * pCCBFileName, const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader){
    return NULL;
}

LayerUI* LayerUI::window(const char * pCCBFileName, const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader)
{
    cocos2d::CCScene *scene = cocos2d::CCScene::create();
    
    cocos2d::extension::CCNodeLoaderLibrary *lib = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    lib->registerCCNodeLoader("Header", HeaderLoader::loader());
    
    lib->registerCCNodeLoader("Footer", FooterLoader::loader());

    
    if (pCCNodeName!=NULL && pCCNodeLoader!=NULL)
    {
        lib->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
    }
    
    cocos2d::extension::CCBReader *reader = new cocos2d::extension::CCBReader(lib);
    CCNode *node = reader->readNodeGraphFromFile(pCCBFileName, this);
    reader->autorelease();
    
    if (node != NULL)
    {
        scene->addChild(node);
    }
    
    cocos2d::CCDirector::sharedDirector()->replaceScene(scene);
    
    return this;
}

void LayerUI::exception(int code,const char *data){
    
}


//======Header=======

bool Header::onAssignCCBMemberVariable(CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode){
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "name", cocos2d::CCLabelTTF*, this->name);
    return true;
}

cocos2d::SEL_MenuHandler Header::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, cocos2d::CCString *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClick", Header::onClick);
    
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler Header::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, cocos2d::CCString *pSelectorName)
{
    return NULL;
}

void Header::onClick(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    CCLOG("%s","onClick");
    Facade::send(CommandHead::Main);
}

//======Footer=======

cocos2d::SEL_MenuHandler Footer::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, cocos2d::CCString *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuHome", Footer::menuHome);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuSkill", Footer::menuSkill);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuGod", Footer::menuGod);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuArena", Footer::menuArena);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuCoin", Footer::menuCoin);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuStore", Footer::menuStore);
    
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler Footer::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, cocos2d::CCString *pSelectorName)
{
    return NULL;
}

void Footer::menuHome(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    Facade::send(CommandHead::Home);
    CCLOG("%s","menuHome");
}

void Footer::menuSkill(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    Facade::send(CommandHead::Pve);
    CCLOG("%s","meunSkill");
}

void Footer::menuGod(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    //Facade::send(CommandHome::Head);
    CCLOG("%s","meunGod");
}

void Footer::menuArena(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    //Facade::send(CommandHome::Head);
    CCLOG("%s","meunArena");
}

void Footer::menuCoin(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    //Facade::send(CommandHome::Head);
    CCLOG("%s","meunCoin");
}

void Footer::menuStore(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    //Facade::send(CommandHome::Head);
    CCLOG("%s","menuStore");
}

