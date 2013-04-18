
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
/* ������Ʒֱ��ʴ�С                                                                     */
/************************************************************************/
void SmartRes::setDesignResolutionSize()
{
    // ľ���ҵ� 2.0 ������ô��ȡ�豸���򡣡����Լٶ��Ǻ�����
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	//�õ���Ļ����ʵ�ֱ��ʴ�С
	CCSize frameSize= pEGLView->getFrameSize();
	CCLOG("winSize width: %0.2f, winSize height: %0.2f",frameSize.width, frameSize.height);

    m_scale = frameSize.width / resSize.width;
    designSize.width = resSize.width;
    designSize.height = frameSize.height / m_scale;
	//������Ʒֱ��ʴ�С
	//kResolutionNoBorder��������Ļ�Ĳ��ֻᱻ�ü�������û�кڱߣ�������Ļ����ͼƬԭʼ������ʾ��ͼƬ�����Ρ�
	//kResolutionShowAll��������Ϸ�����ǿɼ��ģ��ᰴԭʼ�����������ţ�ͼƬ�����Σ���������ܻ����кڱߣ���������Ļ��
	//kResolutionExactFit��������Ϸ�����ǿɼ��ģ�ͼƬ���ܻ�����������ѹ������������Ļ��ͼƬ����Ρ����Ը����Լ���Ҫ��ѡ��
    pEGLView->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
	//��Դ�����ĸ߶���Ӧ��Ʒֱ���
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