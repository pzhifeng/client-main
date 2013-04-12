#include "SenceUI.h"

SceneUI* SceneUI::create(){
    SceneUI *scene = (SceneUI*)CCScene::create();
    
    return scene;
}

void SceneUI::refresh(){
    for (std::map<void*,void*>::iterator i=components.begin(); i!=components.end();)
	{
		void* key=i->first;
        
		cocos2d::CCLabelTTF* pLabel=(cocos2d::CCLabelTTF*)components[key];
        pLabel->setString(*key);
	}
}

//添加一个组件
cocos2d::CCLabelTTF* SceneUI::addLable(const char *title, const char *fontName, float fontSize,void* key){
    cocos2d::CCLabelTTF* pLabel = cocos2d::CCLabelTTF::create(title, fontName, fontSize);
    components[key]=pLabel;
    return pLabel;
}