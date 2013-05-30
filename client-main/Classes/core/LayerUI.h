#ifndef __client_main__LayerUI__
#define __client_main__LayerUI__

#include "cocos2d.h"
#include "cocos-ext.h"

struct VoObject{
    
};

//UI头
struct VoHead:VoObject{
    char * image;//头衔头像
    int lv;
    int exp;
    int expMax;
    int power;
    int powerMax;
    int leftSeconds;
    int coin;
    int money;
};

//UI尾，功能的开放等级
struct VoFoot:VoObject{
    
};

//=========Header======
//class Header
//: public cocos2d::CCLayer
//, public cocos2d::extension::CCBMemberVariableAssigner
//{
//public:
//    //cocos2d::CCLabelTTF *title;
//public:
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Header, create);
//    
//    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode);
//    //virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
//    //virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
//    
//    //void onHeader(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
//    
//    
//private:
//    
//};
//
//class HeaderLoader : public cocos2d::extension::CCLayerLoader
//{
//public:
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HeaderLoader, loader);
//protected:
//    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Header);
//};
//
//
////===========Footer======
//class Footer
//: public cocos2d::CCLayer
//, public cocos2d::extension::CCBSelectorResolver
//{
//public:
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Footer, create);
//    
//    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
//    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
//    
//    void onMenu(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
//    
//};
//
//class FooterLoader : public cocos2d::extension::CCLayerLoader
//{
//public:
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FooterLoader, loader);
//protected:
//    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Footer);
//};
//
//========LayerUI==============

class LayerUI
: public cocos2d::CCLayer
{
public:
    static int TagLayer;
    
    cocos2d::CCLabelTTF *title;
    cocos2d::CCSprite *expBg;
    
    cocos2d::CCMenuItemImage *menuHome;
    cocos2d::CCMenuItemImage *menuSkill;
    cocos2d::CCMenuItemImage *menuGod;
    cocos2d::CCMenuItemImage *menuCoin;
    cocos2d::CCMenuItemImage *menuArena;
    cocos2d::CCMenuItemImage *menuStore;
public:
    //LayerUI();
    //~LayerUI();
    
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerUI, create);
    
    //页头页尾公共方法
    void onHeader(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void onMenu(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void freshFooter(int head);
    void freshHeader();
    
    //打开全屏窗体
    static LayerUI* scene(const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader);
    
    //打开非全屏的弹层
    static LayerUI* layer(const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader);
    
    static void removeLayer();

    //非正常场景的统一处理
    static void exception(int code,const char *data);

};



#endif