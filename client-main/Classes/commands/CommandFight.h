#ifndef __client_main__CommandFight__
#define __client_main__CommandFight__

#include "../core/Command.h"
#include "cocos2d.h"

//======CommandGate======
class CommandGate :public Command
{
public:
    LayerUI* success(const char *data);
};

//======CommandPve======
class CommandPve :public Command
{
public:
    LayerUI* success(const char *data);};

#endif 
