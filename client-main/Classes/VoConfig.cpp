#include "VoConfig.h"
#include "cocos2d.h"

extern std::vector<std::string> split(const std::string s, char delim);

map<int,VoEmail> ConfigUtil::parseEmail(const char *jsonStr){
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

map<string,VoLang> ConfigUtil::parseLang(const char *langFileName){
	map<string,VoLang> langs;
	string filePath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(langFileName);
	FILE *fp;
	char *TmpBuf;
	int maxLen=100;
	TmpBuf = (char*)malloc(maxLen);
	fp = fopen( filePath.c_str(),"rt");
	while((fgets(TmpBuf, maxLen,fp))!= NULL )
	{
		CCLOG("TmpBuf===%s",TmpBuf);
		//Ê×Ò³=Ê×Ò³
		vector<string> titleList=split(TmpBuf,'=');
		VoLang lang;
		lang.value=titleList[1];
		langs[titleList[0]]=lang;
	}
	free(TmpBuf);
	fclose( fp );
	return langs;
}