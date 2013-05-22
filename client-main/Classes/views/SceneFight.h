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
	void addPushBall();//炮台增加发射球
	void pushBall(float interval,CCPoint pos);//发射
	void pushBallFinish();//发射完成
	void explosionBall(CCPoint pt);//爆炸特效
	bool backBall(int hitIndex);//回退
	bool backBallMove(int start,int end);//回退时移动
	void goAll();//移动所有
	void stopAll();//停止所有
	void removeBallFromUI(int removeStart,int removeEnd);//从界面删除球
	void removeBallFromArray(int removeStart,int removeEnd);//从球数组删除
	bool isMoving();//判断是否有球正在移动

	void initWayPoint();//初始化地图
	void insertBall();//插入球到轨道
	void insertBallFinish();//插入球到轨道完成
	void createBallTask(float dt);//创建球定时器
	void removeBallTask(float dt);//移除球定时器

	const char * getColor(int colorType);
	bool IsLineSegmentCross(CCPoint pFirst1, CCPoint pFirst2, CCPoint pSecond1, CCPoint pSecond2);//计算球是否碰撞
	CCPoint GetCrossPoint(CCPoint p1, CCPoint p2, CCPoint q1, CCPoint q2);//碰撞的焦点
};
#endif

