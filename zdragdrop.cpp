#include "zdragdrop.h"
#include <QTime>
#include <QDesktopWidget>
#include "zwebbrowser.h"
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

			ZWebBrowser* obj = new ZWebBrowser(ui->widget);
			obj->setObjectName(olderWidget->objectName());
			obj->setEnabled(true);
			obj->setGeometry(olderWidget->geometry());
			obj->setStyleSheet(QString("#%1 {border: 1px solid rgba(0,0,0,190);border-radius: 5px;background-color: rgba(0, 0, 0, 90);}").arg(olderWidget->objectName()));

			createdObjects->append(obj);
			firstRects->append(obj->geometry());
			obj->show();
			return true;
			QUiLoader yeni;
			QWidget* unnamed = yeni.createWidget(olderWidget->metaObject()->className(),toolPage);
			((QVBoxLayout*)toolPage->layout())->insertWidget(toolIndex,unnamed);

			/* Yeni toolbox objesi */
			unnamed->setMinimumSize(olderWidget->minimumSize());
			unnamed->setMaximumSize(olderWidget->maximumSize());
			unnamed->setSizePolicy(olderWidget->sizePolicy());
			unnamed->setObjectName(QDateTime::currentDateTime().toString(Qt::ISODate));
			unnamed->setStyleSheet(olderWidget->styleSheet().replace(olderWidget->objectName(),olderWidget->objectName()));
			unnamed->setProperty("text",olderWidget->property("text"));
			unnamed->setProperty("value",olderWidget->property("value"));

			unnamed->setFocusPolicy(olderWidget->focusPolicy());
			unnamed->setFont(olderWidget->font());
			toolBoxObjects.append(unnamed);

			QWidget* cache = yeni.createWidget(olderWidget->metaObject()->className(),mainWindow);
			olderWidget->setSizePolicy(cache->sizePolicy());
			olderWidget->setMinimumSize(cache->minimumSize());
			olderWidget->setMaximumSize(cache->maximumSize());
			olderWidget->setEnabled(true);

			if (olderWidget->metaObject()->className()==QString("QToolButton"))
				{
				ZWebBrowser* obj = new ZWebBrowser(ui->widget);
				obj->setObjectName(olderWidget->objectName());
				obj->setEnabled(true);
				obj->setGeometry(olderWidget->geometry());
				obj->setStyleSheet(QString("#%1 {border: 1px solid rgba(0,0,0,190);border-radius: 5px;background-color: rgba(0, 0, 0, 90);}").arg(olderWidget->objectName()));

				createdObjects->append(obj);
				firstRects->append(obj->geometry());
				obj->show();

				for (int i=0;i<obj->children().size();i++)
					{
					removeWithoutObjectOf((QWidget*)obj->children().at(i));
					addWithoutObject((QWidget*)obj->children().at(i));
					((QWidget*)obj->children().at(i))->setObjectName(QString("__zwebbrowserbtn%1").arg(i));
					((QWidget*)obj->children().at(i))->setFocusPolicy(Qt::NoFocus);

					if (QString(((QWidget*)obj->children().at(i))->metaObject()->className())=="QProgressBar")
						((QWidget*)obj->children().at(i))->setStyleSheet("QProgressBar {"
																		 "text-align: center;"
																		 "border : 1px solid rgb(90, 90, 100);"
																		 "background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,"
																		 "stop: 0 #fff,"
																		 "stop: 0.4999 #eee,"
																		 "stop: 0.5 #ddd,"
																		 "stop: 1 #eee);"
																		 "}QProgressBar::chunk {"
																		 "background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,"
																		 "stop: 0 #78d,"
																		 "stop: 0.4999 #46a,"
																		 "stop: 0.5 #45a,"
																		 "stop: 1 #238 );}");
					else if (QString(((QWidget*)obj->children().at(i))->metaObject()->className())=="QLineEdit")
						((QWidget*)obj->children().at(i))->setFocusPolicy(Qt::StrongFocus);
					}
				olderWidget->close();
	#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
				ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Custom,false,1.5);
				ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Custom,1.5);
				QRect r = this->frameGeometry();
				this->setGeometry(1,1,1,1);
				this->setGeometry(r);
	#else
				ZVisualRegulator::regulateWidget(obj,ZVisualRegulator::Pc,false);
				ZVisualRegulator::regulateFont(obj,ZVisualRegulator::Pc);
	#endif

				}



#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
			olderWidget->setGeometry(olderWidget->x(),olderWidget->y(),
									 olderWidget->width()*(1.5/MOBILE_SCALE_FACTOR),
									 olderWidget->height()*(1.5/MOBILE_SCALE_FACTOR));
			ZVisualRegulator::regulateFont(olderWidget,ZVisualRegulator::Custom,(1.5/(MOBILE_SCALE_FACTOR*ZVisualRegulator::getRatio())));

			if (createdObjects->indexOf(olderWidget) >= 0)
				(*firstRects)[createdObjects->indexOf(olderWidget)] = QRect(olderWidget->x(),
																			olderWidget->y(),
																			olderWidget->width(),
																			olderWidget->height());
#endif
			scaleDesignArea(ui->autoFit->value(),mainWindow);
			cache->close();
			delete cache;
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
					disableButton->setGeometry(0,0,20,20);
					burnButton->setGeometry(0,0,20,20);
					resizeButton->setGeometry(0,0,20,20);

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



		if (withoutWidgets.indexOf(mainWindow->childAt(mainWindow->mapFromGlobal(QCursor::pos()))) != -1)
			return false;
		else
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
				disableButton->setGeometry(0,0,20,20);
				burnButton->setGeometry(0,0,20,20);
				resizeButton->setGeometry(0,0,20,20);
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
	if (obj->isWidgetType())
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

void ZDragDrop::scaleDesignArea(int val, QMainWindow* mainWindow)
	{
	float value = val / 100.0;

	if (value > 0)
		{
		for (int i=0;i<createdObjects->size();i++)
			{
			QWidget* obj = (QWidget*) createdObjects->at(i);
			obj->setGeometry(firstRects->at(i).x() * value ,
							 firstRects->at(i).y() * value ,
							 firstRects->at(i).width() * value ,
							 firstRects->at(i).height() * value);
			}
		}
	mainWindow->update();
	}


void ZDragDrop::burnButton_clicked()
	{
	lastSelected->close();
	disableButton->hide();
	burnButton->hide();
	resizeButton->hide();
	disableButton->setGeometry(0,0,20,20);
	burnButton->setGeometry(0,0,20,20);
	resizeButton->setGeometry(0,0,20,20);
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
	disableButton->setGeometry(0,0,20,20);
	burnButton->setGeometry(0,0,20,20);
	resizeButton->setGeometry(0,0,20,20);
	}

