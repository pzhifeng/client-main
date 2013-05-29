#ifndef __client_main__Facade__
#define __client_main__Facade__

#include "core/Command.h"
#include "VoConfig.h"
#include "SceneMain.h"

using namespace std;

#define lgs(s)     Facade::langs(s)

class Facade
{
public:
    static bool IsMock;
    static char* Ip;
    static int Port;
    static char* Version;
    
    static map<int,VoServer*> Servers;
	static map<int,VoEmail> Emails;
    static map<int,VoBall> Balls;
	static map<string,VoLang> Langs;

public:
    static int send(int head);
    static int send(int head,char* p1);
    static int send(int head,char* p1,char* p2);
    static int send(int head,char* p1,char* p2,char* p3);
    static int send(int head,char* p1,char* p2,char* p3,char* p4);
    static int send(int head,char* p1,char* p2,char* p3,char* p4,char* p5);

    static const char* langs(const char* key);
    
    static Command* get(int head);
    
    static void registerCommands();

	static void release();
};

#endif 
