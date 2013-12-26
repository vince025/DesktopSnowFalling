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

class Widget : public QWidget
{
	Q_OBJECT
	
public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

	static const qreal WINDOW_OPACITY = 0.5;
	static const int TIMEOUT_TIME = 150;
	static const int MAX_PIXMAP = 11;
	static const int MAX_PICS = 100;
	static const int SnowSizeMax = 64;
	static const int SnowSizeMin = 16;
	
protected:

protected slots:
	void timerEvent(QTimerEvent *e);
	void FlashSnow();

private:
	Ui::Widget *ui;
	SnowWidget *snow[MAX_PICS];
	QList<QPixmap> pixmapList[MAX_PIXMAP];
	Swing *swing;
};

#endif // WIDGET_H
