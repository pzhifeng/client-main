#include "LayerUI.h"
#include "SmartRes.h"
#include "../Facade.h"
#include "../commands/CommandHead.h"

USING_NS_CC;
USING_NS_CC_EXT;

//======LayerUI=======
//
//LayerUI::LayerUI()
//: title(NULL)
//{}
//
//LayerUI::~LayerUI()
//{
//    CC_SAFE_RELEASE(title);
//}

void LayerUI::onHeader(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    CCLOG("%s","onHeader");
    Facade::send(CommandHead::Main);
}

void LayerUI::onMenu(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    CCMenuItemImage* menu=(CCMenuItemImage*)pSender;
    Facade::send(menu->getTag());
    //this->title->setString("onMenu");
    CCLOG("%s:%d","onMenu",menu->getTag());
}

LayerUI* LayerUI::scene(const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader){
    cocos2d::CCScene *scene = cocos2d::CCScene::create();
    
    cocos2d::extension::CCNodeLoaderLibrary *lib = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
    cocos2d::extension::CCBReader *reader = new cocos2d::extension::CCBReader(lib);
    
    std:string tmp;
    tmp.append(pCCNodeName).append(".ccbi");
    CCNode *node = reader->readNodeGraphFromFile(tmp.c_str(), scene);
    reader->autorelease();
    scene->addChild(node);
    
    cocos2d::CCDirector::sharedDirector()->replaceScene(scene);
    
    return (LayerUI*)node;
}

LayerUI* LayerUI::layer(const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader){
    CCScene* scene=cocos2d::CCDirector::sharedDirector()->getRunningScene();
    
    cocos2d::extension::CCNodeLoaderLibrary *lib = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
    cocos2d::extension::CCBReader *reader = new cocos2d::extension::CCBReader(lib);
    
    std:string tmp;
    tmp.append(pCCNodeName).append(".ccbi");
    CCNode *node = reader->readNodeGraphFromFile(tmp.c_str(), scene);
    reader->autorelease();
    
    CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    node->setPosition(winSize.width/2-100, winSize.height/2-80);
    scene->addChild(node);

    return (LayerUI*)node;
}


void LayerUI::exception(int code,const char *data){
    
}

