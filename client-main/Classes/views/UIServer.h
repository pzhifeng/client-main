#ifndef __client_main__UIServer__
#define __client_main__UIServer__

#include "cocos2d.h"
#include "../core/LayerUI.h"

//服务器列表
struct VoServer:VoObject{
    int id;
    char * name;
    char * domain;
    char * tag;
};

class UIServer : public LayerUI
{
    
public:
    static LayerUI* scene(VoServer* vo);
    
    VoServer* vo;
    
    void initLayer();
    
    void onClick(CCObject* pSender);
    
    CREATE_FUNC(UIServer);
};

#endif
