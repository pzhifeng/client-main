#ifndef __client_main__SenceUI__
#define __client_main__SenceUI__

#include "cocos2d.h"
#include "VoObject.h"

class SceneUI : : public cocos2d::CCLayer
{
private:
    map<void*,void*> components;
    VoObject* vo;
    
public:

    //刷新面板数据
    void refresh();
    
    //添加一个组件
    CCLabelTTF* addLable(const char *string, const char *fontName, float fontSize,void* key);
}

#endif