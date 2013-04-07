#ifndef __client_main__Client__
#define __client_main__Client__

#include <pthread.h>
#include <vector.h>
#include "cocos2d.h"
#include "../utils/odsocket.h"


class Client
{
private:
    Client(void);
	~Client(void);
    
    static Client *instance;
    
    std::string uid;
    std::string sessionKey;
    
public:
    pthread_mutex_t mutex;
    vector<std::string> query;
    ODSocket odSocket;
    
    static Client* GetInstance();
    
	bool connet(char* ip,int port);
    void setConfig(std::string _uid,std::string _sessionKey);
    
    int send(const char *head);
    int send(const char *head,char* p1);
    int send(const char *head,char* p1,char* p2);
    int send(const char *head,char* p1,char* p2,char* p3);
    int send(const char *head,char* p1,char* p2,char* p3,char* p4);
    int send(const char *head,char* p1,char* p2,char* p3,char* p4,char* p5);

    void doCommand();
};


#endif