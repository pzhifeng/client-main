#ifndef __client_main__SenceTest__
#define __client_main__SenceTest__

#include "cocos2d.h"
#include "../VoObject.h"
#include "../core/LayerUI.h"

class SceneTest : public LayerUI
{
    
public:
    static LayerUI* scene(VoTest* vo);
    
    VoTest* vo;
    
    void initLayer();
    
    void back(CCObject* pSender);
    
    CREATE_FUNC(SceneTest);
};

#endif