#ifndef client_main_Command_h
#define client_main_Command_h

#include "cocos2d.h"
#include "LayerUI.h"


class Command
{

public:
    
	virtual LayerUI* success(const char *data)= 0;
    
};



#endif
