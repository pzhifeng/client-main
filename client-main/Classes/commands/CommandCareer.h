#ifndef __client_main__CommandCareer__
#define __client_main__CommandCareer__

#include "../core/Command.h"
#include "../core/VoObject.h"
class CommandCareer :public Command
{
public:
    static std::string Head;
public:
	CommandCareer(void);
	~CommandCareer(void);
    
    void success(VoObject* vo);
    void fail(int code,VoObject* vo);
    VoObject* parse(const char *data);
};

#endif 
