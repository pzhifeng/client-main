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
		for (std::vector<std::string>::iterator iter = mem.begin(); iter != mem.end(); iter++)
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


map<string,VoLang> ConfigUtil::parseLang(const char *folderName,const char *fileName){
	map<string,VoLang> langs;
	string fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fileName);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    string fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(fileName,folderName);
//#else
//    string fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(folderName+"/"+filename);
//#endif
	FILE *fp;
    fp = fopen( fullPath.c_str(),"r");
    if(NULL!=fp){
        char *tmpBuf;
        int maxLen=100;
        tmpBuf = (char*)malloc(maxLen);
        while((fgets(tmpBuf, maxLen,fp))!= NULL )
        {
            CCLOG("%s",tmpBuf);
            // ◊“≥= ◊“≥
            vector<string> titleList=split(tmpBuf,'=');
            VoLang lang;
            lang.value=titleList[1];
            langs[titleList[0]]=lang;
        }
        free(tmpBuf);
        fclose( fp );
    }
	return langs;
}