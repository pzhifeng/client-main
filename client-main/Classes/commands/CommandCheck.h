#ifndef __client_main__CommandCheck__
#define __client_main__CommandCheck__

#include "../core/Command.h"
#include "../core/VoObject.h"
class CommandCheck :public Command
{
public:
    static int Head;
public:
	CommandCheck(void);
	~CommandCheck(void);
    
    void success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};

#endif 
