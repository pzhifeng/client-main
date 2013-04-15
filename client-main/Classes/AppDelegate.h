#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"
#include "cocos2d.h"


class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();


    virtual bool applicationDidFinishLaunching();


    virtual void applicationDidEnterBackground();


    virtual void applicationWillEnterForeground();

private:
	void initGame(cocos2d::CCScene *pScene);
    void excuteCommand();
};

#endif 

