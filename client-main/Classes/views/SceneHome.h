#ifndef __client_main__SenceHome__
#define __client_main__SenceHome__

#include "cocos2d.h"
#include "../core/LayerUI.h"

//大地图，有UI头 UI尾
struct VoHome:VoObject {
    VoHead * head;
    cocos2d::CCArray finishGates;
};

//已完成关卡及评分
struct VoFinish:VoObject {
    int * id;
    int * score;
};

class SceneHome :
  public LayerUI
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
    
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SceneHome, create);
    bool init();
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);

    void onGate1(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
};

class SceneHomeLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SceneHomeLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SceneHome);
};

//=========SceneMap===========

//class SceneMap :
//public LayerUI
//, public cocos2d::extension::CCBMemberVariableAssigner
//, public cocos2d::extension::CCBSelectorResolver
//{
//    
//public:
//    
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SceneMap, create);
//    
//    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode);
//    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
//    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
//    
//    
//    void onGate1(cocos2d::CCObject *pSender);
//    
//};
//
//class SceneMapLoader : public cocos2d::extension::CCLayerLoader
//{
//public:
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SceneMapLoader, loader);
//protected:
//    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SceneMap);
//};


#endif 