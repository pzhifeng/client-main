
#include "SmartRes.h"

SmartRes* SmartRes::s_sharedRes = NULL;

SmartRes* SmartRes::sharedRes(void)
{
    if (!s_sharedRes)
    {
        s_sharedRes = new SmartRes();
        s_sharedRes->init();
    }
    return s_sharedRes;
}

bool SmartRes::init(void)
{
    //const CCSize& winSizeInPixels = CCDirector::sharedDirector()->getWinSizeInPixels();
    //setVirtualScreenWidth(winSizeInPixels.width);
	setDesignResolutionSize();
    return true;
}

/************************************************************************/
/* 设置设计分辨率大小                                                                     */
/************************************************************************/
void SmartRes::setDesignResolutionSize()
{
    // 木有找到 2.0 里面怎么获取设备方向。。所以假定是横向了
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	//得到屏幕的真实分辨率大小
	CCSize frameSize= pEGLView->getFrameSize();
	CCLOG("winSize width: %0.2f, winSize height: %0.2f",frameSize.width, frameSize.height);

    m_scale = frameSize.width / resSize.width;
    designSize.width = resSize.width;
    designSize.height = frameSize.height / m_scale;
	//设置设计分辨率大小   
    pEGLView->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
	//资源背景的高度适应设计分辨率
	pDirector->setContentScaleFactor(resSize.height/designSize.height);

    CCLOG("Virtual width: %0.2f, Virtual height: %0.2f, scale: %0.2f",designSize.width, designSize.height, m_scale);

    CCSize winSize = pDirector->getWinSize();
    m_center.x = winSize.width / 2;
    m_center.y = winSize.height / 2;
    m_left = 0;
    m_right = designSize.width - 1;
	m_top = designSize.height - 1;
	m_bottom = 0;
    CCLOG("center x: %0.2f, center y: %0.2f", m_center.x, m_center.y);
    CCLOG("top: %0.2f, right: %0.2f, bottom: %0.2f, left: %0.2f", m_top, m_right, m_bottom, m_left);
}


void SmartRes::release()
{
	if (s_sharedRes)
	{
		delete s_sharedRes;
		s_sharedRes=NULL;
	}
}