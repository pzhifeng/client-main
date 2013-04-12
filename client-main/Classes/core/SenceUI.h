#ifndef __client_main__SenceUI__
#define __client_main__SenceUI__

#include "cocos2d.h"
#include "Command.h"


class SceneUI :public cocos2d::CCScene
{
private:
    
    static std::map<void*,void*> components;
    
public:
    
    //VoObject* vo;
    
    //刷新面板数据
    void refresh();

    
    static SceneUI* create();
    
        
    //添加一个组件
    static cocos2d::CCLabelTTF* addLable(const char *string, const char *fontName, float fontSize,void* key);
};

#endif