#include "widget.h"
#include "ui_widget.h"
#include <QDesktopWidget>
#include <QMatrix>
#include <QTransform>
#include <QDebug>
#include <time.h>
#include <QCryptographicHash>

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
	setFocusPolicy(Qt::NoFocus); //窗口永远不获取焦点
	setWindowOpacity(WINDOW_OPACITY); //设置窗口透明度
#ifdef Q_OS_LINUX
	//linux下实现鼠标穿透
	XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0,
								0, NULL, 0, ShapeSet, YXBanded);
#endif
#ifdef Q_OS_WIN
	//windows下实现鼠标穿透
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
		pixmapList[i].append(QPixmap(":/PixmapRes/"+QString::number(i)+".png")); //加载图片
		for(j = 0; j < frame-1; j++)
			pixmapList[i].append(pixmapList[i].at(j).transformed(transform)); //对每张图片旋转90度并存到list中
	}

	for(i = 0; i < MAX_PICS; i++) //分配雪花内存
	{
		snow[i] = new SnowWidget(this);
		snow[i]->setGeometry(-128, -128, 64, 64);
		snow[i]->SetSpeed(3, 8);
		snow[i]->SetEdges(0, this->width(), 0, this->height());
		//snow[i]->show();
	}

	swing = new Swing(this, 120, 60); //方向类
	startTimer(TIMEOUT_TIME); //timer用于定时更新雪花, 实现动画效果
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
		qsrand(::time(NULL)); //每隔一段时间, 更新随机数种子
		timeCount = timeinit;
		if(initLabel > 0) //初始化雪花
		{
			--initLabel;
			snow[initLabel]->move(0, -snow[initLabel]->height());
		}
	}

	//swing
	swing->Update(); //更新方向

	//action flow down
	FlashSnow(); //更新雪花动画
}

void Widget::FlashSnow()
{
	int i;
	for(i = 0; i < MAX_PICS; i++)
	{
		if(snow[i] == NULL) continue;
		if(snow[i]->y() == -snow[i]->height()) //雪花准备飘落
		{
			//repaint label's backgroud
			int imgId = (qrand()%MAX_PIXMAP); //随机选择雪花图片
			//resize label
			int size = (qrand()%(SnowSizeMax-SnowSizeMin))+SnowSizeMin; //随机选择雪花大小
			snow[i]->SetPixmapToLabel(&(pixmapList[imgId]), size, size); //设置雪花图片组和大小
			//qDebug()<<"init "<<QString::number(i);

			//init place
			int x = (qrand()%this->width()); //随机选择开始飘落的X坐标
			snow[i]->move(x, 10-snow[i]->height());
		}
		else if(snow[i]->x() == -128) continue;  //初始化为-128
		else
		{
			//snow flow down
			snow[i]->SetDirection(swing->GetDirection());
			//snow[i]->UpdateSnow(true);
		}
	}
}
