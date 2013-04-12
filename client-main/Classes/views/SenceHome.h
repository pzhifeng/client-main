#ifndef __client_main__SenceHome__
#define __client_main__SenceHome__

#include "cocos2d.h"
#include "../VoObject.h"
#include "../core/SenceUI.h"

class SceneHome : public cocos2d::CCLayer
{
    
public:
    VoHome* vo;
    
    virtual bool init();
    
    static SceneUI* scene();

    void back(CCObject* pSender);

    CREATE_FUNC(SceneHome);
};

#endif 