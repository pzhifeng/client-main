#ifndef __client_main__CommandServer__
#define __client_main__CommandServer__

#include "../core/Command.h"

class CommandServer :public Command
{
public:
    static int Head;
public:
	CommandServer(void);
	~CommandServer(void);
    
    void success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};

#endif