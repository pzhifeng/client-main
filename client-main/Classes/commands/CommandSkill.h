#ifndef __client_main__CommandSkill__
#define __client_main__CommandSkill__

#include "cocos2d.h"
#include "../core/Command.h"



//======CommandSkill======
class CommandSkill :public Command
{
public:
    LayerUI* success(const char *data);
};

#endif 