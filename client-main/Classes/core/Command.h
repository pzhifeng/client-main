#ifndef client_main_Command_h
#define client_main_Command_h

#include "cocos2d.h"
#include "LayerUI.h"


class Command
{

public:
	Command(void){};
	~Command(void){};
    
    virtual LayerUI* init()= 0;
    virtual void parse(LayerUI* layer,const char *data)=0;
	virtual void success(LayerUI* layer)= 0;
    
};



#endif
