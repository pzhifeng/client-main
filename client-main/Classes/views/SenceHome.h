//
//  SenceHome.h
//  client-main
//
//  Created by PAN ZHIFENG on 13-4-6.
//
//

#ifndef __client_main__SenceHome__
#define __client_main__SenceHome__

#include "cocos2d.h"

class SceneHome : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void back(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(SceneHome);
};

#endif /* defined(__client_main__SenceHome__) */
