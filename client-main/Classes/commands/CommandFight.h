#ifndef __client_main__CommandFight__
#define __client_main__CommandFight__

#include "../core/Command.h"
#include "cocos2d.h"

//======CommandPve======
class CommandPve :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};

#endif 
