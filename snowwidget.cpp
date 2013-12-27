#include "snowwidget.h"
#include "ui_snowwidget.h"
#include <QDebug>
#include <QPainter>
#include <QPalette>
#include <QBrush>
#include "swing.h"

SnowWidget::SnowWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SnowWidget)
{
	ui->setupUi(this);
	this->setAutoFillBackground(true);

	ImageCount = 0;
	DeadLine = 0;
	ShowIndex = -1;
	LastShowIndex = 0;
	MinSpeed = 0;
	MaxSpeed = 5;
	incX = incY = 0;
	Direction = Swing::NO_DIRECTION;
	LeftEdge = RightEdge = 0;
	TopEdge = BottomEdge = 400;
}

SnowWidget::~SnowWidget()
{
	delete ui;
}

int SnowWidget::GetDeadLine()
{
	return DeadLine;
}

void SnowWidget::SetDeadLine(int deadLine)
{
	DeadLine = deadLine;
}

void SnowWidget::SetSpeed(int min, int max)
{
	if(min < 0 || min > max) min = 0;
	if(max < 0) max = 5;
	MinSpeed = min;
	MaxSpeed = max;
	incX = MinSpeed + qrand()%(MaxSpeed-MinSpeed);
	incY = MinSpeed + qrand()%(MaxSpeed-MinSpeed);
}

void SnowWidget::SetDirection(int direction)
{
	Direction = direction;
}

void SnowWidget::SetEdges(int left, int right, int top, int bottom)
{
	LeftEdge = left;
	RightEdge = right;
	TopEdge = top;
	BottomEdge = bottom;
}

void SnowWidget::paintEvent(QPaintEvent *e)
{
	//QPainter painter(this);
	//painter.drawPixmap(this->geometry(), pmList->at(ShowIndex)); //Failed
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window, QBrush(pmList->at(ShowIndex).scaled(this->size()))); //Work
	this->setPalette(palette);
}

void SnowWidget::SwapImageToShow(int index)
{
	if(!ImageCount) return ;
	ShowIndex = index % ImageCount; //自动循环,防止越界
	update();
	LastShowIndex = ShowIndex;
}

void SnowWidget::SwapNextImageToShow()
{
	SwapImageToShow(++ShowIndex);
}

void SnowWidget::SetPixmapToLabel(const QList<QPixmap> *pixmapList, const unsigned int width, const unsigned int height)
{
	if(pixmapList == NULL) return;
	this->resize(width, height);
	pmList = pixmapList;
	ImageCount = pixmapList->size(); //可用的最大图片数或label数
	SwapImageToShow(++ShowIndex); //必须先加再用, 最终目的是先显示第0张图片
}

void SnowWidget::UpdateSnow(bool bStore)
{
	int downX, downY;//, incX, incY;

	downX = this->x();
	downY = this->y();
	//X
	if(Direction == Swing::LEFT_DIRECTION)
		downX -= incX;
	else if(Direction == Swing::RIGHT_DIRECTION)
		downX += incX;
	if(downX <= -this->width()) downX = RightEdge;
	if(downX >= RightEdge) downX = -this->width();

	//Y
	downY += incY;
	if(downY >= BottomEdge) downY = -this->height();
	if(bStore)
	{
		if(downY > (BottomEdge - 128)) //进入停止区域
		{
			qsrand(downX);
			if((downY-incY) > (BottomEdge-128)) //已经进入停止区域
			{
				if(this->DeadLine <= downY)
				{
					if(!(qrand()%2))
					{
						this->move(downX, BottomEdge);
					}
					return;
				}
			}
			else //准备进入停止区域
			{
				this->DeadLine=downY+qrand()%96;
			}
		}
	}
	this->SwapNextImageToShow();
	this->move(downX, downY);
}
