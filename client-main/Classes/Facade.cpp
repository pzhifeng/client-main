#include "Facade.h"
#include "VoObject.h"
#include "core/LayerUI.h"
#include "core/Client.h"
#include "core/CommandsRegister.h"
#include "commands/CommandSystem.h"
#include "commands/CommandCareer.h"

bool Facade::IsMock=false;
char* Facade::Ip="192.168.1.78";
int Facade::Port=61114;
char* Facade::Version="1.0";

map<int,VoEmail> Facade::Emails;
map<string,VoLang> Facade::Langs;

int Facade::send(int head){
    if(Facade::IsMock){
        CommandsRegister* commands=CommandsRegister::GetInstance();
        Command* c=commands->get(head);
		VoObject* vo=c->parse(NULL);
		LayerUI* LayerUI=c->success(vo);
        LayerUI->vo=vo;
		LayerUI->refresh();
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

void Facade::release(){
	CommandsRegister* commands=CommandsRegister::GetInstance();
    delete commands;
}

void Facade::registerCommands(){
    CommandsRegister* commands=CommandsRegister::GetInstance();
    commands->put(CommandCheck::Head,new CommandCheck());
    commands->put(CommandServer::Head,new CommandServer());
    commands->put(CommandCareer::Head,new CommandCareer());     
}
