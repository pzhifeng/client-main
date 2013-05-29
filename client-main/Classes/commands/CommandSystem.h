#ifndef __client_main__CommandServer__
#define __client_main__CommandServer__

#include "cocos2d.h"
#include "../core/Command.h"
#include "../utils/MyHttpRequest.h"

using namespace cocos2d;

//=========================
class CommandCheck :public Command
{
public:
	MyHttpRequest *myHttpRequest;
public:
    LayerUI* success(const char *data);
};

//=========================
class CommandMain :public Command
{
public:
    LayerUI* success(const char *data);
};

//=========================
class CommandMainServer :public Command
{
public:
    LayerUI* success(const char *data);
};

//=========================
class CommandMainServerSelect :public Command
{
public:
    LayerUI* success(const char *data);
};



#endif