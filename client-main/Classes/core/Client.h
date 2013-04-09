#ifndef __client_main__Client__
#define __client_main__Client__

#include <pthread.h>
#include "cocos2d.h"
#include "../utils/odsocket.h"

using namespace std;

class Client
{
private:
    Client(void);
	~Client(void);
    
    static Client *instance;
    
    std::string uid;
    std::string sessionKey;
    
public:
    ODSocket odSocket;
    
    static Client* GetInstance();
    
	bool connet(char* ip,int port);
    void setConfig(std::string _uid,std::string _sessionKey);
    
    int send(int head);
    int send(int head,char* p1);
    int send(int head,char* p1,char* p2);
    int send(int head,char* p1,char* p2,char* p3);
    int send(int head,char* p1,char* p2,char* p3,char* p4);
    int send(int head,char* p1,char* p2,char* p3,char* p4,char* p5);

	std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
};


#endif