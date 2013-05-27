#ifndef __client_main__SenceHome__
#define __client_main__SenceHome__

#include "cocos2d.h"
#include "../core/LayerUI.h"


//=========SceneHome===========
class SceneHome :
  public LayerUI
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
    
public:
    cocos2d::CCMenuItemImage *homeGate1;
    cocos2d::CCMenuItemImage *homeGate2;
    cocos2d::CCMenuItemImage *homeGate3;
    cocos2d::CCMenuItemImage *homeGate4;
    cocos2d::CCMenuItemImage *homeGate5;

public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SceneHome, create);

    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    void onHomeGate(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
};

class SceneHomeLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SceneHomeLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SceneHome);
};


//=========UIGate===========
class UIHomeGate :
public LayerUI
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
    
public:
    cocos2d::CCLabelTTF *title;    
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(UIHomeGate, create);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    void onHomePve(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
   
};

class UIHomeGateLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(UIHomeGateLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(UIHomeGate);
};




#endif 