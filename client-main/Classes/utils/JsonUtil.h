#ifndef  _JSON_UTIL_H_
#define  _JSON_UTIL_H_

#include <string>
#include "utils/jsoncpp/include/json.h"
#include "VoConfig.h"

using namespace std;
class JsonUtil
{
public:
	JsonUtil(void);
	~JsonUtil(void);

public:
	static map<int,VoEmail> parseEmail(const char *jsonStr);
};
#endif
