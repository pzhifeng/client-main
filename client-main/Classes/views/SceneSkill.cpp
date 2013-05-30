#include "SceneSkill.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool SceneSkill::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, CCString *pMemberVariableName, cocos2d::CCNode *pNode)
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
    
  
    return false;
}

SEL_MenuHandler SceneSkill::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    //绑定页脚菜单按扭
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuHome", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuSkill", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuGod", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuCoin", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuArena", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuStore", LayerUI::onMenu);

    
       
    return NULL;
}

SEL_CCControlHandler SceneSkill::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    return NULL;
}
