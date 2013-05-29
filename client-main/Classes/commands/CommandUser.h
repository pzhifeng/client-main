#ifndef __client_main__CommandUser__
#define __client_main__CommandUser__

#include "../core/Command.h"

//=========================
class CommandUser :public Command
{
public:
    LayerUI* success(const char *data);
};

//=========================
class CommandUserName :public Command
{
public:
    LayerUI* success(const char *data);
};

#endif 
