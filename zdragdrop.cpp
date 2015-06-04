#include "zdragdrop.h"
#include <QDebug>

ZDragDrop::ZDragDrop(QObject *parent) :
	QObject(parent)
	{
	resizeButton= new QPushButton((QWidget*)parent);
	burnButton= new QPushButton((QWidget*)parent);
	disableButton= new QPushButton((QWidget*)parent);

	addWithoutObject(disableButton);
	addWithoutObject(burnButton);

	disableButton->hide();
	burnButton->hide();
	resizeButton->hide();

	disableButton->setCursor(Qt::PointingHandCursor);
	burnButton->setCursor(Qt::PointingHandCursor);
	resizeButton->setCursor(Qt::PointingHandCursor);

	disableButton->setObjectName("__disableButton");
	burnButton->setObjectName("__burnButton");
	resizeButton->setObjectName("__resizeButton");

	disableButton->setGeometry(0,0,20,20);
	burnButton->setGeometry(0,0,20,20);
	resizeButton->setGeometry(0,0,20,20);

	disableButton->setStyleSheet("QPushButton#__disableButton {"
								 "border-image: url(:/drgdrpres/pause-icon.png);}"
								 "QPushButton#__disableButton:pressed {"
								 "border-image: url(:/drgdrpres/pause-icon2.png);}");
	burnButton->setStyleSheet("QPushButton#__burnButton {"
								 "border-image: url(:/drgdrpres/burn-icon.png);}"
								 "QPushButton#__burnButton:pressed {"
								 "border-image: url(:/drgdrpres/burn-icon2.png);}");
	resizeButton->setStyleSheet("QPushButton#__resizeButton {"
								 "border-image: url(:/drgdrpres/resize-diag-2-icon.png);}"
								 "QPushButton#__resizeButton:pressed {"
								 "border-image: url(:/drgdrpres/resize-diag-2-icon2.png);}");

	connect(resizeButton,SIGNAL(clicked()),this,SLOT(resizeButton_clicked()));
	connect(burnButton,SIGNAL(clicked()),this,SLOT(burnButton_clicked()));
	connect(disableButton,SIGNAL(clicked()),this,SLOT(disableButton_clicked()));
	}

bool ZDragDrop::updateWidget(QEvent* event, Ui::MainWindow* ui, QMainWindow* mainWindow, QObject* )
	{

	QMouseEvent *mouseEvent = (QMouseEvent *)event;
	QWidget* widget = static_cast<QWidget*>(mainWindow->childAt(mouseEvent->pos()));

	if (mouseEvent->type() == QEvent::MouseButtonPress &&
		widget!=ui->centralWidget && widget!=ui->widget && widget!=mainWindow)
		{
		if ((widget->objectName() != "__disableButton" &&
			widget->objectName() != "__burnButton" &&
			widget->objectName() != "__resizeButton"))
			{

			disableButton->hide();
			burnButton->hide();
			resizeButton->hide();

			}
		}
	if (event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
		{
		if (mouseEvent->type()==QMouseEvent::MouseButtonPress &&
			widget!=ui->centralWidget && widget!=ui->widget && widget!=mainWindow)
			{
			pressed=true;
			startingPos=mouseEvent->pos();
			widgetPos=widget->pos();
			if (widget!=ui->centralWidget && widget!=mainWindow)
				olderWidget = widget;
			else
				olderWidget = NULL;
			}
		else if ( mouseEvent->type() == QEvent::MouseButtonRelease)
			{
			pressed=false;
			}
		else if (mouseEvent->type()==QMouseEvent::MouseMove && pressed==true)
			{
			for (int i=0;i<withoutWidgets.size();i++)
				if (olderWidget==withoutWidgets.at(i)){
					olderWidget=NULL;
					break;
					}
			if (olderWidget!=NULL)
				{
				olderWidget->move(mouseEvent->pos() - ( startingPos - widgetPos ));
				}
			return true;
			}
		}

	if (event->type() == QEvent::MouseButtonDblClick &&
		widget!=ui->centralWidget && widget!=ui->widget && widget!=mainWindow)
		{
		lastSelected=widget;
		resizeButton->move(widget->mapTo(mainWindow,QPoint(widget->width(),widget->height()-disableButton->height())));
		disableButton->move(widget->mapTo(mainWindow,QPoint(widget->width()+25,widget->height()-disableButton->height())));
		burnButton->move(widget->mapTo(mainWindow,QPoint(widget->width()+50,widget->height()-disableButton->height())));

		if (widget->isEnabled())
			disableButton->setStyleSheet("QPushButton#__disableButton {"
										 "border-image: url(:/drgdrpres/pause-icon.png);}"
										 "QPushButton#__disableButton:pressed {"
										 "border-image: url(:/drgdrpres/pause-icon2.png);}");
		else
			disableButton->setStyleSheet("QPushButton#__disableButton {"
										 "border-image: url(:/drgdrpres/play-icon.png);}"
										 "QPushButton#__disableButton:pressed {"
										 "border-image: url(:/drgdrpres/play-icon2.png);}");
		disableButton->show();
		burnButton->show();
		resizeButton->show();
		}
	return false;
	}

void ZDragDrop::addWithoutObject(QWidget* obj)
	{
	withoutWidgets.append(obj);
	}

void ZDragDrop::setObjectList(QVector<QWidget*>* list)
	{
	createdObjects=list;
	}

void ZDragDrop::resizeButton_clicked()
	{

	}

void ZDragDrop::burnButton_clicked()
	{
	lastSelected->close();
	disableButton->hide();
	burnButton->hide();
	resizeButton->hide();

	createdObjects->removeOne(lastSelected);
	}

void ZDragDrop::disableButton_clicked()
	{
	if (lastSelected->isEnabled())
		{
		lastSelected->setEnabled(false);
		}
	else
		{
		lastSelected->setEnabled(true);
		}

	disableButton->hide();
	burnButton->hide();
	resizeButton->hide();
	}
