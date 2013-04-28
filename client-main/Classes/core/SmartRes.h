
#ifndef __SMART_RES_H_
#define __SMART_RES_H_


#include "cocos2d.h"

USING_NS_CC;

#define _center     SmartRes::sharedRes()->getCenter()
#define _top        SmartRes::sharedRes()->getTop()
#define _right      SmartRes::sharedRes()->getRight()
#define _bottom     SmartRes::sharedRes()->getBottom()
#define _left       SmartRes::sharedRes()->getLeft()
#define _scale      SmartRes::sharedRes()->getScale()
#define _xy(v)      SmartRes::sharedRes()->xy(v)
//缩放因子，主要给文字标签使用  
#define SCALE_FACTOR  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height / resSize.height)  
//可用的资源尺寸  
static CCSize resSize=cocos2d::CCSizeMake(720.0f, 960.0f);  
//设计方案  
static CCSize designSize = cocos2d::CCSizeMake(320.0f, 480.0f); 


class SmartRes
{
public:
    static SmartRes* sharedRes(void);

    // 设定虚拟屏幕的宽度
    //void setVirtualScreenWidth(float width);
	void setDesignResolutionSize();

	void release();

    float getScale(void) {
        return m_scale;
    }

    const CCPoint getCenter(void) {
        return m_center;
    }

    float getTop(void) {
        return m_top;
    }

    float getRight(void) {
        return m_right;
    }

    float getBottom(void) {
        return m_bottom;
    }

    float getLeft(void) {
        return m_left;
    }

    float xy(float v) {
        return m_scale * v;
    }

private:
    SmartRes(void)
    : m_scale(1.0f)
    , m_top(0)
    , m_right(0)
    , m_bottom(0)
    , m_left(0)
    {
    }
    bool init(void);

    static SmartRes* s_sharedRes;

    CCPoint m_center;
    float m_scale;
    float m_top;
    float m_right;
    float m_bottom;
    float m_left;
};

#endif 