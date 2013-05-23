#ifndef __SCENE_FIGHT_H_
#define __SCENE_FIGHT_H_

#include "cocos2d.h"
#include "../core/LayerUI.h"
#include "../domain/Ball.h"

//#define _distanceOfBall 34
#define _indexDistanceOfBall 8
#define _color CCRANDOM_0_1()*4+1

//开战请求，获取NPC数据
struct VoFight:VoObject {
    int * id;
    int * npc;
};

//战斗结束，获取战�?
struct VoReport:VoObject {
    int * id;
    int * score;
    int * coin;
    int * exp;
    int * propertyId;
};

class SceneFight :public LayerUI
{
public:
	CCArray  * m_balls;
	Ball * m_pushBall;
	CCPointArray  * m_wayPoint;
	CCAction *m_pushBallAction;
public:
	static LayerUI* scene(VoFight* vo);

	VoFight* vo;

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
	bool IsLineSegmentCross(CCPoint pFirst1, CCPoint pFirst2, CCPoint pSecond1, CCPoint pSecond2);//º∆À„«Ú «∑Ò≈ˆ◊�?
	CCPoint GetCrossPoint(CCPoint p1, CCPoint p2, CCPoint q1, CCPoint q2);//≈ˆ◊≤µƒΩπµ�?
};
#endif

