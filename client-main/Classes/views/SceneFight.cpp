#include "SceneFight.h"
#include "SceneMain.h"
#include "Facade.h"
#include "../core/SmartRes.h"

using namespace cocos2d;
extern std::vector<std::string> split(const std::string s, char delim);

int hitBallArrayIndex=-1;
char insertSide;

LayerUI* SceneFight::scene(VoFight* vo)
{
    
	CCScene *scene = CCScene::create();
    
	SceneFight *layer = SceneFight::create();
    
	layer->vo=vo;
    
	layer->initLayer();
    
	scene->addChild(layer);
    
	CCDirector::sharedDirector()->replaceScene(scene);
    
	return layer;
}

void SceneFight:: initLayer()
{
	if ( !CCLayer::init() )
	{
		return;
	}
    
    
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(SceneFight::back) );
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);
    
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	//创建地图轨迹
	m_wayPoint=CCPointArray::create(1000);
	m_wayPoint->retain();
	initWayPoint();
    
	//创建球数组
	m_balls=CCArray::create();
	m_balls->retain();
    
	//创建发射球
	addPushBall();
    
	/************************************************************************/
	/* 定时任务                                                                     */
	/************************************************************************/
	//创建球
	CCScheduler *createBallScheduler = CCDirector::sharedDirector()->getScheduler();
	createBallScheduler->scheduleSelector(SEL_SCHEDULE(&SceneFight::createBallTask),this,0.001f,false);
	//消球
	CCScheduler *removeBallScheduler = CCDirector::sharedDirector()->getScheduler();
	removeBallScheduler->scheduleSelector(SEL_SCHEDULE(&SceneFight::removeBallTask),this,0.001f,false);
    
}

void SceneFight::back(CCObject* pSender)
{
	LayerUI *pScene = SceneMain::scene(NULL,false);
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&SceneFight::createBallTask),this);
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&SceneFight::removeBallTask),this);
}

void SceneFight::onEnter(){
	//CCLog("onEnter");
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
	//CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

void SceneFight::onExit(){
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&SceneFight::createBallTask),this);
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&SceneFight::removeBallTask),this);
}

bool SceneFight::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

void SceneFight::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	//CCLog("ccTouchEnded");
	//取得触点位置

	CCPoint touchLocation = pTouch->getLocation();  
	CCLOG("%f,%f",touchLocation.x,touchLocation.y);

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCPoint start=m_pushBall->m_sprite->getPosition();
	CCPoint end=touchLocation;
	//两点距离
	float distance = ccpDistance(start, end);
	float difx = end.x - start.x;
	float dify = end.y - start.y;
	float delta = (float)(s.height/2) / distance;
	CCPoint tmpPos=ccp(start.x + (difx * delta), start.y + (dify * delta));
	//CCLOG("tmpPos===%f,%f",tmpPos.x,tmpPos.y);
	CCPoint a=CCPointMake(start.x,start.y);
	CCPoint b=CCPointMake(tmpPos.x,tmpPos.y);
	bool bCross=false;
	for(int i=0;i<m_balls->count()-1;i++)
	{
		Ball*startBall=(Ball*)m_balls->objectAtIndex(i);
		Ball*endBall=(Ball*)m_balls->objectAtIndex(i+1);
		CCPoint startBallPos=m_wayPoint->getControlPointAtIndex(startBall->m_curPosIndex);
		CCPoint endBallPos=m_wayPoint->getControlPointAtIndex(endBall->m_curPosIndex);
        
		CCPoint c=CCPointMake(startBallPos.x,startBallPos.y);
		CCPoint d=CCPointMake(endBallPos.x,endBallPos.y);
        
		CCPoint pointCross;
		//计算是否碰撞
		bCross = IsLineSegmentCross(a,b,c,d);
		if(i==0 && !bCross)
		{
			//插入到开头
			startBallPos=m_wayPoint->getControlPointAtIndex(startBall->m_curPosIndex+_indexDistanceOfBall);
			endBallPos=m_wayPoint->getControlPointAtIndex(startBall->m_curPosIndex);
			c=CCPointMake(startBallPos.x,startBallPos.y);
			d=CCPointMake(endBallPos.x,endBallPos.y);
			bCross = IsLineSegmentCross(a,b,c,d);
			if (bCross)
			{
				insertSide='R';
				hitBallArrayIndex=i;
				break;
			}
		}
		if (bCross)
		{
			//碰撞的焦点
			pointCross = GetCrossPoint(a,b,c,d);
			float cDistance = ccpDistance(pointCross, c);
			float dDistance = ccpDistance(pointCross, d);
			//CCLOG("pointCross===x===%f===y===%f",pointCross.x,pointCross.y);
			//CCLOG("cDistance===%f===dDistance===%f",cDistance,dDistance);
			if(cDistance<50 && dDistance<50)
				insertSide='R';
			else if(cDistance<50)
				insertSide='L';
			else if(dDistance<50)
				insertSide='R';
			else
				bCross=false;
			hitBallArrayIndex=i+1;
			break;
		}
	}
	if(!bCross)
		pushBall(0.3f,tmpPos);
	else
		insertBall();
}

/************************************************************************/
/* 得到随机球                                                        */
/************************************************************************/
Ball * SceneFight::getBall()
{
	int color=_color;
	const char *fileName=getColor(color);
	Ball *ball=Ball::create();
	ball->m_sprite=CCSprite::create(fileName);
	ball->m_wayPoint=this->m_wayPoint;
	ball->m_color=color;
	return ball;
}
/************************************************************************/
/* 创建发射球                                                              */
/************************************************************************/
void SceneFight::addPushBall(){
	m_pushBall=getBall();
	//CCLOG("pushBall-color===%d",m_pushBall->m_color);
	m_pushBall->retain();
	m_pushBall->m_sprite->setPosition(ccp(_center.x,_center.y-200));
	addChild(m_pushBall->m_sprite);
};
/************************************************************************/
/* 发射球                                                               */
/************************************************************************/
void SceneFight::pushBall(float interval,CCPoint pos)
{
	CCActionInterval*  actionTo = CCMoveTo::create(interval, pos);
	CCCallFunc * call=CCCallFunc::actionWithTarget(this,callfunc_selector(SceneFight::pushBallFinish));
	m_pushBallAction=CCSequence::actions(actionTo,call,NULL);
	m_pushBall->m_sprite->runAction(m_pushBallAction);
}
/************************************************************************/
/* 发送完成                                                                    */
/************************************************************************/
void SceneFight::pushBallFinish(){
	//重新创建发送球
	m_pushBall->m_sprite->removeFromParentAndCleanup(true);
	m_pushBall->release();
	m_pushBall=NULL;
	addPushBall();
}
/************************************************************************/
/* 创建轨道球任务                                                                     */
/************************************************************************/
int ballNum=0;
void SceneFight::createBallTask(float dt){
	for(int i=0;i<m_balls->count();i++)
	{
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		if(ball->m_curPosIndex>=m_wayPoint->count()-50)
		{
			ball->stop();
			ball->m_sprite->removeFromParentAndCleanup(true);
			m_balls->removeObject(ball,true);
			break;
		}
	}
	if(m_balls->count()>0)
	{
		Ball *lastBall=(Ball*)m_balls->objectAtIndex(m_balls->count()-1);
		if(lastBall->m_curPosIndex<=_indexDistanceOfBall)
			return;
	}
	
	/*
	int distance=-1;
	if(m_balls->count()>0)
	{
		CCPoint wayFirstPos=m_wayPoint->getControlPointAtIndex(0);
		Ball *lastBall=(Ball*)m_balls->objectAtIndex(m_balls->count()-1);
		CCPoint lastBallPos=lastBall->m_sprite->getPosition();
		distance=ccpDistance(wayFirstPos,lastBallPos);
		CCLOG("distance===%d===lastBallIndex===%d",distance,lastBall->m_curPosIndex);
	}
	*/
	ballNum++;
	if(ballNum>100)
		return;
	Ball *ball=getBall();
	m_balls->addObject(ball);
	ball->m_sprite->setPosition(m_wayPoint->getControlPointAtIndex(0));
	addChild(ball->m_sprite);
	ball->go();
}
/************************************************************************/
/* 插入球到轨道                                                               */
/************************************************************************/
bool inserting=false;
void SceneFight::insertBall()
{
	if(hitBallArrayIndex>=0){
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		//撞击点位置索引
		int hitCurPosIndex=0;
		CCLOG("insertSide===%c",insertSide);
		Ball*hitBall=NULL;
		if(insertSide=='L')
		{
			hitBall=(Ball*)m_balls->objectAtIndex(hitBallArrayIndex-1);
			hitCurPosIndex=hitBall->m_curPosIndex;
		}
		else if(insertSide=='R')
		{
			hitBall=(Ball*)m_balls->objectAtIndex(hitBallArrayIndex);
			hitCurPosIndex=hitBall->m_curPosIndex+_indexDistanceOfBall;
		}
		//撞击点位置
		CCPoint hitPos=m_wayPoint->getControlPointAtIndex(hitCurPosIndex);
		//插入之前停止球移动
		stopAll();
		//开始将球加入轨道
		CCFileUtils::sharedFileUtils()->setResourceDirectory("role");
		const char *str=getColor(m_pushBall->m_color);

		Ball*insertBall=Ball::create();
		insertBall->m_sprite=CCSprite::create(str);
		insertBall->m_wayPoint=m_wayPoint;
		insertBall->m_curPosIndex=hitCurPosIndex;
		insertBall->m_color=m_pushBall->m_color;
	
		if(hitBall->m_isPause)
		{
			insertBall->m_isPause=true;
			insertBall->m_isStop=false;
		}
		else
		{
			insertBall->m_isPause=false;
			insertBall->m_isStop=true;
		}
		m_balls->insertObject(insertBall,hitBallArrayIndex);
		//插入位置
		//insertBall->m_sprite->setOpacity(0);
		//insertBall->m_sprite->setPosition(hitPos);
		insertBall->m_sprite->setPosition(m_pushBall->m_sprite->getPosition());
		//撞击点前面的球向前移动
		for(int i=0;i<hitBallArrayIndex;i++){
			Ball *moveBall=(Ball*)m_balls->objectAtIndex(i);
			moveBall->m_moveToPosIndex=moveBall->m_curPosIndex+_indexDistanceOfBall;
			moveBall->move();
		}
		
		//新增球移动到轨道上
		inserting=true;
		CCMoveTo*  moveTo = CCMoveTo::create(0.3f, hitPos);
		CCCallFunc *call=CCCallFunc::actionWithTarget(this,callfunc_selector(SceneFight::insertBallFinish));
		CCAction *sequenceAction = CCSequence::actions(moveTo,call,NULL);
		insertBall->m_sprite->runAction(sequenceAction);
		
		/*
		for(int i=0;i<m_balls->count();i++){
			Ball *moveBall=(Ball*)m_balls->objectAtIndex(i);
			//moveBall->go();
		}
		*/
		/*
		CCActionInterval*  insertAction = CCFadeIn::create(1.0f);
		insertBall->m_sprite->runAction(insertAction);
		*/
		//insertBall->go();

		addChild(insertBall->m_sprite);
		//清除发送球
		this->pushBallFinish();
	}
}
void SceneFight::insertBallFinish()
{
	inserting=false;
}

/************************************************************************/
/* 消球                                                                     */
/************************************************************************/
void SceneFight::removeBallTask(float dt)
{
	//正在插入，则直接退出
	if(inserting){return;}
	//检测是否有球正在移动,true则返回
	bool moving=isMoving();
	if(moving){return;}
	//插入后，启动所有球移动
	goAll();
	//静止球重新移动
	for (int i=m_balls->count()-1;i>0;i--)
	{
		Ball *currBall=(Ball*)m_balls->objectAtIndex(i);
		Ball *nextBall=(Ball*)m_balls->objectAtIndex(i-1);
		if(!currBall->m_isStop && !currBall->m_isPause && nextBall->m_isPause)
		{
			int indexDistance=nextBall->m_curPosIndex-currBall->m_curPosIndex;
			if(indexDistance<=_indexDistanceOfBall)
			{
				if(nextBall->m_isPause)
				{
					nextBall->go(); 
					nextBall->m_isPause=false;
				}	
			}
		}
	}
	//停止球
	for (int i=m_balls->count()-1;i>0;i--)
	{
		Ball *currBall=(Ball*)m_balls->objectAtIndex(i);
		Ball *nextBall=(Ball*)m_balls->objectAtIndex(i-1);
		int indexDistance=nextBall->m_curPosIndex-currBall->m_curPosIndex;
		if(indexDistance>2*_indexDistanceOfBall && currBall->m_color!=nextBall->m_color)
		{
			for(int j=i-1;j>=0;j--)
			{
				Ball *ball=(Ball*)m_balls->objectAtIndex(j);
				if(!ball->m_isPause)
				{
					ball->stop();
					ball->m_isPause=true;
				}	
			}
			break;
		}
	}
	//没有撞击,则直接退出
	if(hitBallArrayIndex==-1){return;}
	//回退
	bool isBack=backBall(hitBallArrayIndex);
	if(isBack){return;}
    
	Ball *hitBall=(Ball*)m_balls->objectAtIndex(hitBallArrayIndex);
	int removeBegin=-1,removeEnd=-1;
	//起点
	for(int i=hitBallArrayIndex;i>=0;i--)
	{
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		if(ball->m_color!=hitBall->m_color)
			break;
		removeBegin=i;
	}
	//终点
	for(int i=hitBallArrayIndex;i<m_balls->count();i++)
	{
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		if(ball->m_color!=hitBall->m_color)
			break;
		removeEnd=i;
	}
	//开始消除
	if((removeEnd-removeBegin)>=2)
	{
		//界面消除
		removeBallFromUI(removeBegin,removeEnd);
		//记录消除后新的撞击球
		Ball* newHitBall=(Ball*)m_balls->objectAtIndex(removeEnd+1);
		//从数组删除
		removeBallFromArray(removeBegin,removeEnd);
		//获取撞击点在新数组的位置索引
		hitBallArrayIndex=m_balls->indexOfObject(newHitBall);
		//消除后回退
		//isBack=backBall(hitBallArrayIndex);
		//if(isBack){return;}
		//消除后停止球
		/*
		if(hitBallArrayIndex==0){return;}
		Ball *startBall=(Ball*)m_balls->objectAtIndex(hitBallArrayIndex-1);
		int indexDistance=startBall->m_curPosIndex-newHitBall->m_curPosIndex;
		if(indexDistance>_indexDistanceOfBall && startBall->m_color!=newHitBall->m_color)
		{
			
			for(int i=hitBallArrayIndex-1;i>=0;i--)
			{
				Ball *ball=(Ball*)m_balls->objectAtIndex(i);
				ball->stop();
				ball->m_isPause=true;
			}
		}*/
		return ;
	}
	hitBallArrayIndex=-1;
}


/************************************************************************/
/* 回退                                                                    */
/************************************************************************/
bool SceneFight::backBall(int hitIndex)
{
	bool isBack=false;
	int start=hitIndex-1,end=hitIndex;//停靠在右边
	if(start<0)
		return isBack;
	//开始移动
	isBack=backBallMove(start,end);
	//再停靠左边的情况
	if(!isBack)
	{
		start=hitIndex,end=hitIndex+1;//停靠在左边
		if(end>=m_balls->count())
			return isBack;
		//开始移动
		isBack=backBallMove(start,end);
	}
	return isBack;
}
/************************************************************************/
/* 回退时移动                                                                     */
/************************************************************************/
bool SceneFight::backBallMove(int start,int end)
{
	bool isBack=false;
	Ball *startBall=(Ball*)m_balls->objectAtIndex(start);
	Ball *endBall=(Ball*)m_balls->objectAtIndex(end);
	int indexDistance=startBall->m_curPosIndex-endBall->m_curPosIndex;

	if(indexDistance>_indexDistanceOfBall&& startBall->m_color==endBall->m_color)//&& startBall->m_color==endBall->m_color
	{	
		CCLOG("indexDistance===%d",indexDistance);

		isBack=true;
		//回退之前停止球移动
		stopAll();
		for(int i=start;i>=0;i--)
		{
			Ball *currBall=(Ball*)m_balls->objectAtIndex(i);
			int indexDistance111=currBall->m_curPosIndex-endBall->m_curPosIndex;
			CCLOG("i===%d===indexDistance===%d",i,indexDistance111);
			//currBall->m_moveToPosIndex=endBall->m_curPosIndex+INDEX_DISTANCE*(start-i+1);
			currBall->m_moveToPosIndex=currBall->m_curPosIndex-indexDistance+_indexDistanceOfBall;
			currBall->move();
			//break;
		}
	}
	return isBack;
}

/************************************************************************/
/* 从UI删除球                                                                     */
/************************************************************************/
void SceneFight::removeBallFromUI(int removeStart,int removeEnd)
{
	for(int i=removeStart;i<=removeEnd;i++)
	{
		Ball *removeBall=(Ball*)m_balls->objectAtIndex(i);
		explosionBall(removeBall->m_sprite->getPosition());
		removeBall->m_sprite->removeFromParentAndCleanup(true);
	}
    
}
/************************************************************************/
/* 从球数组删除                                                                     */
/************************************************************************/
void SceneFight::removeBallFromArray(int removeStart,int removeEnd)
{
	CCArray *tmpBalls=CCArray::create();
	//收集要删除的球
	for(int i=removeStart;i<=removeEnd;i++)
	{
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		tmpBalls->addObject(ball);
	}
	//CCLOG("tmpBalls-size===%d",tmpBalls->count());
	for(int i=0;i<tmpBalls->count();i++)
	{
		Ball *removeBall=(Ball*)tmpBalls->objectAtIndex(i);
		for(int j=0;j<m_balls->count();j++){
			if(removeBall->isEqual(m_balls->objectAtIndex(j))){
				m_balls->removeObject(removeBall);
				break;
			}
		}
	}
}
/************************************************************************/
/* 计算是否有球在移动                                                                     */
/************************************************************************/
bool SceneFight::isMoving()
{
	bool isMoving=false;
	for(int i=0;i<m_balls->count();i++)
	{
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		if(ball->m_moving)
		{
			isMoving=true;
			break;
		}
	}
	return isMoving;
}
void SceneFight::goAll()
{
	for(int i=0;i<m_balls->count();i++)
	{
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		if(ball->m_isPause)
			continue;
		//CCLOG("i===%d===isStop===%d",i,ball->m_isStop);
		if(ball->m_isStop)
		{
			ball->go();
			ball->m_isStop=false;
		}
	}
}
void SceneFight::stopAll()
{
	for(int i=0;i<m_balls->count();i++)
	{
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		if(ball->m_isPause)
			continue;
		if(!ball->m_isStop)
		{
			ball->stop();
			ball->m_isStop=true;
		}
	}
}


/************************************************************************/
/* 初始化地图轨迹节点                                                                     */
/************************************************************************/
void SceneFight::initWayPoint(){
	std::string pts="701.313354,126.706619|658.646118,126.706619|568.820190,126.706619|485.731232,122.215607|342.009949,119.970100|220.745148,119.970100|88.252098,119.970100|52.318680,191.827194|52.315369,268.176941|52.312344,337.791412|54.554272,425.372803|54.551472,490.498840|54.550018,524.185181|133.151978,526.430908|234.211792,526.430908|317.305389,521.939453|398.153198,519.693726|474.509369,521.939453|553.111450,524.185181|622.730530,526.430908|674.383240,526.430908|690.103760,528.676697";
	char pattern = '|';
	char nextPattern = ',';
	std::vector<std::string> points=split(pts,pattern);
	for(int i=0;i<points.size();i++){
		std::string point=points[i];
		std::vector<std::string> XY=split(point,nextPattern);
		CCPoint start=CCPointMake(atof(XY[0].c_str()),atof(XY[1].c_str()));
		if(i==points.size()-1){
			m_wayPoint->addControlPoint(start);
			break;
		}
        
		std::string nextPoint=points[i+1];
		std::vector<std::string> nextXY=split(nextPoint,nextPattern);
		CCPoint end=CCPointMake(atof(nextXY[0].c_str()),atof(nextXY[1].c_str()));
		//两点距离
		float distance = ccpDistance(start, end);
		if (distance > 1)
		{
			int d = (int)distance;
			for (int i = 0; i < d; i+=6)
			{
				float difx = end.x - start.x;
				float dify = end.y - start.y;
				float delta = (float)i / distance;
				CCPoint tmpPos=ccp(start.x + (difx * delta), start.y + (dify * delta));
				//CCLOG("pos===x===%f===y===%f",tmpPos.x,tmpPos.y);
				m_wayPoint->addControlPoint(tmpPos);
			}
		}
	}
}

/************************************************************************/
/* 显示爆炸效果                                                                     */
/************************************************************************/
void SceneFight::explosionBall(CCPoint pt){
	CCFileUtils::sharedFileUtils()->setResourceDirectory("ui");
	//粒子发射器
	CCParticleSystem * emitter=CCParticleExplosion::create();
	//爆炸效果
	emitter->setPosition(ccp(pt.x,pt.y));
	emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("CloseNormal.png"));
	emitter->setBlendAdditive(true);
	emitter->setLife(0.5f);//粒子寿命
	emitter->setLifeVar(0);
	emitter->setAutoRemoveOnFinish(true);
	this->addChild(emitter);
}

/* 
判断两条线段是否相交(有交点) 
*/  
bool SceneFight::IsLineSegmentCross(CCPoint pFirst1, CCPoint pFirst2, CCPoint pSecond1, CCPoint pSecond2)  
{  
	//每个线段的两点都在另一个线段的左右不同侧，则能断定线段相交  
	//公式对于向量(x1,y1)->(x2,y2),判断点(x3,y3)在向量的左边,右边,还是线上.  
	//p=x1(y3-y2)+x2(y1-y3)+x3(y2-y1).p<0 左侧,    p=0 线上, p>0 右侧  
	long Linep1,Linep2;  
	//判断pSecond1和pSecond2是否在pFirst1->pFirst2两侧  
	Linep1 = pFirst1.x * (pSecond1.y - pFirst2.y) +  
		pFirst2.x * (pFirst1.y - pSecond1.y) +  
		pSecond1.x * (pFirst2.y - pFirst1.y);  
	Linep2 = pFirst1.x * (pSecond2.y - pFirst2.y) +  
		pFirst2.x * (pFirst1.y - pSecond2.y) +  
		pSecond2.x * (pFirst2.y - pFirst1.y);  
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//符号位异或为0:pSecond1和pSecond2在pFirst1->pFirst2同侧  
	{  
		return false;  
	}  
	//判断pFirst1和pFirst2是否在pSecond1->pSecond2两侧  
	Linep1 = pSecond1.x * (pFirst1.y - pSecond2.y) +  
		pSecond2.x * (pSecond1.y - pFirst1.y) +  
		pFirst1.x * (pSecond2.y - pSecond1.y);  
	Linep2 = pSecond1.x * (pFirst2.y - pSecond2.y) +  
		pSecond2.x * (pSecond1.y - pFirst2.y) +  
		pFirst2.x * (pSecond2.y - pSecond1.y);  
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//符号位异或为0:pFirst1和pFirst2在pSecond1->pSecond2同侧  
	{  
		return false;  
	}  
	//否则判为相交  
	return true;  
} 
/* 
求两直线交点，前提是两条直线必须有交点 
在相交的情况下，可以应付各种情况(垂直、系数等) 
*/  
CCPoint SceneFight::GetCrossPoint(CCPoint p1, CCPoint p2, CCPoint q1, CCPoint q2)  
{  
	//必须相交求出的才是线段的交点，但是下面的程序段是通用的  
	assert(IsLineSegmentCross(p1,p2,q1,q2));  
	/*根据两点式化为标准式，进而求线性方程组*/  
	CCPoint crossPoint;  
	long tempLeft,tempRight;  
	//求x坐标  
	tempLeft = (q2.x - q1.x) * (p1.y - p2.y) - (p2.x - p1.x) * (q1.y - q2.y);  
	tempRight = (p1.y - q1.y) * (p2.x - p1.x) * (q2.x - q1.x) + q1.x * (q2.y - q1.y) * (p2.x - p1.x) - p1.x * (p2.y - p1.y) * (q2.x - q1.x);  
	crossPoint.x =(int)( (double)tempRight / (double)tempLeft );  
	//求y坐标    
	tempLeft = (p1.x - p2.x) * (q2.y - q1.y) - (p2.y - p1.y) * (q1.x - q2.x);  
	tempRight = p2.y * (p1.x - p2.x) * (q2.y - q1.y) + (q2.x- p2.x) * (q2.y - q1.y) * (p1.y - p2.y) - q2.y * (q1.x - q2.x) * (p2.y - p1.y);  
	crossPoint.y =(int)( (double)tempRight / (double)tempLeft );  
	return crossPoint;  
} 
const char* SceneFight::getColor(int colorType){
	//CCLog("colorType===%d",colorType);
	CCFileUtils::sharedFileUtils()->setResourceDirectory("role");
	const char *str;
	if(colorType==1)
		str="red.png";
	else if(colorType==2)
		str="yellow.png";
	else if(colorType==3)
		str="blue.png";
	else if(colorType==4)
		str="zise.png";
	return str;
}