#include "swing.h"

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
	if(Strong == 0)
	{
		RandDirection();
		return;
	}
	Process();
}

void Swing::RandDirection()
{
	Direction = qrand()%5;
	Strong = qrand()%(StrongMax-StrongMin) + StrongMin;
	StrongUp = 0;
	StrongDown = Strong;
}

void Swing::Process()
{
	if(++StrongUp >= Strong)
	{
		Strong = 0;
		return;
	}
}
