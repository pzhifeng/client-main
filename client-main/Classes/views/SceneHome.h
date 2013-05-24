#ifndef __client_main__SenceHome__
#define __client_main__SenceHome__

#include "cocos2d.h"
#include "../core/LayerUI.h"

//大地图，有UI头 UI尾
struct VoHome:VoObject {
    VoHead * head;
    cocos2d::CCArray finishGates;
};

//已完成关卡及评分
struct VoFinish:VoObject {
    int * id;
    int * score;
};

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