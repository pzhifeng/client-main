#ifndef __client_main__CommandServer__
#define __client_main__CommandServer__

#include "../core/Command.h"
#include "cocos2d.h"
#include "utils/MyHttpRequest.h"

using namespace cocos2d;

class CommandCheck :public Command
{
public:
    static int Head;
	MyHttpRequest *myHttpRequest;
public:
    LayerUI* success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};

class CommandServer :public Command
{
public:
    static int Head;
public:
    LayerUI* success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};



#endif