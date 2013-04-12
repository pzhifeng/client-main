#ifndef __client_main__SceneUI__
#define __client_main__SceneUI__

#include "cocos2d.h"


class SceneUI :public cocos2d::CCScene
{
private:
    
    //static std::map<void*,void*> components;
    
public:
    
    void* vo;
    
    //刷新面板数据
    static void refresh();

    
    static SceneUI* create(void);
    
        
    //添加一个组件
    static cocos2d::CCLabelTTF* addLable(const char *string, const char *fontName, float fontSize,void* key);
};

#endif