#ifndef __client_main__CommandUser__
#define __client_main__CommandUser__

#include "../core/Command.h"

class CommandUser :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};

class CommandUserName :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};

#endif 
