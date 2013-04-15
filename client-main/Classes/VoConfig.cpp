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
		//Ê×Ò³=Ê×Ò³:|x|y
		vector<string> langList=split(TmpBuf,':');
		vector<string> titleList=split(langList[0].c_str(),'=');
		vector<string> posList=split(langList[1].c_str(),'|');
		CCLOG("titleList===0===%s",titleList[0].c_str());
		CCLOG("titleList===1===%s",titleList[1].c_str());
		CCLOG("posList===x:%s===y:%s",posList[1].c_str(),posList[2].c_str());

		VoLang lang;
		lang.value=titleList[1];
		lang.x=(atoi(posList[1].c_str()));
		lang.y=(atoi(posList[2].c_str()));
		langs[titleList[0]]=lang;
	}
	free(TmpBuf);
	fclose( fp );
	return langs;
}