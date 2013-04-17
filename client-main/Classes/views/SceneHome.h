#ifndef __client_main__SenceHome__
#define __client_main__SenceHome__

#include "cocos2d.h"
#include "../VoObject.h"
#include "../core/LayerUI.h"

class SceneHome : public LayerUI
{
    
public:
    static LayerUI* scene(VoHome* vo);
    
    VoHome* vo;
    
    void initLayer();

    void back(CCObject* pSender);

    CREATE_FUNC(SceneHome);
};

#endif 