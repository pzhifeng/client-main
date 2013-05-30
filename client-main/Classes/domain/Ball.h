#include "cocos2d.h"
using namespace cocos2d;

class Ball :public CCObject
{
public :
	CCSprite *m_sprite;
	CCPointArray *m_wayPoint;
    int m_curPosIndex;
	CCAction *m_goSequneceAction;
	CCAction *m_moveSequneceAction;
	int m_color;//1=ºì£¬2=»Æ£¬3=À¶
	int m_moveToPosIndex;
	bool m_moving;
	bool m_isPause;
	bool m_isStop;
	bool m_isRemove;
public:
	Ball(void);
	~Ball(void);

	virtual bool init();
	CREATE_FUNC(Ball);

	void go();
	void move();
	void stop();
private:
	void runMoveAction();
	//void runMoveActionFinish();
};

