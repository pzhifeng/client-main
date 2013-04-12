#include "SenceUI.h"
 

void SceneUI::refresh(){
    for (map<void*,void*>::iterator i=components.begin(); i!=componentscommands.end();)
	{
		void* key=i->first;
        
		CCLabelTTF* pLabel=(CCLabelTTF*)components[key];
        pLabel->setString(*key);
	}
}

//添加一个组件
CCLabelTTF* SceneUI::addLable(const char *title, const char *fontName, float fontSize,void* key){
    CCLabelTTF* pLabel = CCLabelTTF::create(title, fontName, fontSize);
    components[key]=pLabel;
    return pLabel;
}