#include "Facade.h"
#include "core/Client.h"
#include "core/CommandsRegister.h"
#include "commands/CommandServer.h"
#include "commands/CommandCareer.h"

char* Facade::version="v1.0.0";

int Facade::mockSend(int head){
    CommandsRegister* commands=CommandsRegister::GetInstance();
    Command* c=commands->get(head);
    c->success(NULL);
}

int Facade::send(int head){
    Client* client=Client::GetInstance();
    return client->send(head);
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
    commands->put(CommandServer::Head,new CommandServer());
    commands->put(CommandCareer::Head,new CommandCareer());
        
}

