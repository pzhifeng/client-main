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

int LayerUI::MainWin=9999999;
int LayerUI::SubWin=9999998;


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
    node->setTag(MainWin);
    scene->addChild(node);
    
    cocos2d::CCDirector::sharedDirector()->replaceScene(scene);
    
    return (LayerUI*)node;
}

LayerUI* LayerUI::layer(const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader){
    CCScene* scene=removeLayer();

    cocos2d::extension::CCNodeLoaderLibrary *lib = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
    cocos2d::extension::CCBReader *reader = new cocos2d::extension::CCBReader(lib);
    
    std:string tmp;
    tmp.append(pCCNodeName).append(".ccbi");
    CCNode *node = reader->readNodeGraphFromFile(tmp.c_str(), scene);
    reader->autorelease();
    
    CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    CCSize layerSize=node->getContentSize();
    node->setPosition(winSize.width/2-layerSize.width/2, winSize.height/2-layerSize.height/2+30);
    node->setTag(SubWin);

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate((CCLayer*)node,0,true);
    
    scene->addChild(node);    
    
    return (LayerUI*)node;
}

CCScene* LayerUI::removeLayer(){
    CCScene* scene=cocos2d::CCDirector::sharedDirector()->getRunningScene();
    CCNode* sub=scene->getChildByTag(SubWin);
    if(NULL!=sub){
        scene->removeChildByTag(SubWin, true);
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate((CCTouchDelegate*)sub);
    }
    return scene;
}


void LayerUI::exception(int code,const char *data){
    
}




//void CommandCheck::fail(int code,VoObject* vo){
//
//    SceneMain::scene((VoMain*)vo,false);
//
//	if(code==1){
//		/*
//		myHttpRequest=new MyHttpRequest();
//		myHttpRequest->doGet();
//		while(true){
//			if(myHttpRequest->m_isCompleted)
//				break;
//			Sleep(100);
//		}
//		//CCLOG("m_responseData===%s",myHttpRequest->m_responseData.c_str());
//
//		const char * fileName= "lang/zh_CN.properties";
//		//myHttpRequest->m_responseData="{\"v\":\"1.0\",\"email\":{\"1\":{\"content\":\"123888\",\"id\":1},\"2\":{\"content\":\"456\",\"id\":2}}}";
//		FileUtil::write(fileName,myHttpRequest->m_responseData.c_str());
//
//		myHttpRequest->release();
//		*/
//	}else if(code==2){
//
//	}
//}


