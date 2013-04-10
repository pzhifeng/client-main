#include "CommandsRegister.h"

CommandsRegister* CommandsRegister::instance=NULL;

CommandsRegister::CommandsRegister(void){
    
}

CommandsRegister::~CommandsRegister(void){
	// Õ∑≈command
	for (map<int,Command *>::iterator i=commands.begin(); i!=commands.end(); /*i++*/)
	{
		int key=i->first;
		delete commands[key];
		commands.erase(i++);
	}
    this->commands.~map();
	if(instance!=NULL){
		delete instance;
		instance=NULL;
	}	
}

CommandsRegister* CommandsRegister::GetInstance(){
    if(instance==NULL){
        instance=new CommandsRegister();
    }
    return instance;
}

void CommandsRegister::put(int head,Command* c){
    commands[head]=c;
}

Command* CommandsRegister::get(int head){
    return commands[head];
}

