#ifndef __client_main__CommandHome__
#define __client_main__CommandHome__

#include "cocos2d.h"
#include "../core/Command.h"


//======CommandHome======
class CommandHome :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};

//======CommandHomeGate======
class CommandHomeGate :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};

//======CommandHomePve======
class CommandHomePve :public Command
{
public:
    LayerUI* init();
    void parse(LayerUI* layer,const char *data);
    void success(LayerUI* layer);
};
#endif 
