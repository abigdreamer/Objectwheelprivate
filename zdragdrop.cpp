#include "zdragdrop.h"
#include <QDebug>
#include <QTime>

ZDragDrop::ZDragDrop(QObject *parent) :
	QObject(parent)
	{
	fixer = false;

	resizeButton= new QPushButton((QWidget*)parent);
	burnButton= new QPushButton((QWidget*)parent);
	disableButton= new QPushButton((QWidget*)parent);

	resizeButton->setFocusPolicy(Qt::NoFocus);
	burnButton->setFocusPolicy(Qt::NoFocus);
	disableButton->setFocusPolicy(Qt::NoFocus);


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
	olderWidget=NULL;
	connect(burnButton,SIGNAL(clicked()),this,SLOT(burnButton_clicked()));
	connect(disableButton,SIGNAL(clicked()),this,SLOT(disableButton_clicked()));
	}

bool ZDragDrop::updateWidget(QEvent* event, Ui::MainWindow* ui, QMainWindow* mainWindow, QObject* )
	{

	QMouseEvent *mouseEvent = (QMouseEvent*)event;

	if ( mouseEvent->type() == QEvent::MouseButtonRelease)
		{
		pressed=false;
		olderWidget=NULL;
		}
	if (mouseEvent->type()==QMouseEvent::MouseButtonPress)
		{
		pressed=true;
		}

	if (withoutWidgets.indexOf(mainWindow->childAt(mainWindow->mapFromGlobal(QCursor::pos()))) == -1 &&
		mouseEvent->type()==QMouseEvent::MouseButtonPress )
		{
		olderWidget = static_cast<QWidget*>(mainWindow->childAt(mainWindow->mapFromGlobal(QCursor::pos())));
		startingPos=mainWindow->mapFromGlobal(QCursor::pos());

		widgetPos=olderWidget->mapTo(mainWindow,QPoint(0,0));
		if (olderWidget->objectName() == "qt_scrollarea_viewport")
			olderWidget=NULL;

		}

	if (mouseEvent->type()==QMouseEvent::MouseMove && pressed==true)
		{

		if (olderWidget!=NULL)
			{

			/* Drag Event */
			if (olderWidget->isEnabled()){
				if (olderWidget->objectName() != "__disableButton" &&
					olderWidget->objectName() != "__burnButton" &&
					olderWidget->objectName() != "__resizeButton")
					{ /* Drag Normal objects  */
					if (fixer)
						olderWidget->setGeometry(ui->widget->mapFrom(mainWindow,mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos)).x(),ui->widget->mapFrom(mainWindow,mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos)).y(),olderWidget->width()+2,olderWidget->height()+2);
					else
						olderWidget->setGeometry(ui->widget->mapFrom(mainWindow,mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos)).x(),ui->widget->mapFrom(mainWindow,mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos)).y(),olderWidget->width()-2,olderWidget->height()-2);
					fixer = !fixer;
					//olderWidget->move( ui->widget->mapFrom(mainWindow,mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos)));
					disableButton->hide();
					burnButton->hide();
					resizeButton->hide();

					}
				else if(lastSelected->isEnabled())
					{ /* Drag Resize_button  */
					olderWidget->move( mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos) );
					}
				}

			/* Resize Event */
			if (resizeButton->isDown() && lastSelected->isEnabled())
				{
				lastSelected->setGeometry(lastSelected->x(),
										  lastSelected->y(),
										  resizeButton->x()-lastSelected->mapTo(mainWindow,QPoint(0,0)).x(),
										  resizeButton->y()-lastSelected->mapTo(mainWindow,QPoint(0,0)).y()+resizeButton->height());

				burnButton->move(resizeButton->x()+20,resizeButton->y());
				disableButton->move(resizeButton->x()+40,resizeButton->y());
				}

			}
		return true;
		}

	/////////////////////////////////////


	if (mouseEvent->type() == QEvent::MouseButtonPress )
		{
		if (olderWidget!=NULL)
			if (olderWidget->objectName() != "__disableButton" &&
				olderWidget->objectName() != "__burnButton" &&
				olderWidget->objectName() != "__resizeButton")
				{
				disableButton->hide();
				burnButton->hide();
				resizeButton->hide();
				}
		}
	if (olderWidget!=NULL)
		if (event->type() == QEvent::MouseButtonDblClick
			&& olderWidget!=resizeButton && olderWidget->objectName()!="__cW" &&olderWidget->parent() == ui->widget )
			{
			lastSelected=olderWidget;
			resizeButton->move(olderWidget->mapTo(mainWindow,QPoint(olderWidget->width(),olderWidget->height()-disableButton->height())));
			disableButton->move(olderWidget->mapTo(mainWindow,QPoint(olderWidget->width()+20,olderWidget->height()-disableButton->height())));
			burnButton->move(olderWidget->mapTo(mainWindow,QPoint(olderWidget->width()+40,olderWidget->height()-disableButton->height())));

			if (olderWidget->isEnabled())
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

void ZDragDrop::removeWithoutObjectOf(QWidget* obj)
	{
	if (withoutWidgets.indexOf(obj)!=-1)
		withoutWidgets.remove(withoutWidgets.indexOf(obj));
	}

void ZDragDrop::setObjectList(QVector<QWidget*>* list)
	{
	createdObjects=list;
	}

void ZDragDrop::burnButton_clicked()
	{
	lastSelected->close();
	disableButton->hide();
	burnButton->hide();
	resizeButton->hide();

	createdObjects->remove(createdObjects->indexOf(lastSelected));
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
