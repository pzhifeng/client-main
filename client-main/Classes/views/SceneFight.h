#ifndef __SCENE_FIGHT_H_
#define __SCENE_FIGHT_H_

#include "cocos2d.h"
#include "../VoObject.h"
#include "../core/LayerUI.h"
#include "../domain/Ball.h"

//#define _distanceOfBall 34
#define _indexDistanceOfBall 8
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
	void explosionBall(CCPoint pt);//��ը��Ч
	bool backBall(int hitIndex);//����
	bool backBallMove(int start,int end);//����ʱ�ƶ�
	void goAll();//�ƶ�����
	void stopAll();//ֹͣ����
	void removeBallFromUI(int removeStart,int removeEnd);//�ӽ���ɾ����
	void removeBallFromArray(int removeStart,int removeEnd);//��������ɾ��
	bool isMoving();//�ж��Ƿ����������ƶ�

	void initWayPoint();//��ʼ����ͼ
	void insertBall();//�����򵽹��
	void insertBallFinish();//�����򵽹�����
	void createBallTask(float dt);//������ʱ��
	void removeBallTask(float dt);//�Ƴ���ʱ��

	const char * getColor(int colorType);
	bool IsLineSegmentCross(CCPoint pFirst1, CCPoint pFirst2, CCPoint pSecond1, CCPoint pSecond2);//�������Ƿ���ײ
	CCPoint GetCrossPoint(CCPoint p1, CCPoint p2, CCPoint q1, CCPoint q2);//��ײ�Ľ���
};
#endif

