#ifndef __client_main__Facade__
#define __client_main__Facade__

#include "core/Command.h"
#include "core/VoObject.h"
#include "VoConfig.h"

using namespace std;

class Facade
{
public:
    static bool IsMock;
    static char* Ip;
    static int Port;
    static char* Version;
    
	static map<int,VoEmail> Emails;
    static map<int,VoBall> Balls;


public:
    static int send(int head);
    static int send(int head,char* p1);
    static int send(int head,char* p1,char* p2);
    static int send(int head,char* p1,char* p2,char* p3);
    static int send(int head,char* p1,char* p2,char* p3,char* p4);
    static int send(int head,char* p1,char* p2,char* p3,char* p4,char* p5);

    
    static Command* get(int head);
    
    static void registerCommands();

	static void release();
};

#endif 
