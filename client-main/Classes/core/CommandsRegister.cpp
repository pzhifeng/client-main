#include "CommandsRegister.h"

CommandsRegister* CommandsRegister::instance=NULL;

CommandsRegister::CommandsRegister(void){
    
}

CommandsRegister::~CommandsRegister(void){
	for (map<int,Command *>::iterator it=commands.begin(); it!=commands.end();)
	{
		int key=it->first;
		delete commands[key];
		commands.erase(it++);
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
    Command* tmp=commands[head];
<<<<<<< HEAD
	/*
    if(NULL!=tmp){
        CCAssert(tmp, "Repeat Command Head:"+head);
    }
	*/
=======
 
    CCLOG("%s,%d","Register Command Head:",head);
    CCAssert(NULL==tmp, "Repeat Command Head:"+head);

>>>>>>> fa6602ee5579d61b4ecc4122e4c14f0bae754fbd
    commands[head]=c;
}

Command* CommandsRegister::get(int head){
    return commands[head];
}

