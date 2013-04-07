#ifndef __client_main__CommandsRegister__
#define __client_main__CommandsRegister__

#include "Command.h"

class CommandsRegister
{
private:
    CommandsRegister(void);
    ~CommandsRegister(void);
    
    static CommandsRegister* instance;
    std::map<std::string,Command*> commands;
    
public:
	
    static CommandsRegister* GetInstance();
    Command* get(std::string head);
    void put(std::string ,Command*);
};


#endif 