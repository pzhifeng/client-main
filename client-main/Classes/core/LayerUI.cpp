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

int LayerUI::TagLayer=9999999;


void LayerUI::onHeader(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    CCLOG("%s","onHeader");
    Facade::send(CommandHead::Main);
}

void LayerUI::onMenu(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    CCMenuItemImage* menu=(CCMenuItemImage*)pSender;
    Facade::send(menu->getTag());
}

void LayerUI::freshHeader(){
    //经验进度条
    CCProgressTo *expTo = CCProgressTo::create(0.6,30);
    CCFileUtils::sharedFileUtils()->setResourceDirectory("ui");
    CCProgressTimer *left = CCProgressTimer::create(CCSprite::create("exp-value.png"));
    left->setType(kCCProgressTimerTypeBar);
    left->setMidpoint(ccp(0,0));
    left->setBarChangeRate(ccp(1,0));
    left->setAnchorPoint(ccp(0,0));
    left->setPosition(CCPointZero);
    left->runAction(expTo);
    expBg->addChild(left);

}

void LayerUI::freshFooter(int head){
    if(head==CommandHead::Home){
        menuHome->setEnabled(false);
        menuSkill->setEnabled(true);
        menuGod->setEnabled(true);
        menuCoin->setEnabled(true);
        menuArena->setEnabled(true);
        menuStore->setEnabled(true);
    }else if(head==CommandHead::Skill){
        menuHome->setEnabled(true);
        menuSkill->setEnabled(false);
        menuGod->setEnabled(true);
        menuCoin->setEnabled(true);
        menuArena->setEnabled(true);
        menuStore->setEnabled(true);
    }else if(head==CommandHead::God){
        menuHome->setEnabled(true);
        menuSkill->setEnabled(true);
        menuGod->setEnabled(false);
        menuCoin->setEnabled(true);
        menuArena->setEnabled(true);
        menuStore->setEnabled(true);
    }else if(head==CommandHead::Coin){
        menuHome->setEnabled(true);
        menuSkill->setEnabled(true);
        menuGod->setEnabled(true);
        menuCoin->setEnabled(false);
        menuArena->setEnabled(true);
        menuStore->setEnabled(true);
    }else if(head==CommandHead::Arena){
        menuHome->setEnabled(true);
        menuSkill->setEnabled(true);
        menuGod->setEnabled(true);
        menuCoin->setEnabled(true);
        menuArena->setEnabled(false);
        menuStore->setEnabled(true);
    }else if(head==CommandHead::Store){
        menuHome->setEnabled(true);
        menuSkill->setEnabled(true);
        menuGod->setEnabled(true);
        menuCoin->setEnabled(true);
        menuArena->setEnabled(true);
        menuStore->setEnabled(false);
    }
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
    removeLayer();
    
    CCScene* scene=cocos2d::CCDirector::sharedDirector()->getRunningScene();

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
    node->setTag(TagLayer);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate((CCLayer*)node,0,true);
    
    scene->addChild(node);
    
    return (LayerUI*)node;
}

void LayerUI::removeLayer(){
    CCScene* scene=cocos2d::CCDirector::sharedDirector()->getRunningScene();
    CCNode* sub=scene->getChildByTag(TagLayer);
    if(NULL!=sub){
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate((CCTouchDelegate*)sub);
        scene->removeChildByTag(TagLayer, true);
    }
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


