#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos-ext.h"
#include "cocos2d.h"
#include "LayerUI.h"

struct VoServer:VoObject{
    int id;
    char * name;
    char * tag;
};

//========SceneMain==========
class SceneMain
: public LayerUI
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
{
public:
    cocos2d::CCLabelTTF *version;
    cocos2d::extension::CCControlButton *mainServer;
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
    void onMainServer(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void onExit(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

};


class SceneMainLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SceneMainLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SceneMain);
};


//========UIMainServer==========
//class UIMainServer
//: public cocos2d::CCLayer
//, public cocos2d::extension::CCBMemberVariableAssigner
//, public cocos2d::extension::CCBSelectorResolver
//{
//public:
//
//public:
//
//    
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(UIMainServer, create);
//    
//    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode);
//    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
//    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
//    
//};
//
//
//class UIMainServerLoader : public cocos2d::extension::CCLayerLoader
//{
//public:
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(UIMainServerLoader, loader);
//protected:
//    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(UIMainServer);
//};

class UIMainServer
: public cocos2d::CCLayer
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
{
public:
    virtual bool init();
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    
    //处理触摸事件，可以计算点击的是哪一个子项
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    //每一项的宽度和高度
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    //生成列表每一项的内容
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    //一共多少项
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    CREATE_FUNC(UIMainServer);
};


#endif
