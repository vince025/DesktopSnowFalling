#include "swing.h"
#include <time.h>

Swing::Swing(QObject *parent, unsigned int strongMax, unsigned int strongMin) :
	QObject(parent)
{
	if(strongMin >= strongMax) strongMin = 0;
	StrongMax = strongMax;
	StrongMin = strongMin;
	Direction = 0;
	Strong = 0;
}

int Swing::GetDirection()
{
	return Direction;
}

void Swing::Update()
{
	//如果持久度为0, 重新选方向
	if(Strong == 0)
	{
		RandDirection();
		return;
	}
	Process();
}

//随机生成方向和持久度
void Swing::RandDirection()
{
	qsrand(::time(NULL)+Strong);
	if(Direction != NO_DIRECTION)
	{
		Direction = NO_DIRECTION;
		Strong = StrongMin;
	}
	else
	{
		Direction = qrand()%5;
		Strong = qrand()%(StrongMax-StrongMin) + StrongMin;
	}
	StrongUp = 0;
	StrongDown = Strong;
}

//某个方向的持续过程, 当StrongUp到达Strong值, 就重新选方向.
void Swing::Process()
{
	if(++StrongUp >= Strong)
	{
		Strong = 0;
		return;
	}
}
