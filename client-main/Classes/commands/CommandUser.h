#ifndef __client_main__CommandUser__
#define __client_main__CommandUser__

#include "../core/Command.h"

class CommandUser :public Command
{
public:
    static int Head;
public:
    LayerUI* success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};

#endif 
