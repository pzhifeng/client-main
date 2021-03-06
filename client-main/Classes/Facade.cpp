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

VoHead * Facade::header;

map<int,VoServer*> Facade::Servers;

map<int,VoEmail> Facade::Emails;
map<string,VoLang> Facade::Langs;

int sendMock(int head,char* p1,char* p2,char* p3,char* p4,char* p5){
    CCLOG("Send|%d %c %c %c %c %c",head,p1,p2,p3,p4,p5);
    CommandsRegister* commands=CommandsRegister::GetInstance();
    Command* c=commands->get(head);
    LayerUI* layer=c->success(NULL);
    if(layer->menuHome!=NULL){
        layer->freshHeader();
        layer->freshFooter(head);
    }
    return 1;
}

int Facade::send(int head){
    
    if(Facade::IsMock){
        return sendMock(head,NULL,NULL,NULL,NULL,NULL);
    }else{
        Client* client=Client::GetInstance();
        return client->send(head);
    }
};
int Facade::send(int head,char* p1){
    if(Facade::IsMock){
        return sendMock(head,p1,NULL,NULL,NULL,NULL);
    }else{
        Client* client=Client::GetInstance();
        return client->send(head,p1);
    }

};
int Facade::send(int head,char* p1,char* p2){
    if(Facade::IsMock){
        return sendMock(head,p1,p2,NULL,NULL,NULL);
    }else{
        Client* client=Client::GetInstance();
        return client->send(head,p1,p2);
    }
};
int Facade::send(int head,char* p1,char* p2,char* p3){
    if(Facade::IsMock){
        return sendMock(head,p1,p2,p3,NULL,NULL);
    }else{
        Client* client=Client::GetInstance();
        return client->send(head,p1,p2,p3);
    }
};
int Facade::send(int head,char* p1,char* p2,char* p3,char* p4){
    if(Facade::IsMock){
        return sendMock(head,p1,p2,p3,p4,NULL);
    }else{
        Client* client=Client::GetInstance();
        return client->send(head,p1,p2,p3,p4);
    }
};
int Facade::send(int head,char* p1,char* p2,char* p3,char* p4,char* p5){
    if(Facade::IsMock){
        return sendMock(head,p1,p2,p3,p4,p5);
    }else{
        Client* client=Client::GetInstance();
        return client->send(head,p1,p2,p3,p4,p5);
    }
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
