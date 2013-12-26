#include "snowwidget.h"
#include "ui_snowwidget.h"
#include <QDebug>

SnowWidget::SnowWidget(QWidget *parent, int imgCount) :
	QWidget(parent),
	ui(new Ui::SnowWidget)
{
	ui->setupUi(this);

	int i;
	if(imgCount <= 0) ImageCount = MAX_IMG_NUM;
	else ImageCount = imgCount;
	label = new QLabel*[imgCount];
	for(i = 0; i < ImageCount; i++)
	{
		label[i] = new QLabel(this);
		label[i]->hide();
	}
	ShowIndex = -1;
	LastShowIndex = 0;
}

SnowWidget::~SnowWidget()
{
	delete ui;
}

void SnowWidget::SwapImageToShow(int index)
{
	ShowIndex = index % ImageCount; //自动循环,防止越界
	label[ShowIndex]->show();
	label[LastShowIndex]->hide();
	LastShowIndex = ShowIndex;
}

void SnowWidget::SwapNextImageToShow()
{
	SwapImageToShow(++ShowIndex);
}

void SnowWidget::SetPixmapToLabel(const QList<QPixmap> &pixmapList, const QSize &pixmapSize)
{
	int i;
	int listSize = pixmapList.size();
	this->resize(pixmapSize);
	for(i = 0; i < ImageCount && i < listSize; i++)
	{
		QPixmap map = pixmapList.at(i).scaled(pixmapSize);
		label[i]->resize(pixmapSize);
		label[i]->move(0, 0);
		label[i]->setPixmap(map);
	}
	ImageCount = i; //可用的最大图片数或label数
	SwapImageToShow(++ShowIndex); //必须先加再用, 最终目的是先显示第0张图片
}

void SnowWidget::SetPixmapToLabel(const QList<QPixmap> &pixmapList, const int width, const int height)
{
	int i;
	int listSize = pixmapList.size();
	this->resize(width, height);
	for(i = 0; i < ImageCount && i < listSize; i++)
	{
		QPixmap map = pixmapList.at(i).scaled(width, height);
		label[i]->resize(width, height);
		label[i]->move(0, 0);
		if(map.isNull())
		{
			label[i]->setText("e");
		}
		else
		{
			label[i]->setText("");
			label[i]->setPixmap(map);
		}
	}
	ImageCount = i; //可用的最大图片数或label数
	SwapImageToShow(++ShowIndex); //必须先加再用, 最终目的是先显示第0张图片
}
