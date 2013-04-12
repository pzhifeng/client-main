#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include "HttpRequest.h"
#include "HttpClient.h"

using namespace cocos2d;
using namespace extension;
using namespace std;

class HttpRequest:public CCObject
{
public:
	string m_responseData;
	bool m_isCompleted;
public:
	HttpRequest(void);
	~HttpRequest(void);

public:
	void doGet();
	void onHttpRequestCompleted(CCNode *sender,void *data);
	//void doResponse(CommandCheck *pTarget,char *data);
};
#endif 

