#ifndef _MY_HTTP_REQUEST_H_
#define _MY_HTTP_REQUEST_H_

#include "cocos2d.h"
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <HttpClient.h>
using namespace cocos2d;
using namespace extension;
using namespace std;

class MyHttpRequest:public CCObject
{
public:
	string m_responseData;
	bool m_isCompleted;
public:
	MyHttpRequest(void);
	~MyHttpRequest(void);

public:
	void doGet();
	void onHttpRequestCompleted(CCNode *sender,void *data);
	//void doResponse(CommandCheck *pTarget,char *data);
};
#endif 

