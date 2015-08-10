#include "zdragdrop.h"
#include <QTime>
#include <QDesktopWidget>

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

		if (toolBoxObjects.indexOf(olderWidget) >= 0 &&
			(mainWindow->mapFromGlobal(QCursor::pos()).x() <= ui->widget->x()+ui->widget->width() &&
			 mainWindow->mapFromGlobal(QCursor::pos()).x() >= ui->widget->x() &&
			 mainWindow->mapFromGlobal(QCursor::pos()).y() <= ui->widget->y()+ui->widget->height() &&
			 mainWindow->mapFromGlobal(QCursor::pos()).y() >= ui->widget->y()))
			{
			toolBoxObjects.removeAt(toolBoxObjects.indexOf(olderWidget));
			createdObjects->append(olderWidget);
			firstRects->append(olderWidget->geometry());
			olderWidget->setParent(ui->widget);
			olderWidget->show();

			QUiLoader yeni;
			QWidget* unnamed = yeni.createWidget(olderWidget->metaObject()->className(),toolPage);
			((QVBoxLayout*)toolPage->layout())->insertWidget(toolIndex,unnamed);

			unnamed->setMinimumSize(olderWidget->minimumSize());
			unnamed->setMaximumSize(olderWidget->maximumSize());
			unnamed->setSizePolicy(olderWidget->sizePolicy());
			unnamed->setObjectName(QDateTime::currentDateTime().toString(Qt::ISODate));
			unnamed->setStyleSheet(olderWidget->styleSheet().replace(olderWidget->objectName(),olderWidget->objectName()));
			unnamed->setProperty("text",olderWidget->property("text"));

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			regulateWidgetGetometryM(unnamed);
#else
			regulateWidgetGetometry(unnamed);
#endif
			toolBoxObjects.append(unnamed);

			QWidget* cache = yeni.createWidget(olderWidget->metaObject()->className(),mainWindow);
			olderWidget->setSizePolicy(cache->sizePolicy());
			olderWidget->setMinimumSize(cache->minimumSize());
			olderWidget->setMaximumSize(cache->maximumSize());
			cache->close();
			}
		else if (toolBoxObjects.indexOf(olderWidget) >= 0)
			{
			olderWidget->setParent(toolPage);
			((QVBoxLayout*)((QWidget*)olderWidget->parent())->layout())->insertWidget(toolIndex,olderWidget);
			}

		olderWidget=NULL;
		pressed=false;


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


		if (toolBoxObjects.indexOf(olderWidget) >= 0)
			{
			toolPage = olderWidget->parentWidget();
			toolIndex = ((QVBoxLayout*)((QWidget*)olderWidget->parent())->layout())->indexOf(olderWidget);
			}
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
						if (toolBoxObjects.indexOf(olderWidget) >= 0)
							{
							olderWidget->setParent(mainWindow);
							olderWidget->move(mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos));
							olderWidget->show();
							}
						else
							olderWidget->setGeometry(ui->widget->mapFrom(mainWindow,mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos)).x(),ui->widget->mapFrom(mainWindow,mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos)).y(),olderWidget->width()+1,olderWidget->height()+1);

					else
						if (toolBoxObjects.indexOf(olderWidget) >= 0)
							{
							olderWidget->setParent(mainWindow);
							olderWidget->move(mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos));
							olderWidget->show();
							}
						else
							olderWidget->setGeometry(ui->widget->mapFrom(mainWindow,mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos)).x(),ui->widget->mapFrom(mainWindow,mainWindow->mapFromGlobal(QCursor::pos()) - (startingPos-widgetPos)).y(),olderWidget->width()-1,olderWidget->height()-1);
					fixer = !fixer;

					disableButton->hide();
					burnButton->hide();
					resizeButton->hide();

					if (createdObjects->indexOf(olderWidget) >= 0)
						(*firstRects)[createdObjects->indexOf(olderWidget)] = QRect(olderWidget->x(),
																					olderWidget->y(),
																					olderWidget->width(),
																					olderWidget->height());
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

void ZDragDrop::setObjectList(QVector<QWidget*>* list, QVector<QRect>* rects)
	{
	createdObjects=list;
	firstRects=rects;
	}

void ZDragDrop::addToolBoxObject(QWidget* obj)
	{
	toolBoxObjects.append(obj);
	}

void ZDragDrop::burnButton_clicked()
	{
	lastSelected->close();
	disableButton->hide();
	burnButton->hide();
	resizeButton->hide();

	firstRects->remove(createdObjects->indexOf(lastSelected));
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



void ZDragDrop::regulateWidgetGetometry(QWidget* widget)
	{
#define MYRESW 1366
#define MYRESH 768

	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry(dwidget.primaryScreen());

	float ratioConstantH =    ( (mainScreenSize.width()) / ((float)MYRESW) );
	float ratioConstantV = ( (mainScreenSize.height()) / ((float)MYRESH) );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	widget->setMinimumHeight(widget->minimumHeight()*ratioConstantH);
	widget->setMaximumHeight(widget->maximumHeight()*ratioConstantH);
	widget->setMinimumWidth(widget->minimumWidth()*ratioConstantH);
	widget->setMaximumWidth(widget->maximumWidth()*ratioConstantH);
	}

void ZDragDrop::regulateWidgetGetometryM(QWidget* widget, float exSize)
	{
#define MYRESW 1366
#define MYRESH 768

	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry(dwidget.primaryScreen());

	float ratioConstantH =    ( (mainScreenSize.width()) / ((float)MYRESW) );
	float ratioConstantV = ( (mainScreenSize.height()) / ((float)MYRESH) );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	widget->setMinimumHeight(widget->minimumHeight()*ratioConstantH*exSize);
	widget->setMaximumHeight(widget->maximumHeight()*ratioConstantH*exSize);
	widget->setMinimumWidth(widget->minimumWidth()*ratioConstantH*exSize);
	widget->setMaximumWidth(widget->maximumWidth()*ratioConstantH*exSize);
	}

void ZDragDrop::regulateWidgetGetometryMnorm(QWidget* widget, float exSize)
	{
#define MYRESW 1366
#define MYRESH 768

	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry(dwidget.primaryScreen());

	float ratioConstantH =    ( (mainScreenSize.width()) / ((float)MYRESW) );
	float ratioConstantV = ( (mainScreenSize.height()) / ((float)MYRESH) );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	widget->setGeometry(widget->x()*ratioConstantH*exSize , widget->y()*ratioConstantH*exSize,
						widget->width()*ratioConstantH*exSize, widget->height()*ratioConstantH*exSize);
	}
