#ifndef __SCENE_FIGHT_H_
#define __SCENE_FIGHT_H_

#include "cocos2d.h"
#include "../VoObject.h"
#include "../core/LayerUI.h"
#include "../domain/Ball.h"

#define INDEX_DISTANCE 10
#define _color CCRANDOM_0_1()*4+1

class SceneFight :public LayerUI
{
public:
	CCArray  * m_balls;
	Ball * m_pushBall;
	CCPointArray  * m_wayPoint;
	CCAction *m_pushBallAction;
public:
	static LayerUI* scene(VoHome* vo);

	VoHome* vo;

	void initLayer();

	void back(CCObject* pSender);

	CREATE_FUNC(SceneFight);


	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	Ball * getBall();
	void addPushBall();//��̨���ӷ�����
	void pushBall(float interval,CCPoint pos);//����
	void pushBallFinish();//�������
	void ballExplosion(CCPoint pt);//��ը��Ч
	bool ballBack(int hitIndex);//�����
	void removeBallFromUI(int removeStart,int removeEnd);//�ӽ���ɾ����
	void removeBallFromArray(int removeStart,int removeEnd);//��������ɾ��
	bool isMoving();//�Ƿ����������ƶ�

	void initWayPoint();//��ʼ����ͼ
	void checkHitTask(float dt);//���ײ����ʱ��
	void insertBallFinish();//�����򵽹�����
	void createBallTask(float dt);//������ʱ��
	void removeBallTask(float dt);//�Ƴ���ʱ��
	int isHit();//���ײ��
	const char * getColor(int colorType);
};
#endif

