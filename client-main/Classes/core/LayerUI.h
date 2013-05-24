#ifndef __client_main__LayerUI__
#define __client_main__LayerUI__

#include "cocos2d.h"
#include "cocos-ext.h"

struct VoObject{
    
};

//UI头
struct VoHead:VoObject{
    char * image;//头衔头像
    int * lv;
    int * exp;
    int * expMax;
    int * power;
    int * powerMax;
    int * leftSeconds;
    int * coin;
    int * money;
};

//UI尾，功能的开放等级
struct VoFoot:VoObject{
    
};


class LayerUI :public cocos2d::CCLayer
{
private:
    
    std::map<void *,void*> components;
    
public:

    //非正常场景的统一处理
    void exception(int code,const char *data);
    
    //打开非全屏的弹层
    LayerUI* layer(const char * pCCBFileName, const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader);
    
    //打开全屏的新窗体
    LayerUI* window(const char * pCCBFileName, const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader);

};


//=========Header======
class Header
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Header, create);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, cocos2d::CCString * pMemberVariableName, CCNode * pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    void onClick(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
 
private:
    cocos2d::CCLabelTTF *name;
};

class HeaderLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HeaderLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Header);
};


//===========Footer======
class Footer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Footer, create);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    void menuHome(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void menuSkill(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void menuGod(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void menuArena(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void menuCoin(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    void menuStore(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
};

class FooterLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FooterLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Footer);
};

#endif