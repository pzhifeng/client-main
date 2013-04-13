#ifndef __client_main__CommandsRegister__
#define __client_main__CommandsRegister__

#include "Command.h"
#include <string>
using namespace std;

class CommandsRegister
{
private:
    CommandsRegister(void);
    
    static CommandsRegister* instance;
    map<int,Command*> commands;
    
public:
	~CommandsRegister(void);
    static CommandsRegister* GetInstance();
    Command* get(int head);
    void put(int ,Command*);
};


#endif 