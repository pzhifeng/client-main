#ifndef __client_main__LayerUI__
#define __client_main__LayerUI__

#include "cocos2d.h"

struct VoObject{
    
};

//UI头
struct VoHead:VoObject{
    char * image;//头衔头像
    int * lv;
    int * exp;
    int * expMax;
    int * power;
    int * powerMax;
    int * leftSeconds;
    int * coin;
    int * money;
};

//UI尾，功能的开放等级
struct VoFoot:VoObject{
    
};


class LayerUI :public cocos2d::CCLayer
{
private:
    
    std::map<void *,void*> components;
    
public:
    
    //当前视图中需要用到的数据结构
	VoObject* vo;
    
    //刷新面板数据
    void refresh();
    
    //创建
    static LayerUI* create(void);
    
    //各UI中公共的头部
    void addHead();
    
    //各UI中公共的尾部
    void addFoot();
    
    //添加一个组件
    cocos2d::CCLabelTTF* addLable(const char *title, const char *fontName, float fontSize,void* key);
    
    

};

#endif