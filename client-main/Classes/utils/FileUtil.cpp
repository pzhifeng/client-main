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
	FILE *fp =fopen(filePath.c_str(),"r");//����·�����ļ�

	char *pchBuf = NULL;//��Ҫȡ�õ��ַ���
	int  nLen = 0;//��Ҫȡ�õ��ַ�������
	fseek(fp, 0,SEEK_END); //�ļ�ָ���Ƶ��ļ�β
	nLen =ftell(fp);  //�õ���ǰָ��λ��,�����ļ��ĳ���
	rewind(fp);    //�ļ�ָ��ָ����ļ�ͷλ��

	//��̬����ռ�,Ϊ�����ַ�����β��־\0, ������һ���ַ��Ŀռ�
	pchBuf = (char*)malloc(sizeof(char)*nLen+1);
	if(!pchBuf)
	{
		fclose(fp);  //�ر��ļ�
		free(pchBuf); //�ͷſռ�
		return NULL;
	}

	//��ȡ�ļ�����//��ȡ�ĳ��Ⱥ�Դ�ļ������п����г��룬�����Զ����� nLen
	nLen =fread(pchBuf, sizeof(char), nLen, fp);

	pchBuf[nLen] ='\0'; //����ַ�����β��־

	string detailStr = pchBuf;
	fclose(fp);  //�ر��ļ�
	free(pchBuf); //�ͷſռ�
	return detailStr;
}

void FileUtil::write(const char *fileName,const char *buff){
	//Ҫ���������
	//string jsonStr = "{\"v\":\"1.0\",\"ball\":{\"1\":{\"name\":null,\"desc\":\"��ɫ��������ͨ��������������1�ι�����ÿ��1�������������һ�ι�����\",\"images\":null,\"effect\":null,\"remove\":1,\"more\":\"1\",\"id\":1},\"2\":{\"name\":null,\"desc\":\"��ɫ�����ӻ���ֵ��������������20%��ÿ��һ�����������������20%��\",\"images\":null,\"effect\":null,\"remove\":0,\"more\":\"0.2\",\"id\":2},\"3\":{\"name\":null,\"desc\":\"��ɫ������ħ��ֵ��������������10��ħ����ÿ��һ�����������������10�㡣\",\"images\":null,\"effect\":null,\"remove\":10,\"more\":\"10\",\"id\":3},\"4\":{\"name\":null,\"desc\":\"��ɫ����������ֵ��������������10��������ÿ��һ�����������������10�㡣\",\"images\":null,\"effect\":null,\"remove\":10,\"more\":\"10\",\"id\":4},\"5\":{\"name\":null,\"desc\":\"��ɫ����Ч��\",\"images\":null,\"effect\":null,\"remove\":0,\"more\":\"0\",\"id\":5},\"6\":{\"name\":null,\"desc\":\"�����򣬱�����������������ɫ��\",\"images\":null,\"effect\":null,\"remove\":0,\"more\":\"0\",\"id\":6},\"7\":{\"name\":null,\"desc\":\"͸���򡣽���������������������������\",\"images\":null,\"effect\":null,\"remove\":0,\"more\":\"0\",\"id\":7}}}";
	//ȡ���ļ������λ��
	string filePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fileName);
	//���ļ�
	FILE *fp =fopen(filePath.c_str(),"w");
	//д���ַ���
	fputs(buff, fp);
	//�ر��ļ�
	fclose(fp);
}