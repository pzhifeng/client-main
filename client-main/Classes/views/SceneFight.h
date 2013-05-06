#ifndef __SCENE_FIGHT_H_
#define __SCENE_FIGHT_H_

#include "cocos2d.h"
#include "../VoObject.h"
#include "../core/LayerUI.h"
#include "../domain/Ball.h"

#define INDEX_DISTANCE 44
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
	void addPushBall();
	void pushBall(float interval,CCPoint pos);
	void pushBallFinish();
	void ballExplosion(CCPoint pt);//±¬Õ¨ÌØÐ§
	void ballsSort();
	void initWayPoint();
	void checkHitTask(float dt);
	void createBallTask(float dt);
	void removeBallTask(float dt);
	int isHit();
	const char * getColor(int colorType);
};
#endif

