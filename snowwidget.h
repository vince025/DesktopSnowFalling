#ifndef SNOWWIDGET_H
#define SNOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QList>
#include <QSize>

namespace Ui {
class SnowWidget;
}

class SnowWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit SnowWidget(QWidget *parent = 0);
	~SnowWidget();

	void SetPixmapToLabel(const QList<QPixmap> *pixmapList, const unsigned int width, const unsigned int height);
	int GetDeadLine();
	void SetDeadLine(int deadLine);
	void SetSpeed(int min, int max);
	void SetDirection(int direction);
	void SetEdges(int left, int right, int top, int bottom);

public slots:
	void SwapImageToShow(int index);
	void SwapNextImageToShow();
	void UpdateSnow(bool bStore = false);

protected:
	void paintEvent(QPaintEvent *e);
	void timerEvent(QTimerEvent *e);
	
private:
	Ui::SnowWidget *ui;
	const QList<QPixmap> *pmList; //图片List指针
	int ImageCount; //图片总数
	int ShowIndex, LastShowIndex; //当前显示的图片下标和上一个图片的下标
	int DeadLine; //是否进入堆积区域
	int MinSpeed, MaxSpeed; //移动的最大/小像素
	int incX, incY; //每次移动的X/Y的像素
	int Direction; //方向
	int LeftEdge, RightEdge, TopEdge, BottomEdge; //雪花飘动的范围
};

#endif // SNOWWIDGET_H
