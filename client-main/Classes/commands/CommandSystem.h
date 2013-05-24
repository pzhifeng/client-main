#ifndef __client_main__CommandServer__
#define __client_main__CommandServer__

#include "../core/Command.h"
#include "cocos2d.h"
#include "../utils/MyHttpRequest.h"

using namespace cocos2d;

//======CommandCheck======
class CommandCheck :public Command
{
public:
	MyHttpRequest *myHttpRequest;
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};

//======CommandMain======
class CommandMain :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};

//======CommandServer======
class CommandServer :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);};

//======CommandHome======
class CommandHome :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};



#endif