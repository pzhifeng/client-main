#include "cocos-ext.h"
#include "Facade.h"
#include "SceneHome.h"
#include "../SceneMain.h"
#include "../commands/CommandHead.h"

USING_NS_CC;
USING_NS_CC_EXT;


bool SceneHome::init(){
    if ( !CCLayer::init() ){
        return false;
    }
    //todo初始化大地图
    
    return true;
}

bool SceneHome::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, CCString *pMemberVariableName, cocos2d::CCNode *pNode)
{
    return false;
}

SEL_MenuHandler SceneHome::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onGate1", SceneHome::onGate1);
    return NULL;
}

SEL_CCControlHandler SceneHome::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{

    return NULL;
}

void SceneHome::onGate1(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    Facade::send(CommandHead::Pve);
    CCLOG("%s","onGate1");
}


//SEL_MenuHandler SceneMap::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
//{
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onGate1", SceneMap::onGate1);
//    return NULL;
//}
//
//SEL_MenuHandler SceneMap::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
//{
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onGate1", SceneMap::onGate1);
//    return NULL;
//}
//
//void SceneMap::onGate1(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
//{
//    Facade::send(CommandHead::Pve);
//    CCLOG("%s","onGate1");
//}


