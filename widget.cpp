#include "widget.h"
#include "ui_widget.h"
#include <QDesktopWidget>
#include <QMatrix>
#include <QTransform>
#include <QDebug>
#include <time.h>

#ifdef Q_OS_LINUX
#include <X11/extensions/shape.h>
#endif
#ifdef Q_OS_WIN
#include <windows.h>
#endif

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);
	setGeometry(0, 0, qApp->desktop()->width(), qApp->desktop()->height());
	setWindowFlags(windowFlags()
				   |Qt::FramelessWindowHint //去边框
				   |Qt::X11BypassWindowManagerHint //linux下脱离任务管理器
				   |Qt::WindowStaysOnBottomHint //最低层显示
				   |Qt::Tool //不在任务栏显示
					);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowState(Qt::WindowNoState //不激活
				   |Qt::WindowFullScreen //全屏
				   );
	setFocusPolicy(Qt::NoFocus);
	setWindowOpacity(WINDOW_OPACITY);
#ifdef Q_OS_LINUX
	XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0,
								0, NULL, 0, ShapeSet, YXBanded);
#endif
#ifdef Q_OS_WIN
	SetWindowLong(winId(), GWL_EXSTYLE, GetWindowLong(winId(), GWL_EXSTYLE) |
						WS_EX_TRANSPARENT | WS_EX_LAYERED);
#endif
	int i, j;
	int frame = 2;
	QTransform transform;
	transform.rotate(90.0);
	//transform = QPixmap::trueMatrix(transform, 128, 128);
	for(i = 0; i < MAX_PIXMAP; i++)
	{
		pixmapList[i].clear();
		pixmapList[i].append(QPixmap(":/PixmapRes/"+QString::number(i)+".png"));
		for(j = 0; j < frame-1; j++)
			pixmapList[i].append(pixmapList[i].at(j).transformed(transform));
	}

	qDebug()<<"alloced pixmapList";
	for(i = 0; i < MAX_PICS; i++)
	{
		snow[i] = new SnowWidget(this, frame);
		snow[i]->setGeometry(-128, -128, 64, 64);
		//snow[i]->show();
	}

	swing = new Swing(this, 60, 20);
	startTimer(TIMEOUT_TIME);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::timerEvent(QTimerEvent *e)
{
	const int timeinit = 10;
	static int timeCount = timeinit;
	static int initLabel = MAX_PICS;
	if(--timeCount <= 0)
	{
		qsrand(::time(NULL));
		timeCount = timeinit;
		if(initLabel > 0)
		{
			--initLabel;
			snow[initLabel]->move(0, -snow[initLabel]->height());
			qDebug()<<"Init snow["+QString::number(initLabel)+"]";
		}
	}

	//swing
	swing->Update();

	//action flow down
	FlashSnow();
}

void Widget::SetLabelBG(const QPixmap &pixmap, QLabel *label)
{
	if(!label || pixmap.isNull()) return;
	QPixmap map = pixmap.scaled(label->size());
	if(map.isNull()) return;
	label->setPixmap(map);
}

void Widget::FlashSnow()
{
	int i;
	for(i = 0; i < MAX_PICS; i++)
	{
		if(snow[i] == NULL) continue;
		if(snow[i]->y() == -snow[i]->height())
		{
			//repaint label's backgroud
			int imgId = (qrand()%MAX_PIXMAP);
			//resize label
			int size = (qrand()%48)+16;
			snow[i]->SetPixmapToLabel(pixmapList[imgId], size, size);

			//init place
			int x = (qrand()%this->width());
			snow[i]->move(x, 10-snow[i]->height());
		}
		else if(snow[i]->x() == -128) continue;
		else
		{
			//snow flow down
			SnowFlowDown(snow[i]);
		}
	}
}

void Widget::SnowFlowDown(SnowWidget *widget, bool bRandom)
{
	int downX, downY;
	if(!widget) return;

	//Y
	downY = widget->y()+5;
	if(bRandom)
	{
		downY = widget->y()+qrand()%(this->height() - widget->y());
	}
	if(downY > (this->height())) downY = -widget->height();

	//X
	if(swing->GetDirection() == Swing::LEFT_DIRECTION)
		downX = widget->x() - 5;
	else if(swing->GetDirection() == Swing::RIGHT_DIRECTION)
		downX = widget->x() + 5;
	else
		downX = widget->x();
	if(downX < -widget->width()) downX = this->width();
	if(downX > this->width()) downX = -widget->width();

	widget->move(downX, downY);
	widget->SwapNextImageToShow();
}
