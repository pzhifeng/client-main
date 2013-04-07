#ifndef __client_main__CommandServer__
#define __client_main__CommandServer__

#include "../core/Command.h"


class CommandCheck :public Command
{
public:
    static int Head;
public:
    void success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};

class CommandServer :public Command
{
public:
    static int Head;
public:
    void success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};



#endif