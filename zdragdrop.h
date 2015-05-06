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

class ZDragDrop : public QObject
	{
		Q_OBJECT
	private:
		QWidget* olderWidget = NULL;
		QVector<QWidget*>  withoutWidgets;
		QPoint startingPos, widgetPos;
		bool pressed;

	public:
		explicit ZDragDrop(QObject *parent = 0);
		bool updateWidget(QEvent* event, Ui::MainWindow* ui, QMainWindow* mainWindow);
		void addWithoutObject(QWidget* obj);
	signals:

	public slots:

	};

#endif // ZDRAGDROP_H
