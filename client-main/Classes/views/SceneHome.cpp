#include "cocos-ext.h"
#include "Facade.h"
#include "SceneHome.h"
#include "../SceneMain.h"
#include "../commands/CommandHead.h"

USING_NS_CC;
USING_NS_CC_EXT;


//todo大地图可拖动
//==========SceneHome===============
bool SceneHome::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, CCString *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "title", CCLabelTTF*, this->title);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate1", CCMenuItemImage*, this->homeGate1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate2", CCMenuItemImage*, this->homeGate2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate3", CCMenuItemImage*, this->homeGate3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate4", CCMenuItemImage*, this->homeGate4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate5", CCMenuItemImage*, this->homeGate5);
    return false;
}

SEL_MenuHandler SceneHome::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHome", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSkill", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onGod", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCoin", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onArena", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStore", LayerUI::onMenu);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeGate1", SceneHome::onHomeGate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeGate2", SceneHome::onHomeGate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeGate3", SceneHome::onHomeGate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeGate4", SceneHome::onHomeGate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeGate5", SceneHome::onHomeGate);


    return NULL;
}

SEL_CCControlHandler SceneHome::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    return NULL;
}

void SceneHome::onHomeGate(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    Facade::send(CommandHead::HomeGate);
}


//==========UIHomeGate===============
bool UIHomeGate::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, CCString *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "title", CCLabelTTF*, this->title);
    
    return false;
}

SEL_MenuHandler UIHomeGate::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler UIHomeGate::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onHomePve", UIHomeGate::onHomePve);
    return NULL;
}

void UIHomeGate::onHomePve(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    Facade::send(CommandHead::HomePve);
}



