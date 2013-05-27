#ifndef __client_main__CommandSkill__
#define __client_main__CommandSkill__

#include "cocos2d.h"
#include "../core/Command.h"



//======CommandSkill======
class CommandSkill :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};

#endif 