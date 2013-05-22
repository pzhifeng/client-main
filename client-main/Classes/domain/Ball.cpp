#include "Ball.h"

Ball::Ball(void)
{
	m_curPosIndex=0;
	m_moving=false;
	m_goSequneceAction=NULL;
	m_isPause=false;
	m_isStop=false;
}


Ball::~Ball(void)
{

}

bool Ball::init(){
	return true;
}

void Ball::go()
{
	m_curPosIndex++; //��ǰ��λ�ãɣĺ���
	if(m_curPosIndex<m_wayPoint->count())
	{
		CCPoint end=m_wayPoint->getControlPointAtIndex(m_curPosIndex);
		//�ٶ�ÿ�������ƶ�������ֵ35
		float moveDuration = 0.2f;

		CCMoveTo *actionMove = CCMoveTo::actionWithDuration(moveDuration,end);
		CCCallFunc *call=CCCallFunc::actionWithTarget(this,callfunc_selector(Ball::go));
		m_goSequneceAction = CCSequence::actions(actionMove,call,NULL);   
		this->m_sprite->runAction(m_goSequneceAction);
	}
	else
	{
		//������Χɾ��
		this->m_sprite->removeFromParentAndCleanup(true);
	}
}

void Ball::move()
{
	//stop();
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
		//�ٶ�ÿ�������ƶ�������ֵ35
		float moveDuration = 0.001f;

		CCMoveTo *actionMove = CCMoveTo::actionWithDuration(moveDuration,end);
		CCCallFunc *call=CCCallFunc::actionWithTarget(this,callfunc_selector(Ball::runMoveAction));
		CCAction *moveSequneceAction = CCSequence::actions(actionMove,call,NULL);   
		this->m_sprite->runAction(moveSequneceAction);
	}
	//CCLOG("m_curPosIndex===%d===m_moveToPosIndex===%d",m_curPosIndex,m_moveToPosIndex);	
	
	if(m_curPosIndex==m_moveToPosIndex)
	{
		m_moving=false;
		//if(m_goSequneceAction!=NULL)
			//go();
	}
	
}
/*
void Ball::runMoveActionFinish()
{
	runMoveAction();
	m_moving=false;
}*/