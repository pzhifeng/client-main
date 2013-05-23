#ifndef __client_main__UICommon__
#define __client_main__UICommon__

#include "cocos2d.h"
#include "../core/LayerUI.h"

class UIHead : public LayerUI
{
    
public:
    static LayerUI* scene(VoHead* vo);
    
    VoHead* vo;
    
    void initLayer();
    
    void onClick(CCObject* pSender);
    
    CREATE_FUNC(UIHead);
};

class UIFoot : public LayerUI
{
    
public:
    static LayerUI* scene(VoFoot* vo);
    
    VoFoot* vo;
    
    void initLayer();
    
    CREATE_FUNC(UIFoot);
};

#endif 
