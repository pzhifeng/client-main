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
	void addPushBall();//炮台增加发射球
	void pushBall(float interval,CCPoint pos);//发射
	void pushBallFinish();//发射完成
	void ballExplosion(CCPoint pt);//爆炸特效
	bool ballBack(int hitIndex);//球回退
	void removeBallFromUI(int removeStart,int removeEnd);//从界面删除球
	void removeBallFromArray(int removeStart,int removeEnd);//从球数组删除
	bool isMoving();//是否有球正在移动

	void initWayPoint();//初始化地图
	void checkHitTask(float dt);//检测撞击定时器
	void insertBallFinish();//插入球到轨道完成
	void createBallTask(float dt);//创建球定时器
	void removeBallTask(float dt);//移除球定时器
	int isHit();//检测撞击
	const char * getColor(int colorType);
};
#endif

