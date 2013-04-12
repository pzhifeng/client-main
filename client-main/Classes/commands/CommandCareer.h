#ifndef __client_main__CommandCareer__
#define __client_main__CommandCareer__

#include "../core/Command.h"
#include "../VoObject.h"
class CommandCareer :public Command
{
public:
    static int Head;
public:
    SceneUI* success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};

#endif 
