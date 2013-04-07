//
//业务VO对象，每个命令解析成一个与之对应的结构，供前端使用
//

#ifndef client_main_VoObject_h
#define client_main_VoObject_h

#include "Command.h"


struct VoServer:VoObject{
    int id;
    std::string name;
    std::string domain;
    std::string tag;
};


#endif


