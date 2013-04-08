#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class SceneMain : public cocos2d::CCLayer
{
public:

    virtual bool init();
    
    void initGame();

    static cocos2d::CCScene* scene();
    
    void start(CCObject* pSender);
    
    void exit(CCObject* pSender);

    CREATE_FUNC(SceneMain);
};

#endif // __MAIN_SCENE_H__
