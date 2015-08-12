#ifndef ZDRAGDROP_H
#define ZDRAGDROP_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QWidget>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QVector>
#include <QPushButton>
#include <QUiLoader>
#include "zvisualregulator.h"

class ZDragDrop : public QObject
	{
		Q_OBJECT
	private:
		QWidget* olderWidget = NULL;
		QWidget* toolPage;
		int toolIndex;
		QVector<QWidget*>  withoutWidgets;
		QPoint startingPos, widgetPos;
		bool pressed;
		QWidget* lastSelected;
		QPushButton* resizeButton,* burnButton,* disableButton;
		QVector<QWidget*>* createdObjects;
		QVector<QWidget*> toolBoxObjects;
		QVector<QRect>* firstRects;

		bool fixer;
	public:
		explicit ZDragDrop(QObject *parent = 0);
		bool updateWidget(QEvent* event, Ui::MainWindow* ui, QMainWindow* mainWindow, QObject* obj);
		void addWithoutObject(QWidget* obj);
		void removeWithoutObjectOf(QWidget* obj);
		void setObjectList(QVector<QWidget*>* list, QVector<QRect>* rects);
		void regulateWidgetGetometry(QWidget* widget);
		void regulateWidgetGetometryM(QWidget* widget, float exSize=2.0);
		void regulateWidgetGetometryMnorm(QWidget* widget, float exSize=2.0);
		void addToolBoxObject(QWidget* obj);
	signals:

	public slots:
		void burnButton_clicked();
		void disableButton_clicked();
	};

#endif // ZDRAGDROP_H
