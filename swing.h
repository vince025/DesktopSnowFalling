#ifndef SWING_H
#define SWING_H

#include <QObject>

class Swing : public QObject
{
	Q_OBJECT
public:
	explicit Swing(QObject *parent = 0, unsigned int strongMax = 20, unsigned int strongMin = 0);

	int GetDirection();

	static const int NO_DIRECTION = 0;
	static const int LEFT_DIRECTION = 0;
	static const int RIGHT_DIRECTION = 0;
	static const int UP_DIRECTION = 0;
	static const int DOWN_DIRECTION = 0;
	
signals:
	
public slots:
	void Update();
	
protected:
	void RandDirection();
	void Process();

private:
	int Direction;
	unsigned int Strong;
	unsigned int StrongMin, StrongMax;
	unsigned int StrongUp, StrongDown;
};

#endif // SWING_H