#include "Client.h"
#include "../utils/md5.h"
#include "Command.h"
#include "CommandsRegister.h"
#include "../utils/jsoncpp/include/json.h"

#define SOH  1
#define STX  2
#define ETX  3
#define EOT  4
#define ENQ  5
#define TAB  9
#define BLOCK_SIZE 1024

Client* Client::instance=NULL;


Client::Client(void){
    
};

Client::~Client(void){
    odSocket.Close();
	odSocket.Clean();
	pthread_mutex_destroy(&mutex);
	query.clear();
};

Client* Client::GetInstance(){
    if(instance==NULL){
        instance=new Client();
    }
    return instance;
}

void * revice(void* arg){
    Client *_this=(Client*)arg;
	char buff[BLOCK_SIZE];
	char joinBuff[2*BLOCK_SIZE];
	string msg="";
	while (true)
	{
		memset(buff,0,BLOCK_SIZE);
		memset(joinBuff,0,2*BLOCK_SIZE);
        
		int msgLen=strlen(msg.c_str());
		memcpy(joinBuff,msg.c_str(),msgLen);
		msg="";
        
        int ret=_this->odSocket.Recv(buff,BLOCK_SIZE,0);
		if(ret<=0)
			break;
        
		memcpy(joinBuff+msgLen,buff,ret);
		for(int i=0;i<(msgLen+ret);i++){
			if(joinBuff[i]==0x0005){
				pthread_mutex_lock(&_this->mutex);
                
                CCLOG("RECIVE|%s",msg.c_str());
                
				_this->query.push_back(msg);
				msg="";
				pthread_mutex_unlock(&_this->mutex);
				continue;
			}
			msg.push_back(joinBuff[i]);
		}
        
	}
	return ((void*)NULL);
}

bool Client::connet(char* ip,int port){
    odSocket.Init();
	odSocket.Create(AF_INET,SOCK_STREAM,0);
    
	pthread_mutex_init(&mutex,NULL);
    
    bool b= odSocket.Connect(ip,port);
    
    if(b){
        pthread_t tid;
        pthread_create(&tid, NULL,revice, this);
        pthread_detach(tid);
    }
    
    CCLOG("START|connect to %s:%d r:%d",ip,port,b);
    
    return b;
};

void Client::setConfig(std::string _uid,std::string _sessionKey){
    this->uid=_uid;
    this->sessionKey=_sessionKey;
}


int Client::send(const char *head,char* p1,char* p2,char* p3,char* p4,char* p5){
    
	std::string key="5dcd73d391c90e8769618d42a916ea1b";
	
    std::string msg;
	std::string tmp;
    
	msg.append(head);
	msg.push_back(SOH);
	msg.append(Client::uid);
	msg.push_back(TAB);
	msg.append(Client::sessionKey);
	msg.push_back(STX);
    if(NULL!=p1){
        msg.push_back(*p1);
        tmp.push_back(*p1);
    }
    if(NULL!=p2){
        msg.push_back(TAB);
        msg.push_back(*p2);
        tmp.push_back(*p1);
    }
    if(NULL!=p3){
        msg.push_back(TAB);
        msg.push_back(*p3);
        tmp.push_back(*p1);
    }
    if(NULL!=p4){
        msg.push_back(TAB);
        msg.push_back(*p4);
        tmp.push_back(*p1);
    }
    if(NULL!=p5){
        msg.push_back(TAB);
        msg.push_back(*p5);
        tmp.push_back(*p1);
    }
	
	msg.push_back(ETX);
    
	std::string chekKey;
	chekKey.append(head);
	chekKey.append(uid);
	chekKey.append(tmp);
	chekKey.append(key);
	msg.append(MD5(chekKey).toString());
	msg.push_back(EOT);
    
    CCLOG("SEND|%s",msg.c_str());
    
	return odSocket.Send(msg.c_str(),strlen(msg.c_str())+2,1);
}

int Client::send(const char *head){
    return Client::send(head,NULL,NULL,NULL,NULL,NULL);
};

int Client::send(const char *head,char* p1){
    return Client::send(head,p1,NULL,NULL,NULL,NULL);
};

int Client::send(const char *head,char* p1,char* p2){
    return Client::send(head,p1,p2,NULL,NULL,NULL);
};

int Client::send(const char *head,char* p1,char* p2,char* p3){
    return Client::send(head,p1,p2,p3,NULL,NULL);
};

int Client::send(const char *head,char* p1,char* p2,char* p3,char* p4){
    return Client::send(head,p1,p2,p3,p4,NULL);
};

void Client::doCommand(){
	pthread_mutex_lock(&mutex);

	if(query.size()>0){
		Json::Reader reader;
		Json::Value value;

        string msg=query.front();

        if(reader.parse(msg, value)){
            //int uid=value["u"].asInt();
            int code=value["r"].asInt();
            std::string head=value["h"].asString();
            CommandsRegister* commands=CommandsRegister::GetInstance();
            Command *command=commands->get(head);
            if(command!=NULL){
                std::string m=value["m"].toStyledString();
                VoObject* vo=command->parse(m.c_str());
                if(code==0){
                    command->success(vo);
                }else{
                    command->fail(code,vo);
                }
                delete vo;
            }
        }
        query.erase(query.begin());
	}
	pthread_mutex_unlock(&mutex);
}