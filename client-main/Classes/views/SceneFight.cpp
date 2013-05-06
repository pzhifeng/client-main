#include "SceneFight.h"
#include "SceneMain.h"
#include "Facade.h"
#include "core/SmartRes.h"

using namespace cocos2d;
extern std::vector<std::string> split(const std::string s, char delim);


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
	//����Ƿ���ײ
	CCScheduler *checkHitScheduler = CCDirector::sharedDirector()->getScheduler();
	checkHitScheduler->scheduleSelector(SEL_SCHEDULE(&SceneFight::checkHitTask),this,0.1f,false);
	//������
	CCScheduler *createBallScheduler = CCDirector::sharedDirector()->getScheduler();
	createBallScheduler->scheduleSelector(SEL_SCHEDULE(&SceneFight::createBallTask),this,0.1f,false);
	//����
	CCScheduler *removeBallScheduler = CCDirector::sharedDirector()->getScheduler();
	removeBallScheduler->scheduleSelector(SEL_SCHEDULE(&SceneFight::removeBallTask),this,0.5f,false);
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
	CCLOG("%f,%f",touchLocation.x,touchLocation.y);
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
	pushBall(0.5f,tmpPos);
}

/************************************************************************/
/* �õ������                                                        */
/************************************************************************/
Ball * SceneFight::getBall(){
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
	CCLOG("pushBall-color===%d",m_pushBall->m_color);
	m_pushBall->retain();
	m_pushBall->m_sprite->setPosition(ccp(_center.x,_center.y-200));
	addChild(m_pushBall->m_sprite);
};
/************************************************************************/
/* ������                                                               */
/************************************************************************/
void SceneFight::pushBall(float interval,CCPoint pos){
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
			for (int i = 0; i < d; i++)
			{
				float difx = end.x - start.x;
				float dify = end.y - start.y;
				float delta = (float)i / distance;
				CCPoint tmpPos=ccp(start.x + (difx * delta), start.y + (dify * delta));
				m_wayPoint->addControlPoint(tmpPos);
			}
		}	
	}
}


/************************************************************************/
/* ��ʾ��ըЧ��                                                                     */
/************************************************************************/
void SceneFight::ballExplosion(CCPoint pt){
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
/************************************************************************/
/* ���������                                                                     */
/************************************************************************/
int ballNum=0;
void SceneFight::createBallTask(float dt){
	if(m_balls->count()>0){
		Ball *lastBall=(Ball*)m_balls->objectAtIndex(m_balls->count()-1);
		if(lastBall->m_curPosIndex<INDEX_DISTANCE)
			return;
	}
	ballNum++;
	if(ballNum>100)
		return;
	Ball *ball=getBall();
	m_balls->addObject(ball);
	ball->m_sprite->setPosition(m_wayPoint->getControlPointAtIndex(0));
	addChild(ball->m_sprite);
	ball->go();
	ballsSort();
}
/************************************************************************/
/* �����ײ                                                                   */
/************************************************************************/
void SceneFight::checkHitTask(float dt){
	int ballArrayIndex=isHit();
	if(ballArrayIndex>=0){
		m_pushBallAction->stop();

		CCSize s = CCDirector::sharedDirector()->getWinSize();
		//ײ������
		Ball *hitBall=(Ball*)m_balls->objectAtIndex(ballArrayIndex);
		//ײ����λ������
		int hitIndex=hitBall->m_curPosIndex+INDEX_DISTANCE;
		//ײ����λ��
		CCPoint hitPos=m_wayPoint->getControlPointAtIndex(hitIndex);
		//ײ����ǰ�������ǰ�ƶ�
		for(int i=0;i<ballArrayIndex;i++){
			Ball *moveBall=(Ball*)m_balls->objectAtIndex(i);
			moveBall->m_curPosIndex+=INDEX_DISTANCE;
			moveBall->move();
		}
		//���������
		//CCLOG("pushBall-color-checkHitTask===%d",m_pushBall->m_color);
		const char *str=getColor(m_pushBall->m_color);
		Ball *insertBall=Ball::create();
		insertBall->m_sprite=CCSprite::create(str);
		insertBall->m_wayPoint=m_wayPoint;
		insertBall->m_curPosIndex=hitIndex;
		insertBall->m_color=m_pushBall->m_color;
		m_balls->insertObject(insertBall,ballArrayIndex);
		insertBall->m_sprite->setPosition(hitPos);
		addChild(insertBall->m_sprite);
		insertBall->go();

		this->pushBallFinish();
	}
}


/************************************************************************/
/* ����                                                                     */
/************************************************************************/
void SceneFight::removeBallTask(float dt){
	CCArray *tmpBalls=CCArray::create();
	for(int i=0;i<m_balls->count();i++){
		Ball *currBall=(Ball*)m_balls->objectAtIndex(i);
		if(currBall->m_moving)
			continue;
		tmpBalls->addObject(currBall);
		int j=0;
		//�ռ�Ҫ��������
		for(j=i+1;j<m_balls->count();j++){
			Ball *nextBall=(Ball*)m_balls->objectAtIndex(j);
			if(nextBall->m_moving)
				break;
			int indexDistance=currBall->m_curPosIndex-nextBall->m_curPosIndex;
			//CCLOG("i===%d===j===%d====indexDistance===%d",i,j,indexDistance);
			if(currBall->m_color==nextBall->m_color)
				tmpBalls->addObject(nextBall);
			else
				break;
		}
		//CCLOG("tmpBalls-size===%d",tmpBalls->count());
		//CCLOG("========================================================");
		//��������������
		if(tmpBalls->count()>=3){
			for(int k=0;k<tmpBalls->count();k++){
				Ball *removeBall=(Ball*)tmpBalls->objectAtIndex(k);
				ballExplosion(removeBall->m_sprite->getPosition());
				removeBall->m_sprite->removeFromParentAndCleanup(true);
				for(int n=0;n<m_balls->count();n++){
					if(removeBall->isEqual(m_balls->objectAtIndex(n))){
						m_balls->removeObject(removeBall);
						break;
					}
				}
			}
			ballsSort();
		}
		tmpBalls->removeAllObjects();
	}
}
/************************************************************************/
/* ����������                                                                     */
/************************************************************************/
void SceneFight::ballsSort(){
	//������������
	//CCLOG("ball-size===%d",m_balls->count());
	int ballNum=m_balls->count();
	if(ballNum<=1)
		return;
	for(int i=ballNum-1;i>0;i--){
		Ball *currBall=(Ball*)m_balls->objectAtIndex(i);
		Ball *preBall=(Ball*)m_balls->objectAtIndex(i-1);
		int indexDistance=preBall->m_curPosIndex-currBall->m_curPosIndex;
		//CCLOG("indexDistance===%d",indexDistance);
		if(indexDistance<=INDEX_DISTANCE)
			continue;
		preBall->m_curPosIndex-=indexDistance;
		preBall->m_curPosIndex+=INDEX_DISTANCE;
		preBall->move();
	}
}
/************************************************************************/
/* �����Ƿ���ײ                                                                     */
/************************************************************************/
int SceneFight::isHit(){
	if(m_pushBall==NULL)
		return -1;
	int i=m_balls->count()-1;
	for(;i>=0;i--){
		Ball *ball=(Ball*)m_balls->objectAtIndex(i);
		CCSprite *_targets=ball->m_sprite;
		CCRect _targetsrect=CCRectMake(_targets->getPosition().x-_targets->getContentSize().width/2, 
			_targets->getPosition().y-_targets->getContentSize().height/2,
			_targets->getContentSize().width, 
			_targets->getContentSize().height);

		CCSprite *_zidans=m_pushBall->m_sprite;
		CCRect _zidansrect=CCRectMake(_zidans->getPosition().x-_zidans->getContentSize().width/2, _zidans->getPosition().y-_zidans->getContentSize().height/2, _zidans->getContentSize().width, _zidans->getContentSize().height);
		//����ӵ��͹������ײ
		if (CCRect::CCRectIntersectsRect(_targetsrect,_zidansrect)){
			//CCLog("i===%d",i);
			break;
		}
	}
	if(i<0)
		i=-1;
	return i;
}

const char* SceneFight::getColor(int colorType){
	//CCLog("colorType===%d",colorType);
	char *str;
	if(colorType==1)
		str="balls/red.png";
	else if(colorType==2)
		str="balls/yellow.png";
	else if(colorType==3)
		str="balls/blue.png";
	else if(colorType==4)
		str="balls/zise.png";
	return str;
}