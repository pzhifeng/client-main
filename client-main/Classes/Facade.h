#ifndef __client_main__CommandsInit__
#define __client_main__CommandsInit__

#include "core/Command.h"
#include "core/VoObject.h"
#include "VoConfig.h"

using namespace std;

class Facade
{
public:
    static char* version;
    static VoEmail Email;
    static VoBall Ball;
public:
    static int mockSend(int head);
    
    static int send(int head);
    static int send(int head);
    static int send(int head,char* p1);
    static int send(int head,char* p1,char* p2);
    static int send(int head,char* p1,char* p2,char* p3);
    static int send(int head,char* p1,char* p2,char* p3,char* p4);
    static int send(int head,char* p1,char* p2,char* p3,char* p4,char* p5);

    
    static Command* get(int head);
    
    static void registerCommands();

};

#endif 
