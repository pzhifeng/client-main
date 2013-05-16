#include "SceneFight.h"
#include "SceneMain.h"
#include "Facade.h"
#include "../core/SmartRes.h"

using namespace cocos2d;
extern std::vector<std::string> split(const std::string s, char delim);

int hitBallArrayIndex=-1;
char insertSide;

LayerUI* SceneFight::scene(VoHome* vo)
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


	CCLOG("name===%s",vo->name);
	CCLOG("title===%s",vo->title);

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	//������ͼ�켣
	m_wayPoint=CCPointArray::create(1000);
	m_wayPoint->retain();
	initWayPoint();

	//����������
	m_balls=CCArray::create();
	m_balls->retain();

	//����������
	addPushBall();

	/************************************************************************/
	/* ��ʱ����                                                                     */
	/************************************************************************/
	//������
	CCScheduler *createBallScheduler = CCDirector::sharedDirector()->getScheduler();
	createBallScheduler->scheduleSelector(SEL_SCHEDULE(&SceneFight::createBallTask),this,0.1f,false);
	//����
	CCScheduler *removeBallScheduler = CCDirector::sharedDirector()->getScheduler();
	removeBallScheduler->scheduleSelector(SEL_SCHEDULE(&SceneFight::removeBallTask),this,0.001f,false);

}

void SceneFight::back(CCObject* pSender)
{
	LayerUI *pScene = SceneMain::scene(NULL,false);
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
}

bool SceneFight::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

void SceneFight::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	//CCLog("ccTouchEnded");  
	//ȡ�ô���λ��
	CCPoint touchLocation = pTouch->getLocation();  
	//CCLOG("%f,%f",touchLocation.x,touchLocation.y);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCPoint start=m_pushBall->m_sprite->getPosition();
	CCPoint end=touchLocation;
	//�������
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
		//�����Ƿ���ײ
		bCross = IsLineSegmentCross(a,b,c,d);  
		if(i==0 && !bCross)
		{
			//���뵽��ͷ
			startBallPos=m_wayPoint->getControlPointAtIndex(startBall->m_curPosIndex+INDEX_DISTANCE);
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
			//��ײ�Ľ���
			pointCross = GetCrossPoint(a,b,c,d);  
			float cDistance = ccpDistance(pointCross, c);
			float dDistance = ccpDistance(pointCross, d);
			CCLOG("pointCross===x===%f===y===%f",pointCross.x,pointCross.y);
			CCLOG("cDistance===%f===dDistance===%f",cDistance,dDistance);
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
/* �õ������                                                        */
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
/* ����������                                                              */
/************************************************************************/
void SceneFight::addPushBall(){
	m_pushBall=getBall();
	//CCLOG("pushBall-color===%d",m_pushBall->m_color);
	m_pushBall->retain();
	m_pushBall->m_sprite->setPosition(ccp(_center.x,_center.y-200));
	addChild(m_pushBall->m_sprite);
};
/************************************************************************/
/* ������                                                               */
/************************************************************************/
void SceneFight::pushBall(float interval,CCPoint pos)
{
	CCActionInterval*  actionTo = CCMoveTo::create(interval, pos);
	CCCallFunc * call=CCCallFunc::actionWithTarget(this,callfunc_selector(SceneFight::pushBallFinish));
	m_pushBallAction=CCSequence::actions(actionTo,call,NULL);
	m_pushBall->m_sprite->runAction(m_pushBallAction);	
}
/************************************************************************/
/* �������                                                                    */
/************************************************************************/
void SceneFight::pushBallFinish(){
	//���´���������
	m_pushBall->m_sprite->removeFromParentAndCleanup(true);
	m_pushBall->release();
	m_pushBall=NULL;
	addPushBall();
}
/************************************************************************/
/* �������������                                                                     */
/************************************************************************/
void SceneFight::createBallTask(float dt){
	if(m_balls->count()>0){
		Ball *lastBall=(Ball*)m_balls->objectAtIndex(m_balls->count()-1);
		if(lastBall->m_curPosIndex<INDEX_DISTANCE)
			return;
	}
	Ball *ball=getBall();
	m_balls->addObject(ball);
	ball->m_sprite->setPosition(m_wayPoint->getControlPointAtIndex(0));
	addChild(ball->m_sprite);
	ball->go();
}
/************************************************************************/
/* �����򵽹��                                                               */
/************************************************************************/
bool inserting=false;
void SceneFight::insertBall(){
	if(hitBallArrayIndex>=0){
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		//ײ����λ������
		int hitCurPosIndex=0;
		CCLOG("insertSide===%c",insertSide);
		if(insertSide=='L')
		{
			Ball*hitBall=(Ball*)m_balls->objectAtIndex(hitBallArrayIndex-1);
			hitCurPosIndex=hitBall->m_curPosIndex;
		}
		else if(insertSide=='R')
		{
			Ball*hitBall=(Ball*)m_balls->objectAtIndex(hitBallArrayIndex);
			hitCurPosIndex=hitBall->m_curPosIndex+INDEX_DISTANCE;
		}
		//ײ����λ��
		CCPoint hitPos=m_wayPoint->getControlPointAtIndex(hitCurPosIndex);
		//ײ����ǰ�������ǰ�ƶ�
		for(int i=0;i<hitBallArrayIndex;i++){
			Ball *moveBall=(Ball*)m_balls->objectAtIndex(i);
			moveBall->m_moveToPosIndex=moveBall->m_curPosIndex+INDEX_DISTANCE;
			moveBall->move();
		}
		//���������
		//CCLOG("pushBall-color-checkHitTask===%d",m_pushBall->m_color);
		CCFileUtils::sharedFileUtils()->setResourceDirectory("role");
		const char *str=getColor(m_pushBall->m_color);
		Ball *insertBall=Ball::create();
		insertBall->m_sprite=CCSprite::create(str);
		insertBall->m_wayPoint=m_wayPoint;
		insertBall->m_curPosIndex=hitCurPosIndex;
		insertBall->m_color=m_pushBall->m_color;
		m_balls->insertObject(insertBall,hitBallArrayIndex);
		//����Ҫ����������ʼλ��
		insertBall->m_sprite->setPosition(m_pushBall->m_sprite->getPosition());
		//�ƶ��������
		inserting=true;
		CCMoveTo*  moveTo = CCMoveTo::create(0.2f, hitPos);
		CCCallFunc *call=CCCallFunc::actionWithTarget(this,callfunc_selector(SceneFight::insertBallFinish));
		CCAction *sequenceAction = CCSequence::actions(moveTo,call,NULL);   
		insertBall->m_sprite->runAction(sequenceAction);
		
		addChild(insertBall->m_sprite);
	    //insertBall->go();
	}
}
void SceneFight::insertBallFinish()
{
	inserting=false;
	//���������
	this->pushBallFinish();
}

/************************************************************************/
/* ����                                                                     */
/************************************************************************/
void SceneFight::removeBallTask(float dt)
{
	//����Ƿ����������ƶ�
	bool moving=isMoving();
	if(moving){return;}
	
	//ֹͣ���ƶ�
	for (int i=m_balls->count()-1;i>0;i--)
	{
		Ball *currBall=(Ball*)m_balls->objectAtIndex(i);
		Ball *nextBall=(Ball*)m_balls->objectAtIndex(i-1);
		int indexDistance=nextBall->m_curPosIndex-currBall->m_curPosIndex;
		if(indexDistance>INDEX_DISTANCE && currBall->m_color!=nextBall->m_color)
		{
			for(int j=i-1;j>=0;j--)
			{
				Ball *ball=(Ball*)m_balls->objectAtIndex(j);
				ball->stop();
				ball->m_goSequneceAction=NULL;
			}
			break;
		}
	}
	//��ֹ�������ƶ�
	for (int i=m_balls->count()-1;i>0;i--)
	{
		Ball *currBall=(Ball*)m_balls->objectAtIndex(i);
		Ball *nextBall=(Ball*)m_balls->objectAtIndex(i-1);
		if(currBall->m_goSequneceAction!=NULL && nextBall->m_goSequneceAction==NULL)
		{
			int indexDistance=nextBall->m_curPosIndex-currBall->m_curPosIndex;
			if(indexDistance<INDEX_DISTANCE)
			{
				nextBall->go();
			}
			break;
		}
		
	}
	//û��ײ���������ڲ��룬��ֱ���˳�
	if(hitBallArrayIndex==-1){return;}
	if(inserting){return;}
	//����
	bool isBack=ballBack(hitBallArrayIndex);
	if(isBack){return;}

	Ball *hitBall=(Ball*)m_balls->objectAtIndex(hitBallArrayIndex);
	int removeBegin=-1,removeEnd=-1;
	//���
	for(int i=hitBallArrayIndex;i>=0;i--)
	{
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		if(ball->m_color!=hitBall->m_color)
			break;
		removeBegin=i;
	}
	//�յ�
	for(int i=hitBallArrayIndex;i<m_balls->count();i++)
	{
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		if(ball->m_color!=hitBall->m_color)
			break;
		removeEnd=i;
	}
	//��ʼ����
	if((removeEnd-removeBegin)>=2)
	{
		//��������
		removeBallFromUI(removeBegin,removeEnd);
		//��¼�������µ�ײ����
		Ball* newHitBall=(Ball*)m_balls->objectAtIndex(removeEnd+1);
		//������ɾ��
		removeBallFromArray(removeBegin,removeEnd);
		//��ȡײ�������������λ������
		hitBallArrayIndex=m_balls->indexOfObject(newHitBall);
		return ;
	}
	hitBallArrayIndex=-1;
}


/************************************************************************/
/* ����                                                                    */
/************************************************************************/
bool SceneFight::ballBack(int hitIndex){
	bool isBack=false;
	int start=hitIndex-1,end=hitIndex;//ͣ�����ұ�
	if(start<0)
		return isBack;
	//��ʼ�ƶ�
	isBack=ballBackMove(start,end);
	//��ͣ����ߵ����
	if(!isBack)
	{
		start=hitIndex,end=hitIndex+1;//ͣ�������
		if(end>=m_balls->count())
			return isBack;
		//��ʼ�ƶ�
		isBack=ballBackMove(start,end);
	}
	return isBack;
}
/************************************************************************/
/* ����ʱ�ƶ�                                                                     */
/************************************************************************/
bool SceneFight::ballBackMove(int start,int end)
{
	bool isBack=false;
	Ball *startBall=(Ball*)m_balls->objectAtIndex(start);
	Ball *endBall=(Ball*)m_balls->objectAtIndex(end);
	int indexDistance=startBall->m_curPosIndex-endBall->m_curPosIndex;
	if(indexDistance>INDEX_DISTANCE && startBall->m_color==endBall->m_color)
	{	
		isBack=true;
		for(int i=start;i>=0;i--)
		{
			Ball *currBall=(Ball*)m_balls->objectAtIndex(i);
			currBall->m_moveToPosIndex=endBall->m_curPosIndex+INDEX_DISTANCE*(start-i+1);
			currBall->move();
		}
	}
	return isBack;
}

/************************************************************************/
/* ��UIɾ����                                                                     */
/************************************************************************/
void SceneFight::removeBallFromUI(int removeStart,int removeEnd)
{
	for(int i=removeStart;i<=removeEnd;i++)
	{
		Ball *removeBall=(Ball*)m_balls->objectAtIndex(i);
		ballExplosion(removeBall->m_sprite->getPosition());
		removeBall->m_sprite->removeFromParentAndCleanup(true);
	}

}
/************************************************************************/
/* ��������ɾ��                                                                     */
/************************************************************************/
void SceneFight::removeBallFromArray(int removeStart,int removeEnd)
{
	CCArray *tmpBalls=CCArray::create();
	//�ռ�Ҫɾ������
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
/* �����Ƿ��������ƶ�                                                                     */
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

/* 
�ж������߶��Ƿ��ཻ(�н���) 
*/  
bool SceneFight::IsLineSegmentCross(CCPoint pFirst1, CCPoint pFirst2, CCPoint pSecond1, CCPoint pSecond2)  
{  
	//ÿ���߶ε����㶼����һ���߶ε����Ҳ�ͬ�࣬���ܶ϶��߶��ཻ  
	//��ʽ��������(x1,y1)->(x2,y2),�жϵ�(x3,y3)�����������,�ұ�,��������.  
	//p=x1(y3-y2)+x2(y1-y3)+x3(y2-y1).p<0 ���,    p=0 ����, p>0 �Ҳ�  
	long Linep1,Linep2;  
	//�ж�pSecond1��pSecond2�Ƿ���pFirst1->pFirst2����  
	Linep1 = pFirst1.x * (pSecond1.y - pFirst2.y) +  
		pFirst2.x * (pFirst1.y - pSecond1.y) +  
		pSecond1.x * (pFirst2.y - pFirst1.y);  
	Linep2 = pFirst1.x * (pSecond2.y - pFirst2.y) +  
		pFirst2.x * (pFirst1.y - pSecond2.y) +  
		pSecond2.x * (pFirst2.y - pFirst1.y);  
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//����λ���Ϊ0:pSecond1��pSecond2��pFirst1->pFirst2ͬ��  
	{  
		return false;  
	}  
	//�ж�pFirst1��pFirst2�Ƿ���pSecond1->pSecond2����  
	Linep1 = pSecond1.x * (pFirst1.y - pSecond2.y) +  
		pSecond2.x * (pSecond1.y - pFirst1.y) +  
		pFirst1.x * (pSecond2.y - pSecond1.y);  
	Linep2 = pSecond1.x * (pFirst2.y - pSecond2.y) +  
		pSecond2.x * (pSecond1.y - pFirst2.y) +  
		pFirst2.x * (pSecond2.y - pSecond1.y);  
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//����λ���Ϊ0:pFirst1��pFirst2��pSecond1->pSecond2ͬ��  
	{  
		return false;  
	}  
	//������Ϊ�ཻ  
	return true;  
}  
/************************************************************************/
/* ��ʼ����ͼ�켣�ڵ�                                                                     */
/************************************************************************/
void SceneFight::initWayPoint(){
	std::string pts="705.809937,234.493042|618.227051,198.563858|474.503174,135.688690|301.588257,126.706619|164.602722,167.126144|79.264282,252.457718|61.295475,331.054443|74.766144,420.881439|162.347595,506.219116|283.618622,542.151428|404.890686,544.397217|517.179077,519.693726|566.584900,483.761627|629.463135,402.915833";
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
		//�������
		float distance = ccpDistance(start, end);
		if (distance > 1)
		{
			int d = (int)distance;
			for (int i = 0; i < d; i+=12)
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
/* ��ʾ��ըЧ��                                                                     */
/************************************************************************/
void SceneFight::ballExplosion(CCPoint pt){
	CCFileUtils::sharedFileUtils()->setResourceDirectory("ui");
	//���ӷ�����
	CCParticleSystem * emitter=CCParticleExplosion::create(); 
	//��ըЧ��
	emitter->setPosition(ccp(pt.x,pt.y)); 
	emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("CloseNormal.png")); 
	emitter->setBlendAdditive(true);
	emitter->setLife(0.5f);//��������
	emitter->setLifeVar(0);
	emitter->setAutoRemoveOnFinish(true);
	this->addChild(emitter);
}
/* 
����ֱ�߽��㣬ǰ��������ֱ�߱����н��� 
���ཻ������£�����Ӧ���������(��ֱ��ϵ����) 
*/  
CCPoint SceneFight::GetCrossPoint(CCPoint p1, CCPoint p2, CCPoint q1, CCPoint q2)  
{  
	//�����ཻ����Ĳ����߶εĽ��㣬��������ĳ������ͨ�õ�  
	assert(IsLineSegmentCross(p1,p2,q1,q2));  
	/*��������ʽ��Ϊ��׼ʽ�����������Է�����*/  
	CCPoint crossPoint;  
	long tempLeft,tempRight;  
	//��x����  
	tempLeft = (q2.x - q1.x) * (p1.y - p2.y) - (p2.x - p1.x) * (q1.y - q2.y);  
	tempRight = (p1.y - q1.y) * (p2.x - p1.x) * (q2.x - q1.x) + q1.x * (q2.y - q1.y) * (p2.x - p1.x) - p1.x * (p2.y - p1.y) * (q2.x - q1.x);  
	crossPoint.x =(int)( (double)tempRight / (double)tempLeft );  
	//��y����    
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