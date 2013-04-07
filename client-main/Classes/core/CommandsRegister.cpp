#include "CommandsRegister.h"

CommandsRegister* CommandsRegister::instance=NULL;

CommandsRegister::CommandsRegister(void){
    
}

CommandsRegister::~CommandsRegister(void){
    this->commands.~map();
}

CommandsRegister* CommandsRegister::GetInstance(){
    if(instance==NULL){
        instance=new CommandsRegister();
    }
    return instance;
}

void CommandsRegister::put(std::string head,Command* c){
    commands[head]=c;
}

Command* CommandsRegister::get(std::string head){
    return commands[head];
}

