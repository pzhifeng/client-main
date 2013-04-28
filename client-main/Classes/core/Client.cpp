#include "Client.h"
#include "../utils/md5.h"
#include "Command.h"
#include "CommandsRegister.h"
#include "../utils/jsoncpp/include/json.h"
#include "Facade.h"
#include "cocos2d.h"

#define SOH  1
#define STX  2
#define ETX  3
#define EOT  4
#define ENQ  5
#define TAB  9
#define BLOCK_SIZE 4096

Client* Client::instance=NULL;
extern std::vector<std::string> split(const std::string s, char delim);


Client::Client(void){
    
};

Client::~Client(void){
    odSocket.Close();
	odSocket.Clean();
    queue.clear();
	if(instance!=NULL){
		delete instance;
		instance=NULL;
	}
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
	string msg="";
	int continueErrorTimes=0;
	while (true)
	{
		memset(buff,0,BLOCK_SIZE);
        int ret=_this->odSocket.Recv(buff,BLOCK_SIZE,0);
		CCLOG("recv===ret===%d",ret);
		if(ret<=0)
		{
			continueErrorTimes++;
			if(continueErrorTimes>15)
			{
				_this->odSocket.Close();
				_this->odSocket.Clean();

				_this->odSocket.Init();
				_this->odSocket.Create(AF_INET,SOCK_STREAM,0);
				bool b= _this->odSocket.Connect(Facade::Ip,Facade::Port);
				CCLOG("reset conn===%d",b);
				if(b)
					continueErrorTimes=0;
			}
			continue;
		}
			
		msg.append(buff);
		if(buff[ret-1]!=0x0005)
			continue;
		vector<string> tmp=split(msg,0x0005);
		
		for(int i=0;i<tmp.size();i++){
            _this->queue.push_back(tmp[i]);
		}
        CCLOG("RECIVE|%d|%d|%s",_this->queue.size(),tmp.size(),msg.c_str());
		tmp.clear();
		msg.clear();
	}
	return ((void*)NULL);
}


void Client::excuteCommand(){
    if(queue.size()>0){
        string msg=queue.front();
        
        Json::Reader reader;
        Json::Value value;
        if(reader.parse(msg, value)){
            //long uid=value["u"].asUInt();
            int code=value["r"].asInt();
            int head=value["h"].asInt();
            CommandsRegister* commands=CommandsRegister::GetInstance();
            Command *command=commands->get(head);
            if(command!=NULL){
                std::string m=value["m"].toStyledString();
                if("null\n"==m){
                    m="";
                }
                VoObject* vo=command->parse(m.c_str());
                if(code==0){
                    LayerUI* LayerUI=command->success(vo);
                    LayerUI->refresh();
                }else{
                    command->fail(code,vo);
                    CCLOG("FAIL|%d  %s",code,m.c_str());
                }
                delete vo;
            }
        }
        
        queue.erase(queue.begin());
    }
    
}


bool Client::connet(char* ip,int port){
    odSocket.Init();
	odSocket.Create(AF_INET,SOCK_STREAM,0);
    
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


int Client::send(int head,char* p1,char* p2,char* p3,char* p4,char* p5){
    
	std::string key="5dcd73d391c90e8769618d42a916ea1b";
	
    std::string msg;
	std::string tmp;
    
    stringstream stream;
    stream<<head;
    std::string strHead=stream.str();
	msg.append(strHead);
	msg.push_back(SOH);
	msg.append(Client::uid);
	msg.push_back(TAB);
	msg.append(Client::sessionKey);
	msg.push_back(STX);
    if(NULL!=p1){
        msg.append(p1);
        tmp.append(p1);
    }
    if(NULL!=p2){
        msg.push_back(TAB);
        msg.append(p2);
        tmp.append(p2);
    }
    if(NULL!=p3){
        msg.push_back(TAB);
        msg.append(p3);
        tmp.append(p3);
    }
    if(NULL!=p4){
        msg.push_back(TAB);
        msg.append(p4);
        tmp.append(p4);
    }
    if(NULL!=p5){
        msg.push_back(TAB);
        msg.append(p5);
        tmp.append(p5);
    }
	
	msg.push_back(ETX);
    
	std::string chekKey;
    
	chekKey.append(strHead);
	chekKey.append(uid);
	chekKey.append(tmp);
	chekKey.append(key);
	msg.append(MD5(chekKey).toString());
	msg.push_back(EOT);
    
    CCLOG("SEND|%s",msg.c_str());
    
	return odSocket.Send(msg.c_str(),strlen(msg.c_str())+2,1);
}

int Client::send(int head){
    return Client::send(head,NULL,NULL,NULL,NULL,NULL);
};

int Client::send(int head,char* p1){
    return Client::send(head,p1,NULL,NULL,NULL,NULL);
};

int Client::send(int head,char* p1,char* p2){
    return Client::send(head,p1,p2,NULL,NULL,NULL);
};

int Client::send(int head,char* p1,char* p2,char* p3){
    return Client::send(head,p1,p2,p3,NULL,NULL);
};

int Client::send(int head,char* p1,char* p2,char* p3,char* p4){
    return Client::send(head,p1,p2,p3,p4,NULL);
};
