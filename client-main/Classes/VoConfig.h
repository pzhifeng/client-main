//
//系统配置，按模块定义struct结构
//

#ifndef client_main_VoConfig_h
#define client_main_VoConfig_h

#include <string>
#include "utils/jsoncpp/include/json.h"

using namespace std;

struct VoBall{
    int id;
    string name;
    string image;
    string effect;
    int remove;
    int more;
    string desc;
};

struct VoEmail{
    int id;
    string content;
};

class ConfigUtil
{
public:
	static map<int,VoEmail> parseEmail(const char* jsonStr);
};

#endif
