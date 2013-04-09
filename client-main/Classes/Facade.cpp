#include "Facade.h"
#include "core/Client.h"
#include "core/CommandsRegister.h"
#include "commands/CommandSystem.h"
#include "commands/CommandCareer.h"

bool Facade::isMock=true;
char* Facade::ip="192.168.1.57";
int Facade::port=61114;
char* Facade::version="v1.0.0";


int Facade::send(int head){
    if(Facade::isMock){
        CommandsRegister* commands=CommandsRegister::GetInstance();
        Command* c=commands->get(head);
        c->success(NULL);
        return 1;
    }else{
        Client* client=Client::GetInstance();
        return client->send(head);
    }
    
};
int Facade::send(int head,char* p1){
    Client* client=Client::GetInstance();
    return client->send(head,p1);

};
int Facade::send(int head,char* p1,char* p2){
    Client* client=Client::GetInstance();
    return client->send(head,p1,p2);

};
int Facade::send(int head,char* p1,char* p2,char* p3){
    Client* client=Client::GetInstance();
    return client->send(head,p1,p2,p3);

};
int Facade::send(int head,char* p1,char* p2,char* p3,char* p4){
    Client* client=Client::GetInstance();
    return client->send(head,p1,p2,p3,p4);

};
int Facade::send(int head,char* p1,char* p2,char* p3,char* p4,char* p5){
    Client* client=Client::GetInstance();
    return client->send(head,p1,p2,p3,p4,p5);

};

Command* Facade::get(int head){
    CommandsRegister* commands=CommandsRegister::GetInstance();
    return commands->get(head);
}

void Facade::registerCommands(){
    CommandsRegister* commands=CommandsRegister::GetInstance();
    commands->put(CommandCheck::Head,new CommandCheck());
    commands->put(CommandServer::Head,new CommandServer());
    commands->put(CommandCareer::Head,new CommandCareer());
        
}

