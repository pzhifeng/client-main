#include "cocos2d.h"
using namespace cocos2d;

class Ball :public CCObject
{
public :
	CCSprite *m_sprite;
	CCPointArray *m_wayPoint;
    int m_curPosIndex;
	CCAction *m_sequneceAction;
	int m_color;//1=�죬2=�ƣ�3=��
	bool m_moving;
public:
	Ball(void);
	~Ball(void);

	virtual bool init();
	CREATE_FUNC(Ball);

	void go();
	void move();
private:
	void runMoveAction();
	void runMoveActionFinish();
};

