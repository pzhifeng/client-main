#include "LayerUI.h"

std::map<void *,void*> LayerUI::components;

LayerUI* LayerUI::create(void){
    LayerUI *pRet = new LayerUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void LayerUI::refresh(){
    for (std::map<void *,void*>::iterator it=components.begin(); it!=components.end();++it)
	{
		void* key=it->first;
        
		cocos2d::CCLabelTTF* pLabel=(cocos2d::CCLabelTTF*)components[key];
        //CCLOG("VALUE: %s", *key);
        pLabel->setString((char *)key);
	}
}

//添加一个组件
cocos2d::CCLabelTTF* LayerUI::addLable(const char *title, const char *fontName, float fontSize,void* key){
    cocos2d::CCLabelTTF* pLabel = cocos2d::CCLabelTTF::create(title, fontName, fontSize);
    components[key]=pLabel;
    return pLabel;
}