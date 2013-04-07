#ifndef __client_main__CommandsInit__
#define __client_main__CommandsInit__

#include "core/Command.h"
#include "core/VoObject.h"

using namespace std;

class Facade
{
public:
    
    static int send(const char *head);
    static int send(const char *head,char* p1);
    static int send(const char *head,char* p1,char* p2);
    static int send(const char *head,char* p1,char* p2,char* p3);
    static int send(const char *head,char* p1,char* p2,char* p3,char* p4);
    static int send(const char *head,char* p1,char* p2,char* p3,char* p4,char* p5);

    
    static Command* get(std::string head);
    
    static void registerCommands();

};

#endif 
