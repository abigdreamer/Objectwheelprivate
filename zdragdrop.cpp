#include "zdragdrop.h"

ZDragDrop::ZDragDrop(QObject *parent) :
	QObject(parent)
	{
	}

bool ZDragDrop::updateWidget(QEvent* event, Ui::MainWindow* ui, QMainWindow* mainWindow)
	{
	if (event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
		{
		QMouseEvent *mouseEvent = (QMouseEvent *)event;
		QWidget* widget = static_cast<QWidget*>(mainWindow->childAt(mouseEvent->pos()));
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

	return false;
	}

void ZDragDrop::addWithoutObject(QWidget* obj)
	{
	withoutWidgets.append(obj);
	}
