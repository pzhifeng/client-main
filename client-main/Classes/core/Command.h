#ifndef client_main_Command_h
#define client_main_Command_h

#include "cocos2d.h"
#include "LayerUI.h"

struct VoObject{
    
};

class Command
{

public:
	Command(void){};
	~Command(void){};
    
	virtual LayerUI* success(VoObject* vo)= 0;
	virtual void fail(int code,VoObject* vo)= 0;
    virtual VoObject* parse(const char *data)=0;
};



#endif
