#include "FileUtil.h"
#include "cocos2d.h"
using namespace cocos2d;

FileUtil::FileUtil(void)
{
}


FileUtil::~FileUtil(void)
{
}
string FileUtil::read(const char *fileName){
	string filePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fileName);
	FILE *fp =fopen(filePath.c_str(),"r");//根据路径打开文件

	char *pchBuf = NULL;//将要取得的字符串
	int  nLen = 0;//将要取得的字符串长度
	fseek(fp, 0,SEEK_END); //文件指针移到文件尾
	nLen =ftell(fp);  //得到当前指针位置,即是文件的长度
	rewind(fp);    //文件指针恢复到文件头位置

	//动态申请空间,为保存字符串结尾标志\0, 多申请一个字符的空间
	pchBuf = (char*)malloc(sizeof(char)*nLen+1);
	if(!pchBuf)
	{
		fclose(fp);  //关闭文件
		free(pchBuf); //释放空间
		return NULL;
	}

	//读取文件内容//读取的长度和源文件长度有可能有出入，这里自动调整 nLen
	nLen =fread(pchBuf, sizeof(char), nLen, fp);

	pchBuf[nLen] ='\0'; //添加字符串结尾标志

	string detailStr = pchBuf;
	fclose(fp);  //关闭文件
	free(pchBuf); //释放空间
	return detailStr;
}

void FileUtil::write(const char *fileName,const char *buff){
	//要保存的内容
	//string jsonStr = "{\"v\":\"1.0\",\"ball\":{\"1\":{\"name\":null,\"desc\":\"红色，触发普通攻击。基础消除1段攻击，每多1个球的消除，多一段攻击。\",\"images\":null,\"effect\":null,\"remove\":1,\"more\":\"1\",\"id\":1},\"2\":{\"name\":null,\"desc\":\"黄色，增加护盾值。基础消除增加20%，每多一个球的消除，多增加20%。\",\"images\":null,\"effect\":null,\"remove\":0,\"more\":\"0.2\",\"id\":2},\"3\":{\"name\":null,\"desc\":\"蓝色，增加魔法值。基础消除增加10点魔法，每多一个球的消除，多增加10点。\",\"images\":null,\"effect\":null,\"remove\":10,\"more\":\"10\",\"id\":3},\"4\":{\"name\":null,\"desc\":\"紫色，增加能量值。基础消除增加10点能量，每多一个球的消除，多增加10点。\",\"images\":null,\"effect\":null,\"remove\":10,\"more\":\"10\",\"id\":4},\"5\":{\"name\":null,\"desc\":\"黑色。无效果\",\"images\":null,\"effect\":null,\"remove\":0,\"more\":\"0\",\"id\":5},\"6\":{\"name\":null,\"desc\":\"万能球，变成最先碰到的球的颜色。\",\"images\":null,\"effect\":null,\"remove\":0,\"more\":\"0\",\"id\":6},\"7\":{\"name\":null,\"desc\":\"透明球。将碰到的球推离轨道，本身不消除。\",\"images\":null,\"effect\":null,\"remove\":0,\"more\":\"0\",\"id\":7}}}";
	//取得文件储存的位置
	string filePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fileName);
	//打开文件
	FILE *fp =fopen(filePath.c_str(),"w");
	//写入字符串
	fputs(buff, fp);
	//关闭文件
	fclose(fp);
}