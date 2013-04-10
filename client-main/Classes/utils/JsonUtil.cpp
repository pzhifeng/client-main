#include "JsonUtil.h"
#include "utils/jsoncpp/include/json.h"

JsonUtil::JsonUtil(void)
{
}


JsonUtil::~JsonUtil(void)
{
}

map<int,VoEmail> JsonUtil::parseEmail(const char *jsonStr){
	//jsonStr="{\"v\":\"1.0\",\"email\":{\"1\":{\"content\":\"123\",\"id\":1},\"2\":{\"content\":\"456\",\"id\":2}}}";
	map<int,VoEmail> emails;
	Json::Reader reader;
	Json::Value value;
	if(reader.parse(jsonStr, value)){
		Json::Value jsonEmails=value["email"];
		Json::Value::Members mem = jsonEmails.getMemberNames();  
		for (auto iter = mem.begin(); iter != mem.end(); iter++)  
		{   
			if (jsonEmails[*iter].type() == Json::objectValue)  
			{  
				const std::string &key = *iter; 
				VoEmail email;
				email.id=jsonEmails[key]["id"].asInt();
				email.content=jsonEmails[key]["content"].asString();
				emails[atoi(key.c_str())]=email;
			}  
		}  
	}
	return emails;
}