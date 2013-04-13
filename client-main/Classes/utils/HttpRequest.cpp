#include "HttpRequest.h"
#pragma comment(lib, "libcurl_imp")
#pragma comment(lib, "libExtensions")
using namespace std;
HttpRequest::HttpRequest(void)
{
	m_responseData="";
	m_isCompleted=false;
}


HttpRequest::~HttpRequest(void)
{
}
void HttpRequest::doGet()
{
	m_isCompleted=false;
	m_responseData="";
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl("www.baidu.com");
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this, callfuncND_selector(HttpRequest::onHttpRequestCompleted));
	CCHttpClient::getInstance()->send(request); 
	request->release();
}

void HttpRequest::onHttpRequestCompleted(CCNode *sender,void *data)  
{  
	m_isCompleted=true;
	CCHttpResponse *response = (CCHttpResponse*)data;  
	if (!response)  
	{  
		return;  
	}  
	int s=response->getHttpRequest()->getRequestType();  
	CCLog("request type %d",s);  


	if (0 != strlen(response->getHttpRequest()->getTag()))   
	{  
		CCLog("%s ------>oked", response->getHttpRequest()->getTag());  
	}  

	int statusCode = response->getResponseCode();  
	CCLog("response code: %d", statusCode);  


	char statusString[64] = {};  
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());  
	CCLog(statusString);  

	if (!response->isSucceed())   
	{  
		CCLog("response failed");  
		CCLog("error buffer: %s", response->getErrorBuffer());  
		return;  
	}  

	std::vector<char> *buffer = response->getResponseData(); 
	printf("Http Test, dump data: ");  
	for (unsigned int i = 0; i < buffer->size(); i++)  
	{  
		//CCLog("%c", (*buffer)[i]);//这里打印从服务器返回的数据  
		m_responseData.push_back((*buffer)[i]);
	}  
	//CCLog("m_responseData:%s",m_responseData.c_str());
	printf("\n");  

} 
/*
void HttpRequest::doResponse(CommandCheck *pTarget,char *data)
{
	pTarget->doResponse(data);
}*/