#include "Ball.h"

Ball::Ball(void)
{
	m_curPosIndex=0;
	m_moving=false;
	m_isRemove=false;
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
		float moveDuration = 0.3f;

		CCMoveTo *actionMove = CCMoveTo::actionWithDuration(moveDuration,end);
		CCCallFunc *call=CCCallFunc::actionWithTarget(this,callfunc_selector(Ball::go));
		m_goSequneceAction = CCSequence::actions(actionMove,call,NULL);   
		this->m_sprite->runAction(m_goSequneceAction);
	}
	else
	{
		//超出范围删除
		//[self removeFromParentAndCleanup:YES];
	}
	m_curPosIndex++; //当前的位置ＩＤ后移
}

void Ball::move(){
	
	stop();
	m_moving=true;
	runMoveAction();
}
void Ball::stop()
{
	this->m_sprite->stopAction(m_goSequneceAction);
}

void Ball::runMoveAction()
{
	if(m_curPosIndex>m_moveToPosIndex)
		m_curPosIndex--;
	else
		m_curPosIndex++;
	if(m_curPosIndex!=m_moveToPosIndex && m_curPosIndex<m_wayPoint->count())
	{
		CCPoint end=m_wayPoint->getControlPointAtIndex(m_curPosIndex);
		//速度每秒钟所移动的像素值35
		float moveDuration = 0.001f;

		CCMoveTo *actionMove = CCMoveTo::actionWithDuration(moveDuration,end);
		CCCallFunc *call=CCCallFunc::actionWithTarget(this,callfunc_selector(Ball::runMoveAction));
		m_moveSequneceAction = CCSequence::actions(actionMove,call,NULL);   
		this->m_sprite->runAction(m_moveSequneceAction);
	}
	//CCLOG("m_curPosIndex===%d===m_moveToPosIndex===%d",m_curPosIndex,m_moveToPosIndex);	
	if(m_curPosIndex==m_moveToPosIndex)
	{
		m_moving=false;
		if(m_goSequneceAction!=NULL)
			go();
	}
}
void Ball::runMoveActionFinish(){

	runMoveAction();
}