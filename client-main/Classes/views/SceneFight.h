#ifndef __SCENE_FIGHT_H_
#define __SCENE_FIGHT_H_

#include "cocos2d.h"
#include "../core/LayerUI.h"
#include "../domain/Ball.h"

//#define _distanceOfBall 34
#define _indexDistanceOfBall 8
#define _color CCRANDOM_0_1()*4+1

//å¼€æˆ˜è¯·æ±‚ï¼ŒèŽ·å–NPCæ•°æ®
struct VoFight:VoObject {
    int * id;
    int * npc;
};

//æˆ˜æ–—ç»“æŸï¼ŒèŽ·å–æˆ˜æŠ?
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
	void addPushBall();//ÅÚÌ¨Ôö¼Ó·¢ÉäÇò
	void pushBall(float interval,CCPoint pos);//·¢Éä
	void pushBallFinish();//·¢ÉäÍê³É
	void explosionBall(CCPoint pt);//±¬Õ¨ÌØÐ§
	bool backBall(int hitIndex);//»ØÍË
	bool backBallMove(int start,int end);//»ØÍËÊ±ÒÆ¶¯
	void goAll();//ÒÆ¶¯ËùÓÐ
	void stopAll();//Í£Ö¹ËùÓÐ
	void removeBallFromUI(int removeStart,int removeEnd);//´Ó½çÃæÉ¾³ýÇò
	void removeBallFromArray(int removeStart,int removeEnd);//´ÓÇòÊý×éÉ¾³ý
	bool isMoving();//ÅÐ¶ÏÊÇ·ñÓÐÇòÕýÔÚÒÆ¶¯

	void initWayPoint();//³õÊ¼»¯µØÍ¼
	void insertBall();//²åÈëÇòµ½¹ìµÀ
	void insertBallFinish();//²åÈëÇòµ½¹ìµÀÍê³É
	void createBallTask(float dt);//´´½¨Çò¶¨Ê±Æ÷
	void removeBallTask(float dt);//ÒÆ³ýÇò¶¨Ê±Æ÷

	const char * getColor(int colorType);
	bool IsLineSegmentCross(CCPoint pFirst1, CCPoint pFirst2, CCPoint pSecond1, CCPoint pSecond2);//Âºâˆ†Ã€â€žÂ«ÃšÂ Â«âˆ‘Ã’â‰ˆË†â—Šâ‰?
	CCPoint GetCrossPoint(CCPoint p1, CCPoint p2, CCPoint q1, CCPoint q2);//â‰ˆË†â—Šâ‰¤ÂµÆ’Î©Ï€Âµâ€?
};
#endif

