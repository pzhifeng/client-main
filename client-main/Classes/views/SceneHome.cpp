#include "cocos-ext.h"
#include "cocos2d.h"
#include "Facade.h"
#include "SceneHome.h"
#include "../SceneMain.h"
#include "../commands/CommandHead.h"

USING_NS_CC;
USING_NS_CC_EXT;


//==========SceneHome===============
bool SceneHome::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, CCString *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //绑定头部变量
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "title", CCLabelTTF*, this->title);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "expBg", CCSprite*, this->expBg);
    //绑定页脚菜单变量
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuHome", CCMenuItemImage*, this->menuHome);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuSkill", CCMenuItemImage*, this->menuSkill);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuGod", CCMenuItemImage*, this->menuGod);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuCoin", CCMenuItemImage*, this->menuCoin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuArena", CCMenuItemImage*, this->menuArena);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "menuStore", CCMenuItemImage*, this->menuStore);
    
    //绑定当前业务变量
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeMap", CCSprite*, this->homeMap);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate1", CCMenuItemImage*, this->homeGate1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate2", CCMenuItemImage*, this->homeGate2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate3", CCMenuItemImage*, this->homeGate3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate4", CCMenuItemImage*, this->homeGate4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homeGate5", CCMenuItemImage*, this->homeGate5);
    return false;
}

SEL_MenuHandler SceneHome::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    //绑定页脚菜单按扭
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuHome", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuSkill", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuGod", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuCoin", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuArena", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuStore", LayerUI::onMenu);
    
    //绑定当前业务操作
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

void SceneHome::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);    
}

void SceneHome::onHomeGate(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    Facade::send(CommandHead::HomeGate);
}

CCPoint began;
bool SceneHome::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCLOG("SceneHome ccTouchBegan");
    CCPoint touchLocation = pTouch->getLocationInView();
    // 把点的坐标转换成OpenGL坐标（左下角为原点）
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    // 把OpenGL的坐标转换成CCLayer的坐标
    began = convertToNodeSpace(touchLocation);
    return true;
}

void SceneHome::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCLOG("SceneHome ccTouchMoved");
    //获取点在视图中的坐标（左上角为原点）
    CCPoint touchLocation = pTouch->getLocationInView();
    // 把点的坐标转换成OpenGL坐标（左下角为原点）
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    // 把OpenGL的坐标转换成CCLayer的坐标
    CCPoint moved = convertToNodeSpace(touchLocation);
    int x=homeMap->getPositionX()+(moved.x-began.x);
    int y=homeMap->getPositionY()+(moved.y-began.y);
    CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    if(x<winSize.width-homeMap->getContentSize().width/2){
        x=winSize.width-homeMap->getContentSize().width/2;
    }
    if(x>homeMap->getContentSize().width/2){
        x=homeMap->getContentSize().width/2;
    }
    
    if(y<winSize.height-homeMap->getContentSize().height/2){
        y=winSize.height-homeMap->getContentSize().height/2;
    }
    if(y>homeMap->getContentSize().height/2){
        y=homeMap->getContentSize().height/2;
    }

    homeMap->setPositionX(x);
    homeMap->setPositionY(y);
}

void SceneHome::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCLOG("SceneHome ccTouchEnded");
}

//==========UIHomeGate===============
bool UIHomeGate::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, CCString *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "gateTitle", CCLabelTTF*, this->gateTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "homePve", CCControlButton*, this->homePve); 
    
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

void UIHomeGate::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this->homePve,-1,true);
}

void UIHomeGate::onHomePve(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    Facade::send(CommandHead::HomePve);
}

bool UIHomeGate::init(){
    
    return true;
}

bool UIHomeGate::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCLOG("ccTouchBegan");
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this->homePve);
    LayerUI::removeLayer();
    
    return false;
}


