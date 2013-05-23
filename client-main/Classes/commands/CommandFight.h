#ifndef __client_main__CommandFight__
#define __client_main__CommandFight__

#include "../core/Command.h"
#include "cocos2d.h"

//======CommandFightPve======
class CommandFightPve :public Command
{
public:
    static int Head;
public:
    LayerUI* success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};

#endif 
