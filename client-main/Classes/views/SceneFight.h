#ifndef __SCENE_FIGHT_H_
#define __SCENE_FIGHT_H_

#include "cocos2d.h"
#include "../core/LayerUI.h"
#include "../domain/Ball.h"

#define INDEX_DISTANCE 5
#define _color CCRANDOM_0_1()*4+1

//开战请求，获取NPC数据
struct VoFight:VoObject {
    int * id;
    int * npc;
};

//战斗结束，获取战报
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
	void addPushBall();//≈⁄Ã®‘ˆº”∑¢…‰«Ú
	void pushBall(float interval,CCPoint pos);//∑¢…‰
	void pushBallFinish();//∑¢…‰ÕÍ≥…
	void ballExplosion(CCPoint pt);//±¨’®Ãÿ–ß
	bool ballBack(int hitIndex);//ªÿÕÀ
	bool ballBackMove(int start,int end);//ªÿÕÀ ±“∆∂Ø
	void removeBallFromUI(int removeStart,int removeEnd);//¥”ΩÁ√Ê…æ≥˝«Ú
	void removeBallFromArray(int removeStart,int removeEnd);//¥”«Ú ˝◊È…æ≥˝
	bool isMoving();//≈–∂œ «∑Ò”–«Ú’˝‘⁄“∆∂Ø

	void initWayPoint();//≥ı ºªØµÿÕº
	void insertBall();//≤Â»Î«ÚµΩπÏµ¿
	void insertBallFinish();//≤Â»Î«ÚµΩπÏµ¿ÕÍ≥…
	void createBallTask(float dt);//¥¥Ω®«Ú∂® ±∆˜
	void removeBallTask(float dt);//“∆≥˝«Ú∂® ±∆˜

	const char * getColor(int colorType);
	bool IsLineSegmentCross(CCPoint pFirst1, CCPoint pFirst2, CCPoint pSecond1, CCPoint pSecond2);//º∆À„«Ú «∑Ò≈ˆ◊≤
	CCPoint GetCrossPoint(CCPoint p1, CCPoint p2, CCPoint q1, CCPoint q2);//≈ˆ◊≤µƒΩπµ„
};
#endif

