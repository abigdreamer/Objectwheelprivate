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

class ZDragDrop : public QObject
	{
		Q_OBJECT
	private:
		QWidget* olderWidget = NULL;
		QVector<QWidget*>  withoutWidgets;
		QPoint startingPos, widgetPos;
		bool pressed;

		QPushButton* resizeButton,* burnButton,* disableButton;

	public:
		explicit ZDragDrop(QObject *parent = 0);
		bool updateWidget(QEvent* event, Ui::MainWindow* ui, QMainWindow* mainWindow, QObject* obj);
		void addWithoutObject(QWidget* obj);
	signals:

	public slots:

	};

#endif // ZDRAGDROP_H
