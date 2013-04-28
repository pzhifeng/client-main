#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "VoObject.h"
#include "core/LayerUI.h"

class SceneMain : public LayerUI
{
public:

    static LayerUI* scene(VoMain* vo,bool isFirst);
    
    VoMain* vo;
    
    void initLayer();
    
    void initGame();
    
    void start(CCObject* pSender);
    
    void test(CCObject* pSender);
    
    void exit(CCObject* pSender);

    CREATE_FUNC(SceneMain);
};

#endif 
