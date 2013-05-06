#include "Ball.h"

Ball::Ball(void)
{
	m_curPosIndex=0;
	m_moving=false;
}


Ball::~Ball(void)
{
}

bool Ball::init(){
	return true;
}

void Ball::go(){
	//CCLOG("m_curPosIndex===%d",m_curPosIndex);
	//CCLOG("count===%d",m_wayPoint->count());
	if(m_curPosIndex<m_wayPoint->count())
	{
		CCPoint end=m_wayPoint->getControlPointAtIndex(m_curPosIndex);
		//CCLOG("end-x===%f,y===%f",end.x,end.y);
		//速度每秒钟所移动的像素值35
		float moveDuration = 0.1f;

		CCMoveTo *actionMove = CCMoveTo::actionWithDuration(moveDuration,end);
		CCCallFunc *call=CCCallFunc::actionWithTarget(this,callfunc_selector(Ball::go));
		m_sequneceAction = CCSequence::actions(actionMove,call,NULL);   
		this->m_sprite->runAction(m_sequneceAction);
	}
	else
	{
		//超出范围删除
		//[self removeFromParentAndCleanup:YES];
	}
	m_curPosIndex++; //当前的位置ＩＤ后移
}

void Ball::move(){
	this->m_sprite->stopAction(m_sequneceAction);
	m_moving=true;
	runMoveAction();
}

void Ball::runMoveAction(){
	if(m_curPosIndex<m_wayPoint->count())
	{
		CCPoint end=m_wayPoint->getControlPointAtIndex(m_curPosIndex);
		//速度每秒钟所移动的像素值35
		float moveDuration = 0.3f;

		CCMoveTo *actionMove = CCMoveTo::actionWithDuration(moveDuration,end);
		CCCallFunc *call=CCCallFunc::actionWithTarget(this,callfunc_selector(Ball::runMoveActionFinish));
		m_sequneceAction = CCSequence::actions(actionMove,call,NULL);   
		this->m_sprite->runAction(m_sequneceAction);
	}
}
void Ball::runMoveActionFinish(){
	m_moving=false;
	go();
}