#ifndef __client_main__LayerUI__
#define __client_main__LayerUI__

#include "cocos2d.h"


class LayerUI :public cocos2d::CCLayer
{
private:
    
    static std::map<void *,void*> components;
    
public:
    
    ~LayerUI(void);
    
	void* vo;
    
    //刷新面板数据
    void refresh();
    
    
    static LayerUI* create(void);
    
    
    //添加一个组件
    cocos2d::CCLabelTTF* addLable(const char *title, const char *fontName, float fontSize,void* key);
};

#endif