#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include "snowwidget.h"
#include "swing.h"
/*
#define WINDOW_OPACITY		0.5
#define TIMEOUT_TIME		150
#define MAX_PIXMAP			11
#define MAX_PICS			30
*/
namespace Ui {
class Widget;
}

//主背景窗体, 全屏透明显示, 添加鼠标穿透功能, 最低端窗口显示
class Widget : public QWidget
{
	Q_OBJECT
	
public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

	static const qreal WINDOW_OPACITY = 1; //窗口透明度
	static const int TIMEOUT_TIME = 150; //更新时间间隔, 刷新一次动画
	static const int MAX_PIXMAP = 11; //图片张数, QPixmap使用
	static const int MAX_PICS = 100; //雪花总数
	static const int SnowSizeMax = 64; //雪花最大直径
	static const int SnowSizeMin = 16; //雪花最小直径
	
protected:

protected slots:
	void timerEvent(QTimerEvent *e); //
	void FlashSnow(); //更新雪花动画和位置

private:
	Ui::Widget *ui;
	SnowWidget *snow[MAX_PICS]; //雪花数组
	QList<QPixmap> pixmapList[MAX_PIXMAP]; //图片二维数组
	Swing *swing; //方向类
};

#endif // WIDGET_H
