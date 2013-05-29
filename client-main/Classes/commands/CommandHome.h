#ifndef __client_main__CommandHome__
#define __client_main__CommandHome__

#include "cocos2d.h"
#include "../core/Command.h"


//======CommandHome======
class CommandHome :public Command
{
public:
    LayerUI* success(const char *data);
};

//======CommandHomeGate======
class CommandHomeGate :public Command
{
public:
    LayerUI* success(const char *data);
};

//======CommandHomePve======
class CommandHomePve :public Command
{
public:
    LayerUI* success(const char *data);
};
#endif 
