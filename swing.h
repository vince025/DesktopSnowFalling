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
	static const int LEFT_DIRECTION = 1;
	static const int RIGHT_DIRECTION = 2;
	static const int UP_DIRECTION = 3;
	static const int DOWN_DIRECTION = 4;
	
signals:
	
public slots:
	void Update();
	
protected:
	void RandDirection(); //随机生成方向和持久度
	void Process(); //方向持续过程处理

private:
	int Direction; //方向, 取值上面的静态值
	unsigned int Strong; //持久度
	unsigned int StrongMin, StrongMax; //持久度范围
	unsigned int StrongUp, StrongDown; //实现持久度的辅助变量
};

#endif // SWING_H
