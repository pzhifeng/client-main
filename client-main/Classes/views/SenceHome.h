#ifndef __client_main__SenceHome__
#define __client_main__SenceHome__

#include "cocos2d.h"
#include "../VoObject.h"
#include "../core/SenceUI.h"

class SceneHome : public SceneUI
{
private:
    VoHome* vo;
    
public:
    
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();

    void back(CCObject* pSender);

    CREATE_FUNC(SceneHome);
};

#endif 