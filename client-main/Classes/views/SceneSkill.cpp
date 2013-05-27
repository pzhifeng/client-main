#include "SceneSkill.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool SceneSkill::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, CCString *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "title", CCLabelTTF*, this->title);
    
  
    return false;
}

SEL_MenuHandler SceneSkill::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHome", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSkill", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onGod", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCoin", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onArena", LayerUI::onMenu);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStore", LayerUI::onMenu);
    
       
    return NULL;
}

SEL_CCControlHandler SceneSkill::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, CCString *pSelectorName)
{
    return NULL;
}
