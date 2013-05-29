#include "Facade.h"
#include "core/LayerUI.h"
#include "core/Client.h"
#include "core/CommandsRegister.h"
#include "commands/CommandHead.h"
#include "commands/CommandSystem.h"
#include "commands/CommandUser.h"
#include "commands/CommandHome.h"
#include "commands/CommandSkill.h"
#include "commands/CommandFight.h"

bool Facade::IsMock=true;
char* Facade::Ip="192.168.1.78";
int Facade::Port=61114;
char* Facade::Version="1.0";

map<int,VoServer*> Facade::Servers;

map<int,VoEmail> Facade::Emails;
map<string,VoLang> Facade::Langs;

int Facade::send(int head){
    CCLOG("Send|%d",head);
    if(Facade::IsMock){
        CommandsRegister* commands=CommandsRegister::GetInstance();
        Command* c=commands->get(head);		
		LayerUI* layer=c->success(NULL);
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

const char* Facade::langs(const char* key){
    const char* result=Facade::Langs[key].value.c_str();
    if(NULL==result||strlen(result)==0){
        return key;
    }else{
        return result;
    }
}

void Facade::release(){
	CommandsRegister* commands=CommandsRegister::GetInstance();
    delete commands;
}

void Facade::registerCommands(){
    CommandsRegister* commands=CommandsRegister::GetInstance();
    commands->put(CommandHead::Check,new CommandCheck());
    commands->put(CommandHead::Main,new CommandMain());
    commands->put(CommandHead::MainServer,new CommandMainServer());
    commands->put(CommandHead::MainServerSelect,new CommandMainServerSelect());
    
    commands->put(CommandHead::User,new CommandUser());
    commands->put(CommandHead::UserName,new CommandUserName());
    
    commands->put(CommandHead::Home,new CommandHome());
    commands->put(CommandHead::HomeGate,new CommandHomeGate());
    commands->put(CommandHead::HomePve,new CommandHomePve());
    
    commands->put(CommandHead::Skill,new CommandSkill());
}
