#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos-ext.h"
#include "cocos2d.h"
#include "LayerUI.h"


class SceneMain
: public LayerUI
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
{
public:
    cocos2d::CCLabelTTF *version;
    cocos2d::CCLabelTTF *server;
public:
    SceneMain();
    ~SceneMain();
    
    static LayerUI* scene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SceneMain, create);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual void onNodeLoaded(CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    void onStart(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void onExit(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

};


class SceneMainLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SceneMainLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SceneMain);
};

#endif
